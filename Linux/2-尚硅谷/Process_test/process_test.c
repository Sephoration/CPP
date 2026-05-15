#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num = 0;

 int main (int argc, char *argv[]){
    
    __pid_t pid = fork();
    if (pid < 0){
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid ==0)
    {
        //子进程
        num = 1;
        printf("Child process: PID = %d, num = %d\n", getpid(), num);
    }
    else 
    {
        //父进程    
        sleep(1);
        printf("Parent process: PID = %d, num = %d\n", getpid(), num);
    }
    
    return 0;
 }

   
