#include <iostream>
using namespace std;

#define MaxSize 15  // 定义顺序表的最大长度

// 定义顺序表结构体
typedef struct {
    int data[MaxSize]; // 静态数组存储顺序表元素
    int length;        // 顺序表当前长度
} SqList;

// 初始化顺序表
void InitList(SqList& L) {
    for (int i = 0; i < MaxSize; i++) {
        L.data[i] = 0; // 将所有元素初始化为0
    }
    L.length = 0; // 顺序表初始长度为0
}

int main() {
    SqList L; // 声明顺序表变量
    InitList(L); // 初始化顺序表
    int myData[15] = { 4, 8, 8, 2, 9, 1, 7, 6, 4, 3, 2, 9, 11, 7, 9 }; // 初始化数据

    // 将数据填充到顺序表中
    for (int i = 0; i < 15; i++) {
        L.data[i] = myData[i];
        L.length++;  // 同时增加顺序表的长度
    }

    // 打印顺序表中的元素
    for (int i = 0; i < L.length; i++) {
        cout << "data[" << i + 1 << "]=" << L.data[i] << endl;
    }
    return 0;

}