#include <stdio.h>

//输入两个数，输出它们的和、差、积、商、余数
int main() {

    int a, b;
    printf("输入两个整数");
    scanf("%d %d", &a, &b);

    printf("和: %d\n", a + b);
    printf("差: %d\n", a - b);
    printf("积: %d\n", a * b);
    if (b != 0) {
        printf("商: %d\n", a / b);
        printf("余数: %d\n", a % b);
    } else {
        printf("除数不能为零，无法计算商和余数。\n");
    }
    
    return 0;
}