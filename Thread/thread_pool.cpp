// 现代 C++ 线程池实现

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <chrono>

class ThreadPool
{
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_;

public:
    explicit ThreadPool(size_t threads)
        : stop_(false)
    {
        for (size_t i = 0; i < threads; i++)
        {
            workers_.emplace_back([this, i]()
            {
                while (true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        condition_.wait(lock, [this]()
                        {
                            return stop_ || !tasks_.empty();
                        });

                        if (stop_ && tasks_.empty())
                        {
                            return;
                        }

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }

                    task();
                }
            });
        }
    }

    template <class F, class... Args>
    auto enqueue(F &&f, Args &&...args)
        -> std::future<typename std::invoke_result_t<F, Args...>>
    {
        using return_type = typename std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();

        {
            std::lock_guard<std::mutex> lock(queue_mutex_);

            if (stop_)
            {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks_.emplace([task]()
            {
                (*task)();
            });
        }

        condition_.notify_one();
        return result;
    }

    size_t pending() const
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        return tasks_.size();
    }

    ~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (auto &worker : workers_)
        {
            worker.join();
        }
    }
};

// 测试函数
int add(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return a + b;
}

int main()
{
    std::cout << "=== 现代 C++ 线程池 ===" << std::endl;

    // 创建 4 个线程的线程池
    ThreadPool pool(4);

    // 提交任务并获取返回值
    std::cout << "提交 10 个任务..." << std::endl;
    std::vector<std::future<int>> results;

    for (int i = 0; i < 10; i++)
    {
        results.emplace_back(pool.enqueue(add, i, i * 2));
    }

    // 收集结果
    std::cout << "收集结果:" << std::endl;
    for (auto &result : results)
    {
        std::cout << "结果: " << result.get() << std::endl;
    }

    // 批量打印任务
    std::cout << "\n批量提交 100 个任务:" << std::endl;
    std::vector<std::future<int>> batch;
    for (int i = 0; i < 100; i++)
    {
        batch.emplace_back(pool.enqueue([i]()
        {
            return i * i;
        }));
    }

    int sum = 0;
    for (auto &f : batch)
    {
        sum += f.get();
    }
    std::cout << "前 100 个数的平方和: " << sum << std::endl;

    // 测试 pending 任务数
    std::cout << "\n线程池状态: 析构中, 将等待所有任务完成" << std::endl;

    return 0;
}
