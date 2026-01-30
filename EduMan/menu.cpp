#include "menu.h"
#include <iostream>

int Menu()
{
    std::cout << "[================================]" << std::endl;
    std::cout << "[    欢迎使用学生成绩管理系统    ]" << std::endl;
    std::cout << "[================================]" << std::endl;
    std::cout << "[         1.录入学生信息         ]" << std::endl;
    std::cout << "[         2.打印学生信息         ]" << std::endl;
    std::cout << "[         3.保存学生信息         ]" << std::endl;
    std::cout << "[         4.读取学生信息         ]" << std::endl;
    std::cout << "[         5.统计学生信息         ]" << std::endl;
    std::cout << "[         6.查找学生信息         ]" << std::endl;
    std::cout << "[         7.修改学生信息         ]" << std::endl;
    std::cout << "[         8.删除学生信息         ]" << std::endl;
    std::cout << "[         0.退出学生系统         ]" << std::endl;
    std::cout << "[================================]" << std::endl;
    std::cout << "[         请输入您的选择:        ]" << std::endl;

    int choice;
    std::cin >> choice;
    return choice;
}
