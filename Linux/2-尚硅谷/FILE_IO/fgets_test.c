#include <stdio.h>

int main (int argc, char *argv[])
{
    //打开文件
    FILE *fp = fopen ("test.txt", "r");
    if (fp == NULL)
    {
        perror ("fopen 失败！");
        return -1;
    }
    else
    {
        printf ("fopen 成功！\n");
    }


    //读取文件内容
    /*
    char *__restrict __s  #接收读取到的字符串
    int __n               #读取的最大字符数（包含字符串结束符\0）
    FILE *__restrict __stream #文件指针
    return char*              #读取成功返回s，读取失败返回NULL
    char * fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
    */
    char  buf[100] = {0};
    while (fgets (buf, sizeof(buf), fp) != NULL)
    {
        printf ("读取到的内容：%s", buf);
    }
 
  
    // 关闭文件
    int close_ret = fclose (fp);
    if (close_ret == 0)
    {
        printf ("fclose 成功！\n");
    }
    else
    {
        perror ("fclose 失败！");   
    }
}