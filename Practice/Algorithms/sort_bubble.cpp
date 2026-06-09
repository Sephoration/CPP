#include <iostream>
#include <vector>
#include <algorithm>

// 冒泡排序练习
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(data);
    for (int x : data) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
