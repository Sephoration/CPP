#include <iostream>
#include <map>
#include <tuple>
#include <string>

// 结构化绑定练习
std::tuple<int, std::string, double> getStudent() {
    return {1001, "张三", 89.5};
}

int main() {
    // 绑定 tuple
    std::cout << "=== 结构化绑定 tuple ===" << std::endl;
    auto [id, name, score] = getStudent();
    std::cout << "学号: " << id << ", 姓名: " << name << ", 成绩: " << score << std::endl;

    // 绑定 map 遍历
    std::cout << "\n=== 结构化绑定 map ===" << std::endl;
    std::map<std::string, int> scores = {
        {"张三", 90}, {"李四", 85}, {"王五", 95}
    };
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }

    // 绑定数组
    std::cout << "\n=== 结构化绑定数组 ===" << std::endl;
    int arr[] = {10, 20, 30};
    auto& [a, b, c] = arr;
    std::cout << a << ", " << b << ", " << c << std::endl;
    a = 100;
    std::cout << "修改后 arr[0] = " << arr[0] << std::endl;

    // 绑定 pair
    std::cout << "\n=== 结构化绑定 pair ===" << std::endl;
    auto p = std::make_pair("key", 42);
    auto& [k, v] = p;
    v = 100;
    std::cout << k << " = " << p.second << std::endl;

    return 0;
}
