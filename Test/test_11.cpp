// 简单函数
#include <iostream>

void print_hello(int a ) {
    std::cout << "Hello, World!" << a << std::endl;
}   

int main() {
    print_hello(10);
    print_hello(20);
    print_hello(30);
    return 0;
}