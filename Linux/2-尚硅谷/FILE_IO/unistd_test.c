#include <unistd.h>
#include <fcntl.h>

int main (){


    //打开文件
    /*
    const char *__path  #文件路径
    int __oflag         #文件打开方式
        1. O_RDONLY  只读方式打开
        2. O_WRONLY  只写方式打开
        3. O_RDWR    读写方式打开
        4. O_APPEND  追加方式打开
        5. O_CREAT   如果文件不存在则创建该文件
        6. O_TRUNC   如果文件存在则将该文件长度截为0
        7. O_EXCL    如果与O_CREAT一起使用,则当文件存在时,返回错误
    mode_t mode  #文件权限,只有在创建文件时才有用
    returns      #文件描述符,失败返回-1，同时设置全局变量errno
    open (const char *__path, int __oflag, ...)
    */
   int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
         perror("打开文件失败");
         return 1;
    }
   
}
