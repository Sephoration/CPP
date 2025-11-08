//爬楼梯，一次可以爬1级或2级台阶，求有多少种不同的方法可以爬到第n级台阶。

#include <iostream> 

int main() {

    int n;
    std::cin >> n;
    if (n <= 2) {
        std::cout << n << std::endl;
        return 0;
    }
    int first = 1;
    int second = 2;
    int third = 0;
    for (int i = 3; i <= n; ++i) {
        third = first + second;
        first = second;
        second = third;
    }
    std::cout << third << std::endl;
    return 0;

}