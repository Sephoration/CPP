#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


//int main (void)

int main (int argc , char *argv[]) {

    printf("父进程%d\n", getpid());
    //使用fork函数创建子进程
    /*
    不需要传参  
    return值：int
        -1  创建失败
         0  子进程
        >0  父进程，返回值是子进程的PID
    */
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return -1;
    } else if (pid == 0) {
        //子进程
        printf("子进程%d\n", getpid());
    } else {
        //父进程
        printf("父进程%d, 子进程%d\n", getpid(), pid);
    }

}
