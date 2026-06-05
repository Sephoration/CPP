#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef struct StackNode {
	int data;
	struct StackNode * next;
} StackNode, * LinkStack;

void InitStack(LinkStack& S) {  // 初始化栈
	S = NULL;
}

void testStack() {
	LinkStack S;
	InitStack(S);
}

bool Push(LinkStack& S, int x) {  //入栈
	StackNode* p = new StackNode; //建立指针
	p->data = x;
	p->next = S;
	S = p;
	return true;
}

bool Pop(LinkStack& S, int& x) {  //出栈
	if (S == NULL) {
		return false;
	}
	StackNode* p = S;
	x = p->data;
	S = S->next;
	delete p;
	return true;
}

bool GetTop(LinkStack S, int& x) {  //取栈顶元素
	if (S == NULL) {
		return false;
	}
	x = S->data;
	return true;
}

