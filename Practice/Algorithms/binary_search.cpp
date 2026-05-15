#include <iostream>
#include <vector>

// 二分查找练习
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    std::vector<int> data = {1, 3, 5, 7, 9, 11, 13};
    int idx = binarySearch(data, 7);
    std::cout << "Index of 7: " << idx << std::endl;
    return 0;
}
