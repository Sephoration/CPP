#include <stdio.h>

int main(int argc,char const *argv[]) {

    /*
   const char *__restrict __filename  #字符串表示打开文件
   const char *__restrict __modes     #字符串表示打开文件的模式
        1. r:以只读方式打开文件,文件必须存在
        2. w:以只写方式打开文件,文件不存在则创建,存在
        3. a:以追加方式打开文件,文件不存在则创建,存在
        4. r+:以读写方式打开文件,文件必须存在
        5. w+:以读写方式打开文件,文件不存在则创建,存在则清空
        6. a+:以读写方式打开文件,文件不存在则
        7. b:以二进制方式打开文件
        8. t:以文本方式打开文件(默认)
        9. +:读写方式
    return: FILE * 结构体指针，表示一个文件
        报错返回NULL
    FILE *fopen (const char *__restrict __filename , const char *__restrict __modes)
    */

    char *filename = "test.txt";
    char *modes = "w+";
    FILE *fp = fopen(filename,modes);
    if(fp == NULL) {
        perror("fopen");
        return -1;
    }
    printf("fopen 成功打开！\n");

    /* 
    FILE *__stream #文件指针
    return: 成功返回0，失败返回EOF
    int fclose (FILE *__stream);
    */
   int result = fclose(fp);  // 关闭文件
    if(result == EOF) {
         perror("fclose");
         return -1;
    }
    else {
        printf("fclose 成功关闭！\n");
    }
 
}