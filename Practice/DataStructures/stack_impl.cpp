#include <iostream>
#include <vector>
#include <stdexcept>

// 栈的数组实现练习
template<typename T>
class Stack {
    std::vector<T> data_;
public:
    void push(const T& value) {
        data_.push_back(value);
    }
    void pop() {
        if (data_.empty()) throw std::runtime_error("Stack empty");
        data_.pop_back();
    }
    T& top() {
        if (data_.empty()) throw std::runtime_error("Stack empty");
        return data_.back();
    }
    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }
};

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
    return 0;
}
