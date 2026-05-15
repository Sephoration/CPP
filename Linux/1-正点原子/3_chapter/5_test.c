#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
    int fd1; //文件描述符
    int fd2;

    fd1 = open("test.txt", O_WRONLY | O_APPEND | O_TRUNC);
    if (fd1 == -1) {
        printf("open error\n");
        return 1;
    }

    fd2 = open ("test.txt", O_WRONLY | O_APPEND );
    if  (fd2 == -1 ){
        printf("open error\n");
        close (fd1);
        return 1;
    }

    write (fd1 ,"Hello World!",12);
    write (fd2,"ABCD EFAG",9);

    close (fd1);
    close (fd2);

    return 0;

}

