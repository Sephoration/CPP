#include <iostream> 

 void swap(int &a,int&b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

int main() {

    //输入两个值
    int a, b;
    std::cout << "请输入两个整数，以空格分隔: ";
    std::cin >> a >> b;

   swap(a, b); //调用交换函数

    //输出交换后的值
    std::cout << "交换后的值为: " << a << " " << b << std::endl;

    return 0;

}