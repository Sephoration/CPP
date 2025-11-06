#include <stdio.h>

int main() {

    int a ;
    printf("输入多少秒: ");
    scanf("%d", &a);

    printf("转换为:\n");
    printf("分钟: %d\n", a / 60);
    printf("小时: %d\n", a / 3600);
    printf("天: %d\n", a / 86400); 

    //输出几小时几分钟几秒
    printf("具体为: %d小时 %d分钟 %d秒\n", a / 3600,
         (a % 3600) / 60,
          a % 60);
}