#include <iostream>
#include <vector>
#include <string>

// 移动语义练习
class Buffer {
    size_t size_;
    int* data_;
public:
    explicit Buffer(size_t size) : size_(size), data_(new int[size]) {
        std::cout << "Constructor" << std::endl;
    }
    ~Buffer() {
        delete[] data_;
        std::cout << "Destructor" << std::endl;
    }
    Buffer(const Buffer& other) : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Copy Constructor" << std::endl;
    }
    Buffer(Buffer&& other) noexcept : size_(other.size_), data_(other.data_) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "Move Constructor" << std::endl;
    }
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        std::cout << "Move Assignment" << std::endl;
        return *this;
    }
};

Buffer createBuffer(size_t size) {
    return Buffer(size);
}

int main() {
    Buffer a(100);
    Buffer b = std::move(a);
    Buffer c = createBuffer(200);
    return 0;
}
