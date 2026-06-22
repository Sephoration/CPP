// 生产者-消费者模型：condition_variable 的使用

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <random>

std::mutex mtx;
std::condition_variable cv_producer;
std::condition_variable cv_consumer;
std::queue<int> buffer;
const int BUFFER_MAX = 10;
bool done = false;

std::mt19937 rng(std::random_device{}());

void producer(int id)
{
    for (int i = 0; i < 20; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // 缓冲区满时等待
        cv_producer.wait(lock, []()
        {
            return buffer.size() < BUFFER_MAX;
        });

        int value = std::uniform_int_distribution<int>(1, 100)(rng);
        buffer.push(value);
        std::cout << "生产者 " << id << " 生产: " << value
                  << " (队列大小: " << buffer.size() << ")" << std::endl;

        lock.unlock();
        cv_consumer.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(
            std::uniform_int_distribution<int>(50, 150)(rng)));
    }
}

void consumer(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // 缓冲区空时等待，同时检查是否结束
        cv_consumer.wait(lock, []()
        {
            return !buffer.empty() || done;
        });

        if (buffer.empty() && done)
        {
            break;
        }

        int value = buffer.front();
        buffer.pop();
        std::cout << "消费者 " << id << " 消费: " << value
                  << " (队列大小: " << buffer.size() << ")" << std::endl;

        lock.unlock();
        cv_producer.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(
            std::uniform_int_distribution<int>(100, 200)(rng)));
    }
    std::cout << "消费者 " << id << " 退出" << std::endl;
}

int main()
{
    std::cout << "=== 生产者-消费者模型 ===" << std::endl;
    std::cout << "缓冲区最大容量: " << BUFFER_MAX << std::endl << std::endl;

    // 启动多个生产者和消费者
    std::thread producers[3] = {
        std::thread(producer, 1),
        std::thread(producer, 2),
        std::thread(producer, 3)
    };

    std::thread consumers[2] = {
        std::thread(consumer, 1),
        std::thread(consumer, 2)
    };

    // 等待所有生产者完成
    for (auto &p : producers)
    {
        p.join();
    }

    // 通知消费者结束
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv_consumer.notify_all();

    // 等待消费者完成
    for (auto &c : consumers)
    {
        c.join();
    }

    std::cout << "\n所有任务完成" << std::endl;
    return 0;
}
