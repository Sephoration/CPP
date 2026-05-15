#include <stdio.h>

int main (int argc, char **argv) //外部传参个数，数组(字符串)
{ 
    printf("argc = %d\n", argc); //打印外部传参个数
    for (int i = 0 ;i < argc ; i++) //遍历外部传参数组
    {
        printf("argv[%d] = %s\n", i, argv[i]); //打印外部传参数组
    }
    return 0;
}
 
