#include <iostream>
#include <stdlib.h>
#include "menu.h"

// 主函数
int main(int argc, char *argv[])
{

    list studentList;
    studentList.head = nullptr; // 初始化链表头指针为空
    studentList.size = 0;       // 初始化链表大小为0

    while (true)
    {
        int choice = Menu(); // 显示菜单并获取用户选择

        switch (choice)
        {
        case INPUT_STUDENT_INFO:
            std::cout << "录入学生信息功能待实现。" << std::endl;
            break;
        case PRINT_STUDENT_INFO:
            std::cout << "打印学生信息功能待实现。" << std::endl;
            break;
        case SAVE_STUDENT_INFO:
            std::cout << "保存学生信息功能待实现。" << std::endl;
            break;
        case READ_STUDENT_INFO:
            std::cout << "读取学生信息功能待实现。" << std::endl;
            break;
        case STATISTICS_STUDENT_INFO:
            std::cout << "统计学生信息功能待实现。" << std::endl;
            break;
        case SEARCH_STUDENT_INFO:
            std::cout << "查找学生信息功能待实现。" << std::endl;
            break;
        case MODIFY_STUDENT_INFO:
            std::cout << "修改学生信息功能待实现。" << std::endl;
            break;
        case DELETE_STUDENT_INFO:
            std::cout << "删除学生信息功能待实现。" << std::endl;
            break;
        case EXIT_SYSTEM:
            std::cout << "退出系统，感谢使用！" << std::endl;
            return 0; // 退出程序
        default:
            std::cout << "无效的选择，请重新输入。" << std::endl;
            break;
        }
    }

    return 0; // 返回 0 表示程序成功结束的
}
