#include <stdio.h>

int main () {
    int a;
    int b;

    printf("请输入两个整数：");
    scanf("%d %d", &a, &b);

    if ( (a%2 ==0) && (b%2 ==0))
    {
        printf( "a和b都是偶数 他们的平均值是%d\n", (a+b/2) );
    }
    else 
    {
        printf("最大值是：%d\n", (a > b) ? a : b);
    }

}