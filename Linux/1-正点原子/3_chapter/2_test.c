
#include <sys/types.h>   // open、lseek、write、close 相关类型
#include <sys/stat.h>    // 文件权限相关
#include <fcntl.h>       // open 函数和文件操作标志
#include <unistd.h>      // lseek、write、close
#include <stdio.h>       // printf、perror
#include <string.h>      // memset
#include <stdlib.h>      // exit

int main(void)
{
    int fd;         // 文件描述符
    int ret;        // 返回值
    char buf[4096]; // 写入缓冲区

    // 初始化缓冲区为0（可选）
    memset(buf, 0, sizeof(buf));

    // 以可读可写方式创建新文件，若存在则清空，权限0644
    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open error"); // 打开失败提示
        exit(1);
    }

    // 文件指针移动到4096字节处，为制造稀疏文件
    ret = lseek(fd, 4096, SEEK_SET);
    if (ret == -1) {
        perror("lseek error");
        close(fd);
        exit(1);
    }

    // 向文件当前位置写入4096字节（全0）
    ret = write(fd, buf, 4096);
    if (ret == -1) {
        perror("write error");
        close(fd);
        exit(1);
    }

    printf("write %d bytes\n", ret); // 打印实际写入字节数
    close(fd); // 关闭文件

    return 0;
}



