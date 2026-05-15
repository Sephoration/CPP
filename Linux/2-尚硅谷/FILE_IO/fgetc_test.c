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
    FILE *__stream : 文件指针
    返回值： 成功返回读取的字符，失败返回EOF
    int fgetc (FILE *__stream);
    */
    char c = fgetc(fp); //读取一个字符
    while ( c != EOF )  //只要没有读到文件结尾，就一直读取
    {
        printf ("%c", c); //输出读取的字符
        c = fgetc(fp);    //继续读取下一个字符
    }
    printf ("\n");
    

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

    return 0;    
}