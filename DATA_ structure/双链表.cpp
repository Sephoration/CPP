#include <iostream>
using namespace std;
	
//双链表结点类型
typedef struct DNode {
	int data;                        
	struct DNode * prior , * next; //指向前驱结点和后继结点
}DNode, * DLinkList;               //DNode为结点类型名，DLinkList为结点指针类型名

bool InitDLinkList (DLinkList &L) {
	L = (DNode*)malloc(sizeof(DNode)); //分配一个头结点
	if (L == NULL) //内存分配失败
		return false;
	L->prior = NULL; //头结点的prior指向头结点
	L->next = NULL;  //头结点的next指向头结点
	return true;
}