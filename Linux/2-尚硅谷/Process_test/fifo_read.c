#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


int main (int argc, char const *argv[]){

    //创建路径
    int fd;
    char *pipe_path = "/tmp/myfifo";

    // /*
    // 有名管道
    // const char *__path  有名管道绑定的文件路径
    // __mode_t __mode     有名管道绑定文件的权限
    // int mkfifo (const char *__path, __mode_t __mode)
    // */
    // if (mkfifo(pipe_path,0664) != 0 ){
    //     perror( "mkfifo");
    //     exit(EXIT_FAILURE);
    // }

    fd = open (pipe_path, O_RDONLY );
    
    if (fd == -1 )
    {
        perror ("open");
        exit(EXIT_FAILURE);
    }

    char buf [100];
    ssize_t read_num;
    //读取管道数据写入到控制台中
    while ( (read_num = read (fd ,buf ,100 )) > 0 )
    {
        write (STDERR_FILENO, buf, read_num);
    }
        
    if (read_num < 0 )
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("接收管道数据完成，进程终止\n");
    close(fd);

}


