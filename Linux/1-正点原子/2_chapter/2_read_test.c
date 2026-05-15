#include <sys/types.h>  //open函数的头文件
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //close、write函数的头文件
#include <stdio.h>

int main (void)
    {
        int fd;
        char buf[125] = {0};
        int ret;
      
        fd = open ("./test.txt", O_RDONLY ); 
        if (-1 == fd ){
            printf  ("open error\n");
            return 1;
        }

        printf ("open success\n");

        ret = read(fd ,buf,11);
        if (-1 == ret){
            printf ("read error\n");
            close(fd);
            return 1;
        }

        printf ("read %d bytes %s \n", ret ,buf );
        close(fd);  
        return 0;
    }