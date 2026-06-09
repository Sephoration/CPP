#include <iostream>
#include <vector>

// 快速排序练习
void quickSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) --j;
        while (i < j && arr[i] <= pivot) ++i;
        if (i < j) std::swap(arr[i], arr[j]);
    }
    arr[left] = arr[i];
    arr[i] = pivot;
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

int main() {
    std::vector<int> data = {3, 6, 8, 10, 1, 2, 1};
    quickSort(data, 0, static_cast<int>(data.size()) - 1);
    for (int x : data) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
