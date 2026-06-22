#include <iostream>
#include <optional>
#include <variant>
#include <string>
#include <vector>

// optional / variant 练习
std::optional<int> safeDivide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

using Value = std::variant<int, double, std::string>;

void printValue(const Value& v) {
    std::visit([](const auto& val) {
        std::cout << val << std::endl;
    }, v);
}

int main() {
    // optional 处理可能为空的值
    std::cout << "=== optional 示例 ===" << std::endl;
    auto r1 = safeDivide(10, 2);
    auto r2 = safeDivide(10, 0);
    std::cout << "10/2 = " << (r1.has_value() ? std::to_string(*r1) : "undefined") << std::endl;
    std::cout << "10/0 = " << (r2.value_or(-1)) << std::endl;

    // variant 类型安全的联合体
    std::cout << "\n=== variant 示例 ===" << std::endl;
    std::vector<Value> values = {42, 3.14, std::string("hello")};
    for (const auto& v : values) printValue(v);

    // 检查当前存储的类型
    Value v = 100;
    if (std::holds_alternative<int>(v)) {
        std::cout << "int: " << std::get<int>(v) << std::endl;
    }
    return 0;
}
