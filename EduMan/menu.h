#ifndef MENU_H
#define MENU_H
#pragma once // 防止重复包含

// 学生结构
typedef struct Student
{
    int id;        // 学号
    char name[50]; // 姓名
    float chinese;
    float math;
    float english;
} student;

// 节点链表
typedef struct Node
{
    student data;      // 学生数据
    struct Node *next; // 指向下一个节点的指针
} Node;

// 链表头和节点数量
typedef struct list
{
    Node *head; // 指向链表头节点的指针
    int   size; // 链表中节点的数量
} list;


// 菜单选项枚举（接口声明）
enum MenuOptions
{
    INPUT_STUDENT_INFO = 1,
    PRINT_STUDENT_INFO,
    SAVE_STUDENT_INFO,
    READ_STUDENT_INFO,
    STATISTICS_STUDENT_INFO,
    SEARCH_STUDENT_INFO,
    MODIFY_STUDENT_INFO,
    DELETE_STUDENT_INFO,
    EXIT_SYSTEM = 0
};

// 显示菜单并返回用户选择
int Menu();

#endif // MENU_H
