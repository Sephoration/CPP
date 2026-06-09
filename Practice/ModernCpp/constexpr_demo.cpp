#include <iostream>

// constexpr 练习
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int fibonacci(int n) {
    return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    constexpr int f5 = factorial(5);
    constexpr int fib10 = fibonacci(10);

    std::cout << "5! = " << f5 << std::endl;
    std::cout << "fib(10) = " << fib10 << std::endl;

    int runtime_val = 7;
    std::cout << "7! = " << factorial(runtime_val) << std::endl;

    return 0;
}
