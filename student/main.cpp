#include <iostream> // 输入输出流
#include <string>   // 字符串处理
#include "menu.h"   // 菜单头文件

using namespace std;

// 主函数
int main(int argc, char *argv[]) // 读取程序参数
{
    // 初始化学生链表
    list studentList;
    studentList.head = nullptr; // 初始化链表头指针为空
    studentList.size = 0;       // 初始化链表大小为0

    // 主循环，持续显示菜单直到用户选择退出
    while (true)
    {
        int choice = Menu(); // 显示菜单并获取用户选择

        switch (choice)
        {
        // 录入学生信息
        case INPUT_STUDENT_INFO:
            entryStudent(studentList);
            break;
        // 打印学生信息
        case PRINT_STUDENT_INFO:
            printStudent(studentList);
            break;
        // 保存学生信息
        case SAVE_STUDENT_INFO:
            saveStudent(studentList);
            break;
        // 读取学生信息
        case READ_STUDENT_INFO:
            readStudent(studentList);
            break;
        case STATISTICS_STUDENT_INFO:
            statisticsStudent(studentList);
            break;
        case SEARCH_STUDENT_INFO:
            searchStudent(studentList);
            break;
        case MODIFY_STUDENT_INFO:
            modifyStudent(studentList);
            break;
        case DELETE_STUDENT_INFO:
            deleteStudent(studentList);
            break;
        case EXIT_SYSTEM:
            cout << "退出系统，感谢使用！" << endl;
            freeList(studentList); // 释放内存
            return 0;              // 退出程序
        default:
            cout << "无效的选择，请重新输入。" << endl;
            break;
        }

        cout << endl; // 输出空行分隔
    }

    return 0; // 返回 0 表示程序成功结束
}