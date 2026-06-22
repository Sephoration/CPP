// 原子操作练习：atomic 与 mutex 的性能对比

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <chrono>

std::atomic<long long> atomic_counter{0};
long long mutex_counter = 0;
std::mutex mtx;

const int THREAD_COUNT = 8;
const int OPS_PER_THREAD = 1000000;

void atomic_increment()
{
    for (int i = 0; i < OPS_PER_THREAD; i++)
    {
        atomic_counter.fetch_add(1, std::memory_order_relaxed);
    }
}

void mutex_increment()
{
    for (int i = 0; i < OPS_PER_THREAD; i++)
    {
        std::lock_guard<std::mutex> lock(mtx);
        mutex_counter++;
    }
}

// 自旋锁：用 atomic flag 实现
class SpinLock
{
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
        while (flag_.test_and_set(std::memory_order_acquire))
        {
            // 忙等待
        }
    }

    void unlock()
    {
        flag_.clear(std::memory_order_release);
    }
};

SpinLock spin;
long long spin_counter = 0;

void spin_increment()
{
    for (int i = 0; i < OPS_PER_THREAD; i++)
    {
        std::lock_guard<SpinLock> lock(spin);
        spin_counter++;
    }
}

// CAS 操作示例
std::atomic<int> cas_value{0};

void cas_demo()
{
    int expected = 0;
    int desired = 42;

    // 原子地比较并交换
    if (cas_value.compare_exchange_strong(expected, desired))
    {
        std::cout << "CAS 成功: 从 " << expected << " 改为 " << desired << std::endl;
    }
    else
    {
        std::cout << "CAS 失败: 当前值 " << expected << " 不等于期望值" << std::endl;
    }
}

// 无锁计数器
class LockFreeCounter
{
    std::atomic<int> value_{0};

public:
    int increment()
    {
        int old = value_.load(std::memory_order_relaxed);
        while (!value_.compare_exchange_weak(old, old + 1,
              std::memory_order_release, std::memory_order_relaxed))
        {
            // CAS 失败则重试，old 已被更新为最新值
        }
        return old + 1;
    }

    int get() const
    {
        return value_.load(std::memory_order_acquire);
    }
};

void run_benchmark()
{
    std::vector<std::thread> threads;

    // 测试 atomic
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads.emplace_back(atomic_increment);
    }
    for (auto &t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto atomic_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "atomic 耗时: " << atomic_time << "ms, 结果: " << atomic_counter << std::endl;
    threads.clear();

    // 测试 mutex
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads.emplace_back(mutex_increment);
    }
    for (auto &t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    auto mutex_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "mutex 耗时: " << mutex_time << "ms, 结果: " << mutex_counter << std::endl;
    threads.clear();

    // 测试自旋锁
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads.emplace_back(spin_increment);
    }
    for (auto &t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    auto spin_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "spinlock 耗时: " << spin_time << "ms, 结果: " << spin_counter << std::endl;

    std::cout << "\n性能对比: atomic 是 mutex 的 "
              << (mutex_time * 100 / atomic_time) / 100.0
              << " 倍, spinlock 是 mutex 的 "
              << (mutex_time * 100 / spin_time) / 100.0
              << " 倍" << std::endl;
}

int main()
{
    std::cout << "=== 原子操作与同步性能对比 ===" << std::endl;
    std::cout << "线程数: " << THREAD_COUNT
              << ", 每线程操作数: " << OPS_PER_THREAD << std::endl << std::endl;

    // CAS 演示
    cas_demo();

    // 无锁计数器
    std::cout << "\n无锁计数器测试:" << std::endl;
    LockFreeCounter lfc;
    std::vector<std::thread> ts;
    for (int i = 0; i < 4; i++)
    {
        ts.emplace_back([&lfc]()
        {
            for (int j = 0; j < 100000; j++)
            {
                lfc.increment();
            }
        });
    }
    for (auto &t : ts) t.join();
    std::cout << "无锁计数器结果: " << lfc.get() << " (期望 400000)" << std::endl;

    // 性能基准测试
    std::cout << "\n=== 性能基准测试 ===" << std::endl;
    run_benchmark();

    return 0;
}
