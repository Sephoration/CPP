#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// 文件IO练习
int main() {
    const char* filename = "test_data.txt";

    {
        std::ofstream ofs(filename);
        if (!ofs) {
            std::cerr << "Failed to open file for writing" << std::endl;
            return 1;
        }
        for (int i = 1; i <= 5; ++i) {
            ofs << "Line " << i << std::endl;
        }
    }

    {
        std::ifstream ifs(filename);
        if (!ifs) {
            std::cerr << "Failed to open file for reading" << std::endl;
            return 1;
        }
        std::string line;
        while (std::getline(ifs, line)) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}
