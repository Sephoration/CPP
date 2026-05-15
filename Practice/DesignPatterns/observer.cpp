#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 观察者模式练习
class Observer {
public:
    virtual void update(const std::string& msg) = 0;
    virtual ~Observer() = default;
};

class Subject {
    std::vector<Observer*> observers_;
    std::string state_;
public:
    void attach(Observer* obs) {
        observers_.push_back(obs);
    }
    void detach(Observer* obs) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), obs), observers_.end());
    }
    void notify() {
        for (auto* obs : observers_) {
            obs->update(state_);
        }
    }
    void setState(const std::string& state) {
        state_ = state;
        notify();
    }
};

class ConcreteObserver : public Observer {
    std::string name_;
public:
    explicit ConcreteObserver(const std::string& name) : name_(name) {}
    void update(const std::string& msg) override {
        std::cout << "[" << name_ << "] received: " << msg << std::endl;
    }
};

int main() {
    Subject subject;
    ConcreteObserver o1("Observer1");
    ConcreteObserver o2("Observer2");
    subject.attach(&o1);
    subject.attach(&o2);
    subject.setState("New Event!");
    return 0;
}
