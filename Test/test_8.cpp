//回文数字判断，121是回文数字

#include <iostream> 


int main() {

    int num, originalNum, reversedNum = 0, remainder;
    std::cout << "请输入一个整数: ";
    std::cin >> num;

    originalNum = num;

    // 反转数字
    while (num != 0) {
        remainder = num % 10;
        reversedNum = reversedNum * 10 + remainder;
        num /= 10;
    }

    // 检查是否为回文
    if (originalNum == reversedNum)
        std::cout << originalNum << " 是回文数字。" << std::endl;
    else
        std::cout << originalNum << " 不是回文数字。" << std::endl;

    return 0;
    
}