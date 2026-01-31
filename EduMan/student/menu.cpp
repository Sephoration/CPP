#include "menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

// 显示菜单并获取用户选择
int Menu()
{
    cout << "[================================]" << endl;
    cout << "[    欢迎使用学生成绩管理系统    ]" << endl;
    cout << "[================================]" << endl;
    cout << "[         1.录入学生信息         ]" << endl;
    cout << "[         2.打印学生信息         ]" << endl;
    cout << "[         3.保存学生信息         ]" << endl;
    cout << "[         4.读取学生信息         ]" << endl;
    cout << "[         5.统计学生信息         ]" << endl;
    cout << "[         6.查找学生信息         ]" << endl;
    cout << "[         7.修改学生信息         ]" << endl;
    cout << "[         8.删除学生信息         ]" << endl;
    cout << "[         0.退出学生系统         ]" << endl;
    cout << "[================================]" << endl;
    cout << "[         请输入您的选择:        ]" << endl;

    int choice;
    cin >> choice;
    
    // 清空输入缓冲区，防止下次读取错误
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return choice;
}

// 检查学号是否已存在
bool isIdExist(const list &list, int id)
{
    Node *current = list.head;
    while (current != nullptr)
    {
        if (current->data.id == id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// 录入学生信息
void entryStudent(list &list)
{
    // 创建节点
    Node *node = new Node;
    node->next = nullptr;

    cout << "输入学生学号: ";
    cin >> node->data.id;
    
    // 检查学号是否重复
    if (isIdExist(list, node->data.id))
    {
        cout << "学号已存在，录入失败！" << endl;
        delete node;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "输入学生姓名: ";
    cin >> node->data.name;

    cout << "输入学生语文成绩: ";
    cin >> node->data.chinese;

    cout << "输入学生数学成绩: ";
    cin >> node->data.math;

    cout << "输入学生英语成绩: ";
    cin >> node->data.english;
    
    // 清空输入缓冲区
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 插入链表头部
    node->next = list.head;
    list.head = node;
    list.size++;
    
    cout << "学生信息录入成功！" << endl;
}

// 打印学生信息
void printStudent(const list &list)
{
    if (list.size == 0)
    {
        cout << "暂无学生信息！" << endl;
        return;
    }

    cout << "学号\t姓名\t语文\t数学\t英语\t总分\t平均分" << endl;
    cout << "----------------------------------------------------------" << endl;
    
    Node *current = list.head;
    while (current != nullptr)
    {
        float total = current->data.chinese + current->data.math + current->data.english;
        float average = total / 3.0f;
        
        cout << current->data.id << "\t"
             << current->data.name << "\t"
             << current->data.chinese << "\t"
             << current->data.math << "\t"
             << current->data.english << "\t"
             << fixed << setprecision(1) << total << "\t"
             << average << endl;
        
        current = current->next;
    }
}

// 保存学生信息到文件
void saveStudent(const list &list)
{
    if (list.size == 0)
    {
        cout << "暂无学生信息可保存！" << endl;
        return;
    }
    
    ofstream outFile("students.dat", ios::binary);
    if (!outFile)
    {
        cout << "无法打开文件进行保存！" << endl;
        return;
    }

    Node *current = list.head;
    while (current != nullptr)
    {
        outFile.write(reinterpret_cast<char*>(&current->data), sizeof(student));
        current = current->next;
    }

    outFile.close();
    cout << "学生信息保存成功！共保存 " << list.size << " 条记录。" << endl;
}

// 从文件读取学生信息
void readStudent(list &list)
{
    ifstream inFile("students.dat", ios::binary);
    if (!inFile)
    {
        cout << "无法打开文件或文件不存在！" << endl;
        return;
    }

    // 清空现有链表
    Node *current = list.head;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;
    list.size = 0;

    // 从文件读取
    student stu;
    while (inFile.read(reinterpret_cast<char*>(&stu), sizeof(student)))
    {
        Node *node = new Node;
        node->data = stu;
        node->next = list.head;
        list.head = node;
        list.size++;
    }

    inFile.close();
    cout << "学生信息读取成功！共读取 " << list.size << " 条记录。" << endl;
}

// 统计学生信息
void statisticsStudent(const list &list)
{
    if (list.size == 0)
    {
        cout << "暂无学生信息！" << endl;
        return;
    }

    float chineseTotal = 0, mathTotal = 0, englishTotal = 0;
    float chineseMax = -1, mathMax = -1, englishMax = -1;
    float chineseMin = 101, mathMin = 101, englishMin = 101;
    
    Node *current = list.head;
    
    // 初始化第一个学生的成绩
    if (current != nullptr)
    {
        chineseMax = chineseMin = current->data.chinese;
        mathMax = mathMin = current->data.math;
        englishMax = englishMin = current->data.english;
    }
    
    while (current != nullptr)
    {
        // 计算总分
        chineseTotal += current->data.chinese;
        mathTotal += current->data.math;
        englishTotal += current->data.english;
        
        // 更新最高分
        if (current->data.chinese > chineseMax) chineseMax = current->data.chinese;
        if (current->data.math > mathMax) mathMax = current->data.math;
        if (current->data.english > englishMax) englishMax = current->data.english;
        
        // 更新最低分
        if (current->data.chinese < chineseMin) chineseMin = current->data.chinese;
        if (current->data.math < mathMin) mathMin = current->data.math;
        if (current->data.english < englishMin) englishMin = current->data.english;
        
        current = current->next;
    }

    cout << "===== 成绩统计 =====" << endl;
    cout << "科目\t平均分\t最高分\t最低分" << endl;
    cout << fixed << setprecision(1);
    cout << "语文\t" << chineseTotal / list.size << "\t" << chineseMax << "\t" << chineseMin << endl;
    cout << "数学\t" << mathTotal / list.size << "\t" << mathMax << "\t" << mathMin << endl;
    cout << "英语\t" << englishTotal / list.size << "\t" << englishMax << "\t" << englishMin << endl;
    cout << "总人数: " << list.size << endl;
}

// 查找学生信息
void searchStudent(const list &list)
{
    if (list.size == 0)
    {
        cout << "暂无学生信息！" << endl;
        return;
    }

    int choice;
    cout << "请选择查找方式：" << endl;
    cout << "1. 按学号查找" << endl;
    cout << "2. 按姓名查找" << endl;
    cin >> choice;

    if (choice == 1)
    {
        int id;
        cout << "请输入学号: ";
        cin >> id;
        
        Node *current = list.head;
        bool found = false;
        while (current != nullptr)
        {
            if (current->data.id == id)
            {
                cout << "找到学生信息：" << endl;
                cout << "学号: " << current->data.id << endl;
                cout << "姓名: " << current->data.name << endl;
                cout << "语文: " << current->data.chinese << endl;
                cout << "数学: " << current->data.math << endl;
                cout << "英语: " << current->data.english << endl;
                found = true;
                break;
            }
            current = current->next;
        }
        
        if (!found)
        {
            cout << "未找到学号为 " << id << " 的学生！" << endl;
        }
    }
    else if (choice == 2)
    {
        char name[50];
        cout << "请输入姓名: ";
        cin >> name;
        
        Node *current = list.head;
        bool found = false;
        int count = 0;
        
        cout << "查找结果：" << endl;
        while (current != nullptr)
        {
            if (strcmp(current->data.name, name) == 0)
            {
                cout << "------------------------" << endl;
                cout << "学号: " << current->data.id << endl;
                cout << "姓名: " << current->data.name << endl;
                cout << "语文: " << current->data.chinese << endl;
                cout << "数学: " << current->data.math << endl;
                cout << "英语: " << current->data.english << endl;
                found = true;
                count++;
            }
            current = current->next;
        }
        
        if (!found)
        {
            cout << "未找到姓名为 " << name << " 的学生！" << endl;
        }
        else
        {
            cout << "------------------------" << endl;
            cout << "共找到 " << count << " 个同名学生。" << endl;
        }
    }
    else
    {
        cout << "无效的选择！" << endl;
    }
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 修改学生信息
void modifyStudent(list &list)
{
    if (list.size == 0)
    {
        cout << "暂无学生信息！" << endl;
        return;
    }

    int id;
    cout << "请输入要修改的学生学号: ";
    cin >> id;
    
    Node *current = list.head;
    while (current != nullptr)
    {
        if (current->data.id == id)
        {
            cout << "找到学生信息，请输入新信息：" << endl;
            
            cout << "输入学生姓名: ";
            cin >> current->data.name;

            cout << "输入学生语文成绩: ";
            cin >> current->data.chinese;

            cout << "输入学生数学成绩: ";
            cin >> current->data.math;

            cout << "输入学生英语成绩: ";
            cin >> current->data.english;
            
            cout << "学生信息修改成功！" << endl;
            
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        current = current->next;
    }
    
    cout << "未找到学号为 " << id << " 的学生！" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 删除学生信息
void deleteStudent(list &list)
{
    if (list.size == 0)
    {
        cout << "暂无学生信息！" << endl;
        return;
    }

    int id;
    cout << "请输入要删除的学生学号: ";
    cin >> id;
    
    Node *current = list.head;
    Node *prev = nullptr;
    
    while (current != nullptr)
    {
        if (current->data.id == id)
        {
            if (prev == nullptr) // 删除头节点
            {
                list.head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            
            delete current;
            list.size--;
            cout << "学生信息删除成功！" << endl;
            
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        
        prev = current;
        current = current->next;
    }
    
    cout << "未找到学号为 " << id << " 的学生！" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 释放链表内存
void freeList(list &list)
{
    Node *current = list.head;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;
    list.size = 0; 
}