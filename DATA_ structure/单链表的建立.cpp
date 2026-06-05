//初始化一个单链表
//每次插入一个数据元素

#include <iostream>

//尾插法
typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

//插入元素到表尾
bool ListInsert(LinkList& L, int i, ElemType e) {
    if (i < 1)
        return false;
    LNode* p;
    int j = 0;
    p = L;
    while (p != nullptr && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p == nullptr)
        return false;
    LNode* s = new LNode(); //分配内存
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

LinkList List_Taillnsert(LinkList& L) {  //正向建立单链表
    int x;                               //设ElemType为整型
    L = (LinkList)malloc(sizeof(LNode)); //建立头结点
    LNode* s, * r = L;                   //r为表尾指针

    cin("%d", &x);                     //输入结点的值
    while (x != 9999) {                  //输入9999表示结束
        //s = (LNode*)malloc(sizeof(LNode));
        s = new LNode;
        s->data = x;
        r->next = s;
        r = s;                           //r指向新的表尾结点
        scanf("%d", &x);

        r->next = NULL;                  //尾结点指针置空
        return L;
    }