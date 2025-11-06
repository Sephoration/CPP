/*
输入英文句子，统计每个英文字母出现次数
不区分大小写，只统计英文字母
*/

#include <iostream>
using namespace std;

int main()
{
    const int maxsize = 26;  // 定义常量，表示英文字母总数
    char sentence[1000];     // 定义字符数组，用于存储用户输入的句子

    cout << "请输入一个英文句子：" << endl;
    cin.getline(sentence, 1000); // 读取一行包括空格的字符串，最多999个字符

    int count[26] = {0}; // 初始化字母计数数组，所有元素初始化为0
    // 数组索引：0对应a/A, 1对应b/B, ..., 25对应z/Z
    
    int idx = 0; // 用于存储字母在计数数组中的索引位置

    // 遍历字符串中的每个字符，直到遇到字符串结束符'\0'
    for (int i = 0; sentence[i] != '\0'; i++)
    {
        char c = sentence[i]; // 获取当前字符

        // 判断字符类型并计算对应的数组索引
        if (c >= 'a' && c <= 'z') 
        {
            // 小写字母：'a'->0, 'b'->1, ..., 'z'->25
            idx = c - 'a';
        }
        else if (c >= 'A' && c <= 'Z') 
        {
            // 大写字母：'A'->0, 'B'->1, ..., 'Z'->25
            idx = c - 'A';
        }
        else 
        {
            // 如果不是英文字母，跳过当前字符，继续处理下一个字符
            continue;
        }
        
        // 对应字母的计数器加1
        count[idx]++;
    }

    // 输出统计结果
    for (int i = 0; i < 26; i++)
    {
        // 只输出出现次数不为0的字母
        if (count[i] != 0)
        {
            // 将索引转换为对应的小写字母并输出统计结果
            cout << char(i + 'a') << " : " << count[i] << endl;
        }
    }

    return 0; // 程序正常结束
}