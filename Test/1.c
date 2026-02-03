//手写编程题考字符串复制操作


#include <stdio.h>
#include <stdio.h>
#include <string.h>

// 方法1：使用标准库函数strcpy
void string_copy_using_strcpy() {
    printf("=== 方法1: 使用strcpy函数 ===\n");
    char source[] = "Hello, World!";
    char destination[50];
    
    strcpy(destination, source);
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n", destination);
    printf("\n");
}

// 方法2：使用标准库函数strncpy（更安全）
void string_copy_using_strncpy() {
    printf("=== 方法2: 使用strncpy函数 ===\n");
    char source[] = "Hello, World!";
    char destination[20];
    
    // 使用strncpy，限制复制的最大长度
    strncpy(destination, source, sizeof(destination) - 1);
    destination[sizeof(destination) - 1] = '\0'; // 确保字符串以null结尾
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n", destination);
    printf("\n");
}

// 方法3：手动实现字符串复制
void manual_string_copy() {
    printf("=== 方法3: 手动实现字符串复制 ===\n");
    char source[] = "Hello, World!";
    char destination[50];
    int i = 0;
    
    // 手动复制，直到遇到空字符
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // 添加字符串结束符
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n", destination);
    printf("\n");
}

// 方法4：使用指针手动实现字符串复制
void manual_string_copy_with_pointers() {
    printf("=== 方法4: 使用指针手动实现字符串复制 ===\n");
    char source[] = "Hello, World!";
    char destination[50];
    char *src_ptr = source;
    char *dest_ptr = destination;
    
    // 使用指针复制
    while (*src_ptr != '\0') {
        *dest_ptr = *src_ptr;
        src_ptr++;
        dest_ptr++;
    }
    *dest_ptr = '\0'; // 添加字符串结束符
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n", destination);
    printf("\n");
}

// 方法5：安全的字符串复制（带长度检查）
void safe_string_copy() {
    printf("=== 方法5: 安全的字符串复制（带长度检查） ===\n");
    char source[] = "This is a very long string that might overflow if we're not careful";
    char destination[30];
    int max_copy_length = sizeof(destination) - 1; // 预留一个字符给空字符
    
    int i;
    for (i = 0; i < max_copy_length && source[i] != '\0'; i++) {
        destination[i] = source[i];
    }
    destination[i] = '\0'; // 确保字符串以null结尾
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s (只复制了前%d个字符)\n", destination, max_copy_length);
    printf("\n");
}

// 方法6：自定义字符串复制函数
char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest; // 保存目标字符串的起始地址
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // 添加字符串结束符
    return original_dest; // 返回目标字符串的起始地址
}

void custom_string_copy_function() {
    printf("=== 方法6: 自定义字符串复制函数 ===\n");
    char source[] = "Hello from custom function!";
    char destination[50];
    
    my_strcpy(destination, source);
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n", destination);
    printf("\n");
}

int main() {
    printf("C语言字符串复制操作示例\n");
    printf("=========================\n\n");
    
    // 演示各种字符串复制方法
    string_copy_using_strcpy();
    string_copy_using_strncpy();
    manual_string_copy();
    manual_string_copy_with_pointers();
    safe_string_copy();
    custom_string_copy_function();
    
    printf("=== 字符串复制注意事项 ===\n");
    printf("1. 始终确保目标缓冲区足够大\n");
    printf("2. 不要忘记字符串结束符'\\0'\n");
    printf("3. 使用strncpy比strcpy更安全，可以防止缓冲区溢出\n");
    printf("4. 手动实现时要检查源字符串是否为空\n");
    
    return 0;
}