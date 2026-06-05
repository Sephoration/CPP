#include <iostream>
using namespace std;
#define InitSize 10 // 顺序表的初始长度

typedef struct {
    int* data;  // 指示动态分配数组的指针
    int MaxSize;
    int length;
} SeqList;

// 初始化顺序表
void InitList(SeqList& L) {
    L.data = new int[InitSize]; // 动态分配数组
    L.MaxSize = InitSize;
    L.length = 0; // 初始长度为0
}

// 按位查找
int GetElem(const SeqList& L, int i) {
    if (i < 1 || i > L.length) {
        cout << "Error: Index out of bounds!" << endl;
        exit(1); // 或者返回一个特殊值表示错误
    }
    return L.data[i - 1];
}

// 按值查找
int LocateElem(const SeqList& L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            return i + 1; // 数组下标为i的元素值等于e，返回其位置i+1
        }
    }
    return 0; // 没有找到元素
}

int main() {
    SeqList L;
    InitList(L); // 初始化顺序表

    // 填充数据（这里只是示例，实际应用中应该有更好的数据填充方式）
    for (int i = 0; i < 5; i++) {
        L.data[i] = i + 1; // 假设我们存储1到5
        L.length++; // 增加长度
    }

    // 测试按位查找
    std::cout << "Element at position 3: " << GetElem(L, 3) << std::endl;

    // 测试按值查找
    int position = LocateElem(L, 4);
    if (position != 0) {
        std::cout << "Element 4 found at position: " << position << std::endl;
    }
    else {
        std::cout << "Element 4 not found!" << std::endl;
    }

    // 清理资源
    delete[] L.data;

    return 0;