#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc , char *argv[])
{
    if (argc < 2){
        printf("参数不够，上不了二楼\n");
        return 1 ;
    }

    printf ("我是%s %d,父进程%d，我跟佳佳一起上二楼啦！\n", argv[1] ,getpid(),getppid());
    sleep(100);
    return 0;
}

//getpid  子进程 
//grippid 父进程