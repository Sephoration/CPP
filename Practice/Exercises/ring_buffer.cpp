#include <cassert>
#include <cstddef>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

// 固定容量的循环缓冲区：满时拒绝写入，读取遵循先进先出。
template<class T> class RingBuffer {
    std::vector<std::optional<T>> storage_;
    std::size_t head_ = 0, size_ = 0;
public:
    explicit RingBuffer(std::size_t capacity) : storage_(capacity) {
        if (!capacity) throw std::invalid_argument("capacity must be positive");
    }
    bool push(T value) {
        if (size_ == storage_.size()) return false;
        storage_[(head_ + size_) % storage_.size()].emplace(std::move(value));
        ++size_; return true;
    }
    std::optional<T> pop() {
        if (!size_) return std::nullopt;
        auto value = std::move(storage_[head_]); storage_[head_].reset();
        head_ = (head_ + 1) % storage_.size(); --size_; return value;
    }
    std::size_t size() const { return size_; }
    std::size_t capacity() const { return storage_.size(); }
};
int main() {
    RingBuffer<int> buffer(3);
    if (!buffer.push(10) || !buffer.push(20) || !buffer.push(30) || buffer.push(40)) return 1;
    if (buffer.pop() != 10 || !buffer.push(40)) return 1;
    if (buffer.pop() != 20 || buffer.pop() != 30 || buffer.pop() != 40 || buffer.pop()) return 1;
    std::cout << "循环缓冲区测试通过\n";
}
