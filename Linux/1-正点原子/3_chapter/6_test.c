#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (void) {

    int fd1 ,fd2 ;
    int ret;
    char buf[12];

    fd1 = open ("./test.txt",O_RDWR |  O_TRUNC);
    if (fd1 == -1) {
        printf("open error\n");
        return 1;
    }


    fd2  = dup (fd1);
    if (fd2 == -1) {
        printf("dup error\n");
        close (fd1);
        return 1;      
    }

    ret = write (fd2 ,"Hello World!",12);
    if (ret == -1) {
        printf("write error\n");
        close (fd1);
        close (fd2);
        return 1;      
    }

    lseek (fd1 ,0,SEEK_SET);

    ret = read(fd1, buf , 11);
    if (ret == -1) {
        printf("read error\n");
        close (fd1);
        close (fd2);
        return 1;      
    }

    printf ("read %d bytes : %s\n",ret,buf);
    close (fd1);
    close (fd2);    
    return 0;

}