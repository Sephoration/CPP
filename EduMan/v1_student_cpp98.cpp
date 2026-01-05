// 传统C++学生管理系统（不使用STL，使用链表）

#include <iostream>
#include <cstring>  // 使用C字符串操作函数
#include <limits>

// 学生类定义
class Student {
public:
    char name[50];      // 学生姓名
    int age;           // 学生年龄
    float score_1;     // 第一门课成绩
    float score_2;     // 第二门课成绩
    Student* next;     // 指向下一个学生的指针
    
    // 计算平均成绩
    float getAverage() const {
        return (score_1 + score_2) / 2.0f;
    }
};

// ================ 函数声明 ================
Student* createStudent(const char* name, int age, float s1, float s2);
void appendStudent(Student*& head, Student* node);
void insertStudent(Student*& head, Student* node);
void listStudents(const Student* head);
Student* findStudent(const Student* head, const char* name);
bool deleteStudent(Student*& head, const char* name);
int countStudents(const Student* head);
void displayStudent(const Student* student);
void clearInputBuffer();
void freeList(Student*& head);

// ================ 函数实现 ================

/**
 * @brief 创建新的学生节点
 * @param name 学生姓名
 * @param age 学生年龄
 * @param s1 成绩1
 * @param s2 成绩2
 * @return 新创建的学生节点指针
 */
Student* createStudent(const char* name, int age, float s1, float s2) {
    Student* newStudent = new Student();
    
    // 安全地复制姓名
    std::strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
    newStudent->name[sizeof(newStudent->name) - 1] = '\0';
    
    newStudent->age = age;
    newStudent->score_1 = s1;
    newStudent->score_2 = s2;
    newStudent->next = nullptr;
    
    return newStudent;
}

/**
 * @brief 将学生节点追加到链表末尾
 * @param head 链表头指针的引用
 * @param node 要添加的学生节点
 */
void appendStudent(Student*& head, Student* node) {
    if (node == nullptr) return;
    
    if (head == nullptr) {
        head = node;
    } else {
        Student* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
}

/**
 * @brief 将学生节点插入到链表头部
 * @param head 链表头指针的引用
 * @param node 要插入的学生节点
 */
void insertStudent(Student*& head, Student* node) {
    if (node == nullptr) return;
    
    node->next = head;
    head = node;
}

/**
 * @brief 显示所有学生信息
 * @param head 链表头指针
 */
void listStudents(const Student* head) {
    if (head == nullptr) {
        std::cout << "当前没有学生记录。" << std::endl;
        return;
    }
    
    std::cout << "\n========== 学生列表 ==========" << std::endl;
    std::cout << "序号\t姓名\t\t年龄\t成绩1\t成绩2\t平均分" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    
    const Student* current = head;
    int index = 1;
    
    while (current != nullptr) {
        std::cout << index << "\t"
                  << current->name << "\t\t"
                  << current->age << "\t"
                  << current->score_1 << "\t"
                  << current->score_2 << "\t"
                  << current->getAverage() << std::endl;
        
        current = current->next;
        index++;
    }
    
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "总计: " << (index - 1) << " 名学生" << std::endl;
}

/**
 * @brief 查找学生
 * @param head 链表头指针
 * @param name 要查找的学生姓名
 * @return 找到的学生节点指针，未找到返回nullptr
 */
Student* findStudent(const Student* head, const char* name) {
    const Student* current = head;
    
    while (current != nullptr) {
        if (std::strcmp(current->name, name) == 0) {
            return const_cast<Student*>(current);
        }
        current = current->next;
    }
    
    return nullptr;
}

/**
 * @brief 删除指定姓名的学生
 * @param head 链表头指针的引用
 * @param name 要删除的学生姓名
 * @return 成功删除返回true，未找到返回false
 */
bool deleteStudent(Student*& head, const char* name) {
    if (head == nullptr) return false;
    
    // 如果删除的是头节点
    if (std::strcmp(head->name, name) == 0) {
        Student* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    
    // 查找要删除的节点
    Student* current = head;
    while (current->next != nullptr) {
        if (std::strcmp(current->next->name, name) == 0) {
            Student* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
        current = current->next;
    }
    
    return false;
}

/**
 * @brief 统计学生数量
 * @param head 链表头指针
 * @return 学生数量
 */
int countStudents(const Student* head) {
    int count = 0;
    const Student* current = head;
    
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * @brief 显示单个学生信息
 * @param student 学生节点指针
 */
void displayStudent(const Student* student) {
    if (student == nullptr) {
        std::cout << "学生信息为空。" << std::endl;
        return;
    }
    
    std::cout << "\n========== 学生详情 ==========" << std::endl;
    std::cout << "姓名: " << student->name << std::endl;
    std::cout << "年龄: " << student->age << std::endl;
    std::cout << "成绩1: " << student->score_1 << std::endl;
    std::cout << "成绩2: " << student->score_2 << std::endl;
    std::cout << "平均分: " << student->getAverage() << std::endl;
}

/**
 * @brief 清空输入缓冲区
 */
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief 释放整个链表内存
 * @param head 链表头指针的引用
 */
void freeList(Student*& head) {
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

/**
 * @brief 获取有效的整数输入
 * @param prompt 提示信息
 * @param min 最小值
 * @param max 最大值
 * @return 有效的整数
 */
int getValidInt(const char* prompt, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        std::cout << "输入无效，请输入" << min << "到" << max << "之间的整数。" << std::endl;
        clearInputBuffer();
    }
}

/**
 * @brief 获取有效的浮点数输入
 * @param prompt 提示信息
 * @param min 最小值
 * @param max 最大值
 * @return 有效的浮点数
 */
float getValidFloat(const char* prompt, float min = 0.0f, float max = 100.0f) {
    float value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        std::cout << "输入无效，请输入" << min << "到" << max << "之间的数字。" << std::endl;
        clearInputBuffer();
    }
}

// ================ 主函数 ================
int main() {
    Student* head = nullptr;  // 链表头指针
    int choice = 0;
    
    std::cout << "========================================" << std::endl;
    std::cout << "      欢迎使用学生管理系统(传统C++版)    " << std::endl;
    std::cout << "========================================" << std::endl;
    
    while (true) {
        std::cout << "\n========== 主菜单 ==========" << std::endl;
        std::cout << "1. 添加学生" << std::endl;
        std::cout << "2. 显示所有学生" << std::endl;
        std::cout << "3. 查找学生" << std::endl;
        std::cout << "4. 删除学生" << std::endl;
        std::cout << "5. 统计学生数量" << std::endl;
        std::cout << "6. 清空所有记录" << std::endl;
        std::cout << "7. 退出系统" << std::endl;
        std::cout << "=============================" << std::endl;
        
        choice = getValidInt("请选择操作(1-7): ", 1, 7);
        
        switch (choice) {
            case 1: {  // 添加学生
                char name[50];
                std::cout << "请输入学生姓名: ";
                std::cin >> name;
                clearInputBuffer();
                
                // 检查是否已存在同名学生
                if (findStudent(head, name) != nullptr) {
                    std::cout << "警告: 已存在同名学生！" << std::endl;
                    char confirm;
                    std::cout << "是否继续添加？(y/n): ";
                    std::cin >> confirm;
                    clearInputBuffer();
                    if (confirm != 'y' && confirm != 'Y') {
                        break;
                    }
                }
                
                int age = getValidInt("请输入学生年龄(1-100): ", 1, 100);
                float score1 = getValidFloat("请输入第一门成绩(0-100): ", 0, 100);
                float score2 = getValidFloat("请输入第二门成绩(0-100): ", 0, 100);
                
                Student* newStudent = createStudent(name, age, score1, score2);
                
                // 选择插入位置
                std::cout << "\n请选择插入位置:" << std::endl;
                std::cout << "1. 添加到末尾" << std::endl;
                std::cout << "2. 插入到开头" << std::endl;
                int insertChoice = getValidInt("请选择(1-2): ", 1, 2);
                
                if (insertChoice == 1) {
                    appendStudent(head, newStudent);
                } else {
                    insertStudent(head, newStudent);
                }
                
                std::cout << "\n学生添加成功！" << std::endl;
                displayStudent(newStudent);
                break;
            }
                
            case 2:  // 显示所有学生
                listStudents(head);
                break;
                
            case 3: {  // 查找学生
                char name[50];
                std::cout << "请输入要查找的学生姓名: ";
                std::cin >> name;
                clearInputBuffer();
                
                Student* found = findStudent(head, name);
                if (found != nullptr) {
                    displayStudent(found);
                } else {
                    std::cout << "未找到姓名为 \"" << name << "\" 的学生。" << std::endl;
                }
                break;
            }
                
            case 4: {  // 删除学生
                char name[50];
                std::cout << "请输入要删除的学生姓名: ";
                std::cin >> name;
                clearInputBuffer();
                
                if (deleteStudent(head, name)) {
                    std::cout << "学生 \"" << name << "\" 删除成功！" << std::endl;
                } else {
                    std::cout << "未找到姓名为 \"" << name << "\" 的学生。" << std::endl;
                }
                break;
            }
                
            case 5:  // 统计学生数量
                std::cout << "\n当前共有 " << countStudents(head) << " 名学生。" << std::endl;
                break;
                
            case 6: {  // 清空所有记录
                if (head == nullptr) {
                    std::cout << "当前没有学生记录。" << std::endl;
                    break;
                }
                
                std::cout << "\n警告: 这将删除所有学生记录！" << std::endl;
                char confirm;
                std::cout << "确定要清空吗？(y/n): ";
                std::cin >> confirm;
                clearInputBuffer();
                
                if (confirm == 'y' || confirm == 'Y') {
                    freeList(head);
                    head = nullptr;
                    std::cout << "所有学生记录已清空。" << std::endl;
                } else {
                    std::cout << "操作已取消。" << std::endl;
                }
                break;
            }
                
            case 7:  // 退出系统
                std::cout << "\n感谢使用学生管理系统！" << std::endl;
                freeList(head);
                head = nullptr;
                return 0;
                
            default:
                std::cout << "无效的选择，请重新输入。" << std::endl;
        }
    }
    
    return 0;
}