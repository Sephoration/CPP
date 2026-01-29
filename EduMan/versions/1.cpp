#include <iostream>    // 输入输出流库
#include <string>      // 字符串库

// 学生结构体
struct student {
    int id;                    // 学号 
    std::string name;          // 姓名
    int age;                   // 年龄
    int score;                 // 成绩
};

// 学生节点
struct student_ptr {
    student one;
    student_ptr* next;  // 指向下一个学生的指针
};

// 学生链表，包含头指针和大小
struct student_list {
    student_ptr* head;
    int size;
};

// 初始化链表
void init(student_list& list) {
    list.head = nullptr;
    list.size = 0;
}

// 1. 添加学生函数
void add_student(student_list& list) {
    int id, age, score;
    std::string name;
    
    std::cout << "\n=== 添加学生 ===" << std::endl;
    std::cout << "请输入学号: ";
    std::cin >> id;
    std::cin.ignore();  // 清除输入缓冲区
    
    std::cout << "请输入姓名: ";
    std::getline(std::cin, name);
    
    std::cout << "请输入年龄: ";
    std::cin >> age;
    
    std::cout << "请输入成绩: ";
    std::cin >> score;
    
    // 创建新节点
    student_ptr* new_student = new student_ptr;
    new_student->one.id = id;
    new_student->one.name = name;
    new_student->one.age = age;
    new_student->one.score = score;
    new_student->next = nullptr;
    
    // 添加到链表末尾
    if (list.head == nullptr) {
        list.head = new_student;
    } else {
        student_ptr* temp = list.head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_student;
    }
    list.size++;
    
    std::cout << "添加学生成功！" << std::endl;
}

// 2. 查阅学生函数（根据学号）
void view_student(student_list& list) {
    if (list.size == 0) {
        std::cout << "\n学生列表为空！" << std::endl;
        return;
    }
    
    int id;
    std::cout << "\n=== 查阅学生 ===" << std::endl;
    std::cout << "请输入要查阅的学生学号: ";
    std::cin >> id;
    
    student_ptr* temp = list.head;
    bool found = false;
    
    while (temp != nullptr) {
        if (temp->one.id == id) {
            std::cout << "\n找到学生信息：" << std::endl;
            std::cout << "学号: " << temp->one.id << std::endl;
            std::cout << "姓名: " << temp->one.name << std::endl;
            std::cout << "年龄: " << temp->one.age << std::endl;
            std::cout << "成绩: " << temp->one.score << std::endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    
    if (!found) {
        std::cout << "未找到学号为 " << id << " 的学生！" << std::endl;
    }
}

// 3. 打印全部学生
void print_all_students(student_list& list) {
    if (list.size == 0) {
        std::cout << "\n学生列表为空！" << std::endl;
        return;
    }
    
    std::cout << "\n=== 全部学生列表（共" << list.size << "人） ===" << std::endl;
    student_ptr* temp = list.head;
    int count = 1;
    
    while (temp != nullptr) {
        std::cout << "学生 " << count << ":" << std::endl;
        std::cout << "  学号: " << temp->one.id << std::endl;
        std::cout << "  姓名: " << temp->one.name << std::endl;
        std::cout << "  年龄: " << temp->one.age << std::endl;
        std::cout << "  成绩: " << temp->one.score << std::endl;
        if (temp->next != nullptr) {
            std::cout << "  --------------------" << std::endl;
        }
        temp = temp->next;
        count++;
    }
    std::cout << "===============================" << std::endl;
}

// 菜单函数
void menu() {
    std::cout << "\n========== 学生管理系统 ==========" << std::endl;
    std::cout << "1. 添加学生" << std::endl;
    std::cout << "2. 查阅学生（按学号）" << std::endl;
    std::cout << "3. 打印全部" << std::endl;
    std::cout << "0. 退出" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "请选择操作 (0-3): ";
}

// 清理内存
void cleanup(student_list& list) {
    student_ptr* current = list.head;
    while (current != nullptr) {
        student_ptr* next = current->next;
        delete current;
        current = next;
    }
    list.head = nullptr;
    list.size = 0;
}

int main() {
    student_list list;
    init(list);
    
    int choice;
    
    do {
        menu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                add_student(list);
                break;
            case 2:
                view_student(list);
                break;
            case 3:
                print_all_students(list);
                break;
            case 0:
                std::cout << "\n感谢使用学生管理系统，再见！" << std::endl;
                break;
            default:
                std::cout << "\n无效的选择，请重新输入！" << std::endl;
        }
        
    } while (choice != 0);
    
    // 清理内存
    cleanup(list);
    
    return 0;
}