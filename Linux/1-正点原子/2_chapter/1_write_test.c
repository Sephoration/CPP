#include <sys/types.h>  //open函数的头文件
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //close、write函数的头文件
#include <stdio.h>

int main (void){
    int fd;
    int ret;


    fd = open ("./test.txt", O_WRONLY | O_CREAT | O_EXCL, 0644); //第三个参数是权限
    //检查open函数的返回值
    if (-1 == fd ){
        printf  ("open error\n");
        return 1;
    }
    printf ("open success！");


    ret =  write( fd, "hello World", 11); //写入10个字节
    if (-1 == ret){
        printf ("write error\n");
        close(fd);
        return 1;
    }
    printf ("write %d bytes OK!\n", ret );

    close(fd);
    return 0;
}
