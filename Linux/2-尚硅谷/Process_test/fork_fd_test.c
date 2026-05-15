# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>    
# include <sys/types.h>


int main (int argc,char *argv[]){
    
    //fork之前
    //打开一个文件
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd < 0){
        perror("Open file failed");
        exit(EXIT_FAILURE); 
    }

    char buffer[100]; // 用于读写的缓冲区

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process    
    }else
    {
        // Parent process
        sleep(1); // 确保子进程先运行
        strcpy(buffer, "Hello from parent process!\n");
    }
    
    //父子进程都执行的代码
    ssize_t bytes_write = write(fd, buffer, strlen(buffer));
    if (bytes_write < 0){
        perror("Write to file failed");
        close(fd);
        exit(EXIT_FAILURE); 
    }

    if (pid == 0){
        printf("Child process wrote to file.\n");
    }else{
        printf("Parent process wrote to file.\n");
    }

}