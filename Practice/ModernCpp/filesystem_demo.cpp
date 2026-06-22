#include <iostream>
#include <filesystem>

// filesystem 练习
namespace fs = std::filesystem;

void printFileInfo(const fs::path& p) {
    if (!fs::exists(p)) {
        std::cout << p << " 不存在" << std::endl;
        return;
    }
    std::cout << "文件名: " << p.filename() << std::endl;
    std::cout << "大小: " << fs::file_size(p) << " bytes" << std::endl;
    std::cout << "扩展名: " << p.extension() << std::endl;
}

void listDirectory(const fs::path& dir) {
    std::cout << "\n目录 " << dir << " 的内容:" << std::endl;
    for (const auto& entry : fs::directory_iterator(dir)) {
        auto ft = entry.is_directory() ? "[DIR]" : "[FILE]";
        std::cout << ft << " " << entry.path().filename() << std::endl;
    }
}

int main() {
    // 路径操作
    std::cout << "=== 路径操作 ===" << std::endl;
    fs::path p = "C:/A_GitCode/CPP/readme.md";
    std::cout << "根目录: " << p.root_path() << std::endl;
    std::cout << "父目录: " << p.parent_path() << std::endl;

    // 文件信息
    std::cout << "\n=== 文件信息 ===" << std::endl;
    printFileInfo(p);

    // 遍历目录
    listDirectory("C:/A_GitCode/CPP/Practice");

    // 创建/删除目录
    fs::path tmp = "C:/A_GitCode/CPP/tmp_test";
    fs::create_directory(tmp);
    std::cout << "\n创建临时目录: " << (fs::exists(tmp) ? "成功" : "失败") << std::endl;
    fs::remove(tmp);
    std::cout << "删除临时目录: " << (!fs::exists(tmp) ? "成功" : "失败") << std::endl;

    return 0;
}
