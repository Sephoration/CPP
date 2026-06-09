#include <iostream>
#include <mutex>

// 单例模式练习
class Singleton {
    static Singleton* instance_;
    static std::mutex mtx_;
    int data_ = 0;
    Singleton() = default;
public:
    static Singleton* getInstance() {
        if (instance_ == nullptr) {
            std::lock_guard<std::mutex> lock(mtx_);
            if (instance_ == nullptr) {
                instance_ = new Singleton();
            }
        }
        return instance_;
    }
    void setData(int d) { data_ = d; }
    int getData() const { return data_; }
};

Singleton* Singleton::instance_ = nullptr;
std::mutex Singleton::mtx_;

int main() {
    Singleton::getInstance()->setData(42);
    std::cout << "Data: " << Singleton::getInstance()->getData() << std::endl;
    return 0;
}
