// 多线程同步练习：mutex / lock_guard / unique_lock / 死锁避免

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::mutex mtx;
int counter = 0;

void increment(int n)
{
    for (int i = 0; i < n; i++)
    {
        // 手动 lock / unlock
        mtx.lock();
        counter++;
        mtx.unlock();
    }
}

void increment_guard(int n)
{
    // lock_guard: RAII 封装，构造时加锁，析构时自动解锁
    for (int i = 0; i < n; i++)
    {
        std::lock_guard<std::mutex> lock(mtx);
        counter++;
    }
}

class BankAccount
{
    int balance_;
    mutable std::mutex mtx_;

public:
    explicit BankAccount(int initial) : balance_(initial) {}

    void deposit(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        balance_ += amount;
    }

    bool withdraw(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (balance_ >= amount)
        {
            balance_ -= amount;
            return true;
        }
        return false;
    }

    int getBalance() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        return balance_;
    }
};

// 演示死锁及解决方案
std::mutex mtx_a;
std::mutex mtx_b;

void deadlock_demo()
{
    // 同时锁住两个锁，避免死锁
    std::lock(mtx_a, mtx_b);
    // 用 adopt_lock 表示已经上锁，只需析构时解锁
    std::lock_guard<std::mutex> lock_a(mtx_a, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(mtx_b, std::adopt_lock);

    std::cout << "安全地同时持有两个锁" << std::endl;
}

int main()
{
    // 1. 不使用同步的问题
    std::cout << "=== 使用 mutex 保护共享数据 ===" << std::endl;
    counter = 0;
    std::thread t1(increment, 100000);
    std::thread t2(increment, 100000);
    t1.join();
    t2.join();
    std::cout << "手动 lock: counter = " << counter << " (期望 200000)" << std::endl;

    // 2. lock_guard 更安全
    counter = 0;
    std::thread t3(increment_guard, 100000);
    std::thread t4(increment_guard, 100000);
    t3.join();
    t4.join();
    std::cout << "lock_guard: counter = " << counter << " (期望 200000)" << std::endl;

    // 3. 银行账户模拟
    std::cout << "\n=== 银行账户模拟 ===" << std::endl;
    BankAccount account(1000);
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back([&account]()
        {
            for (int j = 0; j < 100; j++)
            {
                account.deposit(10);
                account.withdraw(5);
            }
        });
    }
    for (auto &t : threads)
    {
        t.join();
    }
    std::cout << "最终余额: " << account.getBalance() << " (期望 1000 + 500 = 1500)" << std::endl;

    // 4. 死锁避免
    std::cout << "\n=== 死锁避免 ===" << std::endl;
    deadlock_demo();

    return 0;
}
