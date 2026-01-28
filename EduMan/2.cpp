// 添加txt文件保存功能

#include <iostream>    // 输入输出流库
#include <string>      // 字符串库
#include <fstream>     // 文件流库

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

// 把数据保存成txt文件
void save_to_file(const student_list& list, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "无法打开文件 " << filename << " 进行保存！" << std::endl;
        return;
    }
    
    // 写入文件头部信息（可选）
    file << "学生管理系统数据文件" << std::endl;
    file << "格式：学号,姓名,年龄,成绩" << std::endl;
    file << "======================" << std::endl;
    
    // 遍历链表，写入每个学生的数据
    student_ptr* temp = list.head;
    while (temp != nullptr) {
        file << temp->one.id << ","
             << temp->one.name << ","
             << temp->one.age << ","
             << temp->one.score << std::endl;
        temp = temp->next;
    }
    
    file.close();
    std::cout << "数据已保存到文件: " << filename << std::endl;
    std::cout << "共保存了 " << list.size << " 条学生记录" << std::endl;
}

// 前置声明：在使用前声明 cleanup
void cleanup(student_list& list);

// 从txt文件加载数据
void load_from_file(student_list& list, const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "无法打开文件 " << filename << " 或文件不存在" << std::endl;
        return;
    }
    
    // 先清空现有链表
    cleanup(list);
    
    std::string line;
    int line_count = 0;
    
    // 跳过文件头部的说明行（可选）
    for (int i = 0; i < 3; i++) {
        if (!std::getline(file, line)) break;
    }
    
    // 读取学生数据
    while (std::getline(file, line)) {
        if (line.empty()) continue;  // 跳过空行
        
        // 解析数据行：学号,姓名,年龄,成绩
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
            try {
                // 创建新学生
                student_ptr* new_student = new student_ptr;
                
                // 解析学号
                std::string id_str = line.substr(0, pos1);
                new_student->one.id = std::stoi(id_str);
                
                // 解析姓名
                new_student->one.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                
                // 解析年龄
                std::string age_str = line.substr(pos2 + 1, pos3 - pos2 - 1);
                new_student->one.age = std::stoi(age_str);
                
                // 解析成绩
                std::string score_str = line.substr(pos3 + 1);
                new_student->one.score = std::stoi(score_str);
                
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
                line_count++;
                
            } catch (const std::exception& e) {
                std::cout << "解析错误，跳过行: " << line << std::endl;
            }
        }
    }
    
    file.close();
    std::cout << "从文件 " << filename << " 加载了 " << line_count << " 条学生记录" << std::endl;
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

// 菜单函数
void menu() {
    std::cout << "\n========== 学生管理系统 ==========" << std::endl;
    std::cout << "1. 添加学生" << std::endl;
    std::cout << "2. 查阅学生（按学号）" << std::endl;
    std::cout << "3. 打印全部" << std::endl;
    std::cout << "4. 保存数据到文件" << std::endl;
    std::cout << "5. 从文件加载数据" << std::endl;
    std::cout << "0. 退出并自动保存" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "请选择操作 (0-5): ";
}

int main() {
    student_list list;
    init(list);
    
    // 程序启动时尝试加载数据
    std::cout << "正在尝试从文件加载数据..." << std::endl;
    load_from_file(list, "students.txt");
    
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
            case 4:
                save_to_file(list, "students.txt");
                break;
            case 5:
                load_from_file(list, "students.txt");
                break;
            case 0:
                std::cout << "\n正在保存数据..." << std::endl;
                save_to_file(list, "students.txt");
                std::cout << "\n感谢使用学生管理系统，再见！" << std::endl;
                break;
            default:
                std::cout << "\n无效的选择，请重新输入！" << std::endl;
                // 清除错误状态
                std::cin.clear();
                std::cin.ignore(10000, '\n');
        }
        
    } while (choice != 0);
    
    // 清理内存
    cleanup(list);
    
    return 0;
}