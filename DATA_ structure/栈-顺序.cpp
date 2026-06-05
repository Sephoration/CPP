#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef struct {
	int data[MAXSIZE];
	int top;              //栈顶指针
} SqStack;                //Sq:sequence顺序

void InitStack(SqStack & S){  // 初始化栈
	S.top = -1;
}

void teseStack() {
	SqStack S;
	InitStack(S);
}

bool Push(SqStack& S, int x) {  //入栈
	if (S.top == MAXSIZE - 1){  //栈是否满
		return false;
	}
	S.data[++S.top] = x;        //先加后用
	return true;
} 

bool Pop(SqStack& S, int& x) {  //出栈
	if (S.top == -1) {          //栈是否空
		return false;
	}
	x = S.data[S.top--];        //先用后减
	return true;
} 

bool GetTop(SqStack S, int& x) {  //取栈顶元素
	if (S.top == -1) {            //栈是否空
		return false;
	}
	x = S.data[S.top];
	return true;
}

//共享栈：两个栈共享一个存储空间，top1和top2分别指向两个栈的栈顶
typedef struct {
	int data[MAXSIZE];
	int top1;
	int top2;
} SqDoubleStack;
