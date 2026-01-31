//简单计算器
//传统C++

#include <iostream>
#include <cmath>   // 用于数学函数（如 sqrt）
#include <stdio.h>

int main() {

    double a, b;
    char op;
    double result;

    std::cout << "请输入计算表达式（格式：a 操作符 b，例如 3 + 4）：";
    std::cin >> a >> op >> b;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                std::cout << "错误：除数不能为零。" << std::endl;
                return 1;
            }
            result = a / b;
            break;
        default:
            std::cout << "错误：不支持的操作符。" << std::endl;
            return 1;
    }
    std::cout << "结果是: " << result << std::endl;
}