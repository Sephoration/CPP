// 多线程基础练习：std::thread 的创建、join、detach

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void print_id(int id)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
    std::cout << "线程 " << id << " 正在运行, 线程ID: "
              << std::this_thread::get_id() << std::endl;
}

void detach_worker()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "detach 线程执行完毕" << std::endl;
}

int main()
{
    // 1. 基本线程创建与 join
    std::cout << "=== 基础线程示例 ===" << std::endl;
    std::thread t1(print_id, 1);
    std::thread t2(print_id, 2);
    std::thread t3(print_id, 3);

    t1.join();
    t2.join();
    t3.join();

    // 2. 使用 lambda 创建线程
    std::cout << "\n=== Lambda 线程 ===" << std::endl;
    int shared = 0;
    std::thread lambda_th([&shared]()
    {
        for (int i = 0; i < 5; i++)
        {
            shared++;
            std::cout << "lambda 线程: shared = " << shared << std::endl;
        }
    });
    lambda_th.join();
    std::cout << "最终 shared = " << shared << std::endl;

    // 3. detach 示例：线程与主线程分离
    std::cout << "\n=== Detach 示例 ===" << std::endl;
    std::thread detach_th(detach_worker);
    detach_th.detach();
    std::cout << "主线程继续执行, detach 线程在后台运行" << std::endl;

    // 4. 批量创建线程
    std::cout << "\n=== 批量线程 ===" << std::endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++)
    {
        threads.emplace_back([i]()
        {
            std::cout << "批量线程 " << i << " 启动" << std::endl;
        });
    }
    for (auto &t : threads)
    {
        t.join();
    }

    std::cout << "\n主线程结束" << std::endl;
    return 0;
}
