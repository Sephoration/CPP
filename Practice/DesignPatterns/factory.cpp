#include <iostream>
#include <memory>
#include <string>

// 工厂模式练习
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

class ConcreteProductA : public Product {
public:
    void use() override {
        std::cout << "Using Product A" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void use() override {
        std::cout << "Using Product B" << std::endl;
    }
};

class Factory {
public:
    static std::unique_ptr<Product> create(const std::string& type) {
        if (type == "A") return std::make_unique<ConcreteProductA>();
        if (type == "B") return std::make_unique<ConcreteProductB>();
        return nullptr;
    }
};

int main() {
    auto a = Factory::create("A");
    auto b = Factory::create("B");
    if (a) a->use();
    if (b) b->use();
    return 0;
}
