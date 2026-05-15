#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   /* 新增：strlen 需要 */

int main ()
{
    //打开文件
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        perror("打开文件失败");
        _exit(1);
    }


    const char *text = "Hello syscall!\n";
    char buffer[100]; //用于存放数据
    ssize_t bytes_read;


    //写入数据
    /*
    int __fd         #文件描述符
    void *__buf      #指向存放数据的缓冲区
    size_t __nbytes  #要读取的字节数
    returns          #成功返回 ssize_t ,失败返回-1，同时设置全局变量errno
    read (int __fd, void *__buf, size_t __nbytes)
    */
    ssize_t bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("已写入 %zd 字节\n", bytes_written);


    /* 3. 把文件偏移重新移到开头，准备读 */
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }


    /* read 返回 ssize_t：成功=实际读取字节数，读到EOF=0，失败=-1 */
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';          /* 手动补字符串结束符 */
    printf("读到 %zd 字节：%s", bytes_read, buffer);


    /* 5. 关闭文件描述符 */
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}