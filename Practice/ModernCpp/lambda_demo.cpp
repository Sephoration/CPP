#include <iostream>
#include <vector>
#include <algorithm>

// Lambda 表达式练习
int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    auto square = [](int x) { return x * x; };
    std::cout << "3^2 = " << square(3) << std::endl;

    std::for_each(nums.begin(), nums.end(), [](int x) {
        std::cout << x << " ";
    });
    std::cout << std::endl;

    int threshold = 3;
    auto it = std::find_if(nums.begin(), nums.end(), [threshold](int x) {
        return x > threshold;
    });
    if (it != nums.end()) {
        std::cout << "First > " << threshold << ": " << *it << std::endl;
    }

    return 0;
}
