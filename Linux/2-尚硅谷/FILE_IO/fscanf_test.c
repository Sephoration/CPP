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


    /*
    FILE *__restrict __stream       # 文件流指针
    const char *__restrict __format # 格式字符串(固定格式接受)
    ...                             # 可变参数列表
    return value: 成功读取的字段个数，失败返回0，报错失败返回EOF
    int fscanf (FILE *__restrict __stream,
		const char *__restrict __format, ...) 
    */
    char name[20];
    int age;
    char wifep[20];
    int ret_fscanf = fscanf (fp, "%s %d %s", name, &age, wifep);
    if (ret_fscanf == EOF)
    {
        perror ("fscanf 失败！");
    }
    else
    {
        printf ("fscanf 成功！\n");
        printf ("name = %s, age = %d, wifep = %s\n", name, age, wifep);
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

    return 0;    
}