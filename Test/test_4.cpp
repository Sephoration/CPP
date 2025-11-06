/*
输入英文句子，统计单词数目。单词以空格分隔
*/

#include <stdio.h>

int main() {

    int word_count = 0;

    printf("请输入一个英文句子：\n");
    char ch[1000];
    scanf(" %[^\n]s", ch); //读取一行包括空格的字符串

    //循环读取
    for (int i = 0; i < 1000; i++) {
       if ( ch[i] == ' ' ) { word_count++;  }
       else if ( ch[i] == '\n' ) { break;  }
       else { continue; }
    }

    printf("单词数目为：%d\n", word_count + 1); //最后一个单词后没有空格，所以加1

}