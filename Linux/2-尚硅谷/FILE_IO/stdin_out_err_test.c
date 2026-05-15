#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
    char *ch = malloc (100);               

    //从标准输入中读取数据
    fgets(ch , 100 ,stdin);
    printf("你输入的数据是: %s\n", ch);   

    //标准输出，不会换行
    fputs(ch, stdout);

    //标准错误输出
    fputs(ch, stderr);


}
