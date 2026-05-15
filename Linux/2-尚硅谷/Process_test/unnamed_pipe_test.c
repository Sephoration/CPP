#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char const *argv[]) {

    pid_t cpid ;
    int pipefd[2];

    //将程序传递进来的第一个命令行参数，通过管道传输到子进程
    if (argc!=2){
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //创建管道
    if (pipe(pipefd) == -1){
        perror("创建管道失败！");
        exit(EXIT_FAILURE);
    }

    //复制父子进程
    cpid = fork();
    if (cpid == -1){
        perror("邀请新学员失败！");
        exit(EXIT_FAILURE); 
    }

    if(cpid == 0 ){
        //子进程，读取管道的数据，打印到控制台
        close(pipefd[1]); //关闭写端
        
        char buf;
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]); //读完后关闭读端
        exit(EXIT_SUCCESS);    
    }
    else {
        //父进程，向管道写入数据
        close(pipefd[0]); //关闭读端
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]); //写完后关闭写端
        waitpid(cpid, NULL, 0); //等待子进程结束
        exit(EXIT_SUCCESS);
    }
}
