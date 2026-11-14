#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <stdexcept>
#include <thread>
#include <utility>

// close 后不再接收新数据，但消费者仍可取出队列中已有的条目。
template<class T> class BoundedQueue {
    std::queue<T> queue_;
    const std::size_t capacity_;
    bool closed_ = false;
    std::mutex mutex_;
    std::condition_variable readable_, writable_;
public:
    explicit BoundedQueue(std::size_t capacity) : capacity_(capacity) {
        if (!capacity) throw std::invalid_argument("capacity must be positive");
    }
    bool push(T value) {
        std::unique_lock<std::mutex> lock(mutex_);
        writable_.wait(lock, [this] { return closed_ || queue_.size() < capacity_; });
        if (closed_) return false;
        queue_.push(std::move(value));
        lock.unlock(); readable_.notify_one(); return true;
    }
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        readable_.wait(lock, [this] { return closed_ || !queue_.empty(); });
        if (queue_.empty()) return std::nullopt;
        T result = std::move(queue_.front()); queue_.pop();
        lock.unlock(); writable_.notify_one(); return result;
    }
    void close() {
        { std::lock_guard<std::mutex> lock(mutex_); closed_ = true; }
        readable_.notify_all(); writable_.notify_all();
    }
};
int main() {
    BoundedQueue<int> queue(8);
    std::thread producer([&] { for (int i = 1; i <= 100; ++i) queue.push(i); queue.close(); });
    int sum = 0, count = 0;
    while (auto value = queue.pop()) { sum += *value; ++count; }
    producer.join();
    assert(count == 100 && sum == 5050 && !queue.push(0));
    std::cout << "消费 " << count << " 个数据，总和 " << sum << '\n';
}
