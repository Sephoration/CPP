#include <iostream>
#include <thread>
#include <chrono>

// 进程线程信息练习
int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Hardware concurrency: " << n << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    volatile long long sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time elapsed: " << duration.count() << " us" << std::endl;

    return 0;
}
