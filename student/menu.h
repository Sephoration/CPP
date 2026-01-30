#ifndef MENU_H // 检查是否定义过 MENU_H
#define MENU_H // 第一次包含时定义这个标记
#pragma once   // 防止重复包含

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
    int size;   // 链表中节点的数量
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

// 函数声明，不然主函数报错
void entryStudent(list &list);
void printStudent(const list &list);
void saveStudent(const list &list);
void readStudent(list &list);
void statisticsStudent(const list &list);
void searchStudent(const list &list);
void modifyStudent(list &list);
void deleteStudent(list &list);
void freeList(list &list);

#endif // MENU_H