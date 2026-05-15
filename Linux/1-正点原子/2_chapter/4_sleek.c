/*
实现一个文件拷贝功能,给定一个源文件,读取源文件中的所有数据,
将其写入到另一个目标文件中,效果:
./app "src file" "farget file"
给定一个文件,计算它的大小并打印出来
*/

#include <sys/types.h>  // open、read、write、close 相关类型
#include <sys/stat.h>    // 文件权限相关
#include <fcntl.h>       // open 函数和文件操作标志
#include <unistd.h>      // read、write、close
#include <stdio.h>       // printf

int main(int argc, char *argv[])
{
    // 定义源文件和目标文件的文件描述符
    int fd_src, fd_dst;
    // 读写缓冲区
    char buf[1024];
    // 每次读取的字节数
    ssize_t nread;

    // 检查参数个数，必须有程序名+2个参数
    if (argc != 3) {
        printf("用法: %s <src_file> <dst_file>\n", argv[0]);
        return 1;
    }

    // 只读方式打开源文件
    fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1) {
        printf("open src error\n"); // 打开失败提示
        return 1;   
    }

    // 只写方式创建/打开目标文件，若存在则清空，权限0644
    fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dst == -1) {
        printf("open dst error\n"); // 打开失败提示
        close(fd_src);
        return 1;
    }

    // 循环读取源文件内容并写入目标文件
    while ((nread = read(fd_src, buf, sizeof(buf))) > 0) {
        // 写入目标文件，返回值不等于nread表示写入出错
        if (write(fd_dst, buf, nread) != nread) {
            printf("write error\n");
            close(fd_src);
            close(fd_dst);
            return 1;
        }
    }
    // 读取出错时提示
    if (nread < 0) {
        printf("read error\n");
    }

    // 关闭文件
    close(fd_src);
    close(fd_dst);
    printf("copy finished!\n"); // 拷贝完成提示
    return 0;
}