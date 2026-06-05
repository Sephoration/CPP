#include <iostream>
using namespace std;

//int &e: 引用传递一个整型变量，用于返回被删除节点的数据值。
//LinkList & L: 引用传递链表头指针，允许函数修改链表。
//头指针遍历、结点位移

typedef struct LNode {       //LNode结点，定义单链表节点类型
	int data;                //数据域，每个节点存放一个数据元素
	struct LNode* next;      //指针指向下一个节点
}LNode, * LinkList;		     //LNode为节点类型名，LinkList为结构体指针类型名

//在第 i 个位置插插入元素e (带头结点)
bool ListInsert(LinkList& L, int i, int e) {
	if (i < 1)
		return false;
	LNode* p;   //指针p指向当前扫描到的结点
	int j = 0;  //当前p指向的是第几个结点
	p = L;      //L指向头结点,头结点是第0个结点(不存数据)
	while (p != nullptr && j < i - 1) { //循环找到第 i-1 个结点
		p = p->next;
		j++;
	}
	//return InsertNextNode(p, e);
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)     //内存分配失败
		return false;
	s->data = e;       //用结点s保存数据元素e
	s->next = p->next;
	p->next = s;       //将结点s连到p之后
	return true;
}

//后插操作:在p结点之后插入元素e
bool InsertNextNode(LNode* p, int e) {
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)     //内存分配失败
		return false;
	s->data = e;       //用结点s保存数据元素e
	s->next = p->next;
	p->next = s;       //将结点s连到p之后
	return true;
}

//按为序插入（不带头结点）
//需要对头结点进行特殊处理
bool ListInsert(LinkList& L, int i, int e) {
	if (i < 1)
		return false;
	if (i == 1) { //插入第1个结点的操作与其他结点操作不同
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = L;
		L = s;      //头指针指向新结点
		return true;
	}
	LNode* p;  //指针p指向当前扫描到的结点
	int j = 1; //当前p指向的是第几个结点
	p = L;     //p指向第1个结点(注意:不是头结点)

	while (p != NULL && j < i - 1) {//循环找到第 i-1 个结点
		p = p->next;
		j++;
	}
	if (p == NULL)   //i值不合法
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;     //插入成功
}

//前插操作：在p结点之前插入元素e
bool InsertPriorNode(LNode* p, int e) {
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)     //内存分配失败
		return false;
	s->next = p->next;
	p->next = s;       //新结点 s 连到 p 之后
	s->data = p->data; //将p中元素复制到s中
	p->data = e;       //p 中元素覆盖为 e
	return true;
}

//按为序删除（带头结点）
bool ListDelete(LinkList& L, int i, int& e) {  //同时返回e的值，故&e
	if (i < 1)
		return false;
	LNode* p;//指针p指向当前扫描到的结点
	int j = 0;//当前p指向的是第几个结点
	p = L;//L指向头结点,头结点是第0个结点(不存数据)

	while (p != NULL && j < i - 1) { //循环找到第 i-1 个结点
		p = p->next;
		j++;
	}
	if (p == NULL)//i值不合法
		return false;
	if (p->next == NULL) //第i-1个结点之后已无其他结点
		return false;
	LNode* q = p->next;  //令q指向被删除结点
	e = q->data;         //用e返回元素的值
	p->next = q->next;   //将*q结点从链中“断开”
	free(q);             //释放结点的存储空间
	return true;         //删除成功
}

//删除指定结点 p
bool DeleteNode(LNode* p) {
	if (p == NULL)
		return false;
	LNode* q = p->next;      //令q指向*p的后继结点
	p->data = p->next->data; //和后继结点交换数据域
	p->next = q->next;       //将*q结点从链中“断开”
	free(q);                 //释放后继结点的存储空间
	return true;