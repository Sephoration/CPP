#include <iostream>  
using namespace std;

#define MAXSIZE 100  

typedef struct {
    int data[MAXSIZE];
    int top;  // 栈顶指针  
} SqStack;  // Sq: sequence 顺序  

void InitStack(SqStack& S) {
    S.top = -1;  // 初始化栈顶指针  
}

bool Push(SqStack& S, int x) {
    if (S.top == MAXSIZE - 1) {
        return false;  // 栈满  
    }
    S.data[++S.top] = x;  // 先加后用  
    return true;
}

bool Pop(SqStack& S, int& x) {
    if (S.top == -1) {
        return false;  // 栈空  
    }
    x = S.data[S.top--];  // 先用后减  
    return true;
}

bool GetTop(SqStack S, int& x) {
    if (S.top == -1) {
        return false;  // 栈空  
    }
    x = S.data[S.top];
    return true;
}

void DisplayMenu() {
    cout << "请选择操作:" << endl;
    cout << "1. 入栈" << endl;
    cout << "2. 出栈" << endl;
    cout << "3. 获取栈顶元素" << endl;
    cout << "4. 显示栈内元素" << endl;
    cout << "5. 退出" << endl;
}

void DisplayStack(SqStack S) {
    if (S.top == -1) {
        cout << "栈为空。" << endl;
        return;
    }
    cout << "栈内元素: ";
    for (int i = 0; i <= S.top; i++) {
        cout << S.data[i] << " ";
    }
    cout << endl;
}

int main() {
    SqStack S;
    InitStack(S);
    int option, element;

    // 预先将一些数据入栈  
    int sampleData[] = { 10, 20, 30, 40, 50 };
    for (int i = 0; i < 5; i++) {
        Push(S, sampleData[i]);
    }

    while (true) {
        DisplayMenu();
        cin >> option;

        switch (option) {
        case 1: // 入栈  
            cout << "请输入要入栈的元素: ";
            cin >> element;
            if (Push(S, element)) {
                cout << element << " 已入栈。" << endl;
            }
            else {
                cout << "栈已满!" << endl;
            }
            break;
        case 2: // 出栈  
            if (Pop(S, element)) {
                cout << element << " 已出栈。" << endl;
            }
            else {
                cout << "栈为空!" << endl;
            }
            break;
        case 3: // 获取栈顶元素  
            if (GetTop(S, element)) {
                cout << "栈顶元素是: " << element << endl;
            }
            else {
                cout << "栈为空!" << endl;
            }
            break;
        case 4: // 显示栈内元素  
            DisplayStack(S);
            break;
        case 5: // 退出  
            cout << "退出程序..." << endl;
            return 0;
        default:
            cout << "无效选项，请重试。" << endl;
        }
    }
}