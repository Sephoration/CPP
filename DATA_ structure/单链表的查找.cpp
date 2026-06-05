#include <iostream>

typedef struct LNode {            //LNode结点，定义单链表节点类型
    int data;                     //数据域，每个节点存放一个数据元素
    struct LNode* next;           //指针指向下一个节点
}LNode, * LinkList;

//struct 结构体
//struct LNode是一个结构体类型，它包含一个整型数据域data和一个指向下一个LNode结构体的指针next。
//* LinkList是一个指向LNode结构体的指针类型。这里的*表示这是一个指针类型，而LinkList是这个指针类型的新名字。
//LNode   * L    //声明一个指向单链表第一个节点的指针
//LinkList  L    //和上面功能相同

//按位查找，返回第i个元素（带头结点）
LNode* GetElem(LinkList& L, int i) {
    if (i < 0)
        return nullptr;
    LinkList p;   //指针p指向当前扫描到的结点
    int j = 0;  //当前p指向的是第几个结点 
    p = L;      //L指向头结点,头结点是第0个结点(不存数据)
    while (p != nullptr && j < i - 1) { //循环找到第 i-1 个结点
        p = p->next;
        j++;
    }
    return p;
}

//按值查找,找到数据域 == e 的结点

LNode* LocateElem(LinkList L, ElemType e) {
    LNode* p = L->next;
    //从第1个结点开始查找数据域为e的结点
    while (p != NULL && p->data != e)
        p = p->next;
    return p;//找到后返回该结点指针,否则返回NULL
}

//求表的长度
int Length(LinkList L) {
    int len = 0;//统计表长
    LNode* p = L;
    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}