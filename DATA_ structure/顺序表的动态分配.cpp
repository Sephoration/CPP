#include <stdlib.h>
#include <iostream>
using namespace std;

#define InitSize 10  //默认的最大长度
typedef struct {
    int* data;     //指示动态分配数组的指针
    int MaxSize;   //顺序表的最大容量
    int length;    //顺序表的当前长度
}SeqList;

void InitList(SeqList& L) {
    //用 malloc 函数申请一片连续的存储空间
    L.data = (int*)malloc(InitSize * sizeof(int));
    L.length = 0;
    L.MaxSize = InitSize;
}

void IncreaseSize(SeqList& L, int len) { //动态控制顺序表的容量
    int* p = L.data;
    L.data = (int*)malloc((L.MaxSize + len) * sizeof(int));
    for (int i = 0; i < L.length; i++) {
        L.data[i] = p[i];
    }
    L.MaxSize = L.MaxSize + len;
    free(p);
}

void Insert(SeqList& L, int element) {  //插入函数，保证顺序表的容量限制
    if (L.length >= L.MaxSize) {
        IncreaseSize(L, 5);  // 增加5的容量
    }
    L.data[L.length] = element;
    L.length++;
}

int main() {
    SeqList L;
    InitList(L); //初始化一个顺序表

    int mydata[12] = { 5, 1, 4, 9, 6, 5, 7, 8, 2, 1, 3, 7 };
    for (int i = 0; i < 12; i++) {
        Insert(L, mydata[i]); // 用插入函数逐个添加数据
    }

    for (int i = 0; i < L.length; i++) {
        cout << "data[" << i + 1 << "]=" << L.data[i] << endl;
    }

    free(L.data); // 在结束前释放内存
    return 0;