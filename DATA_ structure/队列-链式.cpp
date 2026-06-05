#include <iostream>
using namespace  std;

typedef struct QNode {
	int data;
	struct QNode* next;
}LinkNode;

typedef struct {
	LinkNode *front, *rear;
}LQueue;

