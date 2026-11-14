#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <vector>
#include <memory>
#include <utility>

class ThreadPool {
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable ready_;
    bool stopping_ = false;
    void worker() {
        for (;;) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                ready_.wait(lock, [this] { return stopping_ || !tasks_.empty(); });
                if (stopping_ && tasks_.empty()) return;
                task = std::move(tasks_.front()); tasks_.pop();
            }
            task();
        }
    }
    void stop() {
        { std::lock_guard<std::mutex> lock(mutex_); stopping_ = true; }
        ready_.notify_all();
        for (auto& worker : workers_) if (worker.joinable()) worker.join();
    }
public:
    explicit ThreadPool(std::size_t count) {
        if (!count) throw std::invalid_argument("线程数不能为零");
        try { for (std::size_t i = 0; i < count; ++i) workers_.emplace_back([this] { worker(); }); }
        catch (...) { stop(); throw; }
    }
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ~ThreadPool() { stop(); }
    template <class F>
    auto submit(F&& f) -> std::future<std::invoke_result_t<F>> {
        using Result = std::invoke_result_t<F>;
        auto task = std::make_shared<std::packaged_task<Result()>>(std::forward<F>(f));
        auto result = task->get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (stopping_) throw std::runtime_error("线程池正在停止");
            tasks_.emplace([task] { (*task)(); });
        }
        ready_.notify_one(); return result;
    }
};
int main() {
    ThreadPool pool(3);
    std::vector<std::future<int>> results;
    for (int i = 1; i <= 8; ++i) results.push_back(pool.submit([i] { return i * i; }));
    for (auto& result : results) std::cout << result.get() << ' ';
    std::cout << '\n';
}
