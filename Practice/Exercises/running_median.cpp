#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

// 两个堆分别维护较小和较大的数据；前者最多多一个元素。
class RunningMedian {
    std::priority_queue<int> lower_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> upper_;
public:
    void add(int value) {
        if (lower_.empty() || value <= lower_.top()) lower_.push(value);
        else upper_.push(value);
        if (lower_.size() > upper_.size() + 1) { upper_.push(lower_.top()); lower_.pop(); }
        else if (upper_.size() > lower_.size()) { lower_.push(upper_.top()); upper_.pop(); }
    }
    double median() const {
        if (lower_.empty()) throw std::logic_error("no values");
        if (lower_.size() != upper_.size()) return lower_.top();
        return (static_cast<double>(lower_.top()) + static_cast<double>(upper_.top())) / 2.0;
    }
};
int main() {
    RunningMedian values;
    values.add(8); values.add(2); values.add(5); assert(values.median() == 5);
    values.add(10); assert(values.median() == 6.5);
    values.add(-3); assert(values.median() == 5);
    std::cout << "中位数: " << values.median() << '\n';
}
