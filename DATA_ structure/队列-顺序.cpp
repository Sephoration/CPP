#include <iostream>
using namespace std;
#define MAXSIZE 100


//队列是只允许在一端进行插入，在另一端进行删除的线性表
//队头：允许删除的一端
//队尾：允许插入的一端
//先进先出（FIFO）


typedef struct {
	int data[MAXSIZE];
	int front, rear;  // 队头指针和队尾指针
} SqQueue;  // Sq: sequence 顺序

//入队
bool EnQueue(SqQueue& Q, int x) {
	//rear、front指向同个位置，队列空满冲突，牺牲一个空间
	if ((Q.rear + 1) % MAXSIZE == Q.front){ 
		return false; 
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MAXSIZE;     //循环队列，取余实现循环，a MOD b 
	return true;	
	}

//出队
	bool DeQueue(SqQueue & Q, int& x); {
	
		if (Q.rear == Q.front) {
			return false;  // 队空  
		}
		x = Q.data[Q.front];
		Q.front = (Q.front + 1) % MAXSIZE;  //循环队列
		return true;
	}

	//队列元素个数：return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
