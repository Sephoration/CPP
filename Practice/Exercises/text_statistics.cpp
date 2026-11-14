#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// 统计 ASCII 单词；非 ASCII 字节作为分隔符，不将其解释为汉字词语。
int main(int argc, char** argv) {
    if (argc != 2) { std::cerr << "用法: " << argv[0] << " 文本文件\n"; return 2; }
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) { std::cerr << "无法打开文件: " << argv[1] << '\n'; return 1; }
    std::map<std::string, std::size_t> counts;
    std::string word; std::size_t bytes = 0, newlines = 0; char c;
    auto flush = [&] { if (!word.empty()) { ++counts[word]; word.clear(); } };
    while (file.get(c)) {
        ++bytes; if (c == '\n') ++newlines;
        const auto byte = static_cast<unsigned char>(c);
        if (byte < 128 && std::isalnum(byte)) word += static_cast<char>(std::tolower(byte));
        else flush();
    }
    if (file.bad()) { std::cerr << "读取失败\n"; return 1; }
    flush();
    std::vector<std::pair<std::string, std::size_t>> ranking(counts.begin(), counts.end());
    std::sort(ranking.begin(), ranking.end(), [](const auto& a, const auto& b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    });
    std::cout << "字节: " << bytes << "，换行符: " << newlines << "，不同单词: " << counts.size() << '\n';
    for (std::size_t i = 0; i < std::min<std::size_t>(10, ranking.size()); ++i)
        std::cout << ranking[i].first << ": " << ranking[i].second << '\n';
}
