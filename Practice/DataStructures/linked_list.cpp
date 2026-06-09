#include <iostream>
#include <memory>

// 单链表练习
template<typename T>
class LinkedList {
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        Node(T d) : data(d), next(nullptr) {}
    };
    std::shared_ptr<Node> head_;
    size_t size_ = 0;
public:
    void push_front(const T& value) {
        auto node = std::make_shared<Node>(value);
        node->next = head_;
        head_ = node;
        ++size_;
    }
    void pop_front() {
        if (head_) {
            head_ = head_->next;
            --size_;
        }
    }
    void print() const {
        auto cur = head_;
        while (cur) {
            std::cout << cur->data << " -> ";
            cur = cur->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    size_t size() const { return size_; }
};

int main() {
    LinkedList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.print();
    list.pop_front();
    list.print();
    return 0;
}
