/*
对一个整数序列按照从小到大顺序排序，并输出排序后的结果
冒泡排序法实现
*/

#include <iostream>

int main() {

    int arr[1000] = {0};

    std::cout << "请输入一串整数，以空格分隔，输入非数字字符结束：" << std::endl;
    
    int index = 0;
    while (std::cin >> arr[index]) { 
        index++;
    }
   
    // 冒泡排序
    for (int i = 0; i < index -1 ; i++){   //排除最后一个数

        for (int j = 0; j < (index - i - 1 ) ; j++) 
        {
            if(arr[j] > arr[j+1] )
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        
    }

    std::cout << "排序后的结果是：" << std::endl;
    for (int i = 0; i < index; i++) {
        std::cout << arr[i] << " ";
    }
}