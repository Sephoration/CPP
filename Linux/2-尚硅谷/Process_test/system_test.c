#include <stdio.h>
#include <stdlib.h>

int main (int argc , char const *argv[])
{
    //使用标准库函数创建子进程
    /*
    const char *__command  #使用Linux命令创建
    return 成功返回0，失败返回失败编号
    int system (const char *__command)
    */
    int sysR  = system("ping -c 100 www.baidu.com");
    if (sysR != 0 )
    {
        perror("system");
        exit(EXIT_FAILURE);
    }
}