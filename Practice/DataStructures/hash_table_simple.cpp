#include <iostream>
#include <vector>
#include <list>
#include <string>

// 简单哈希表练习
class HashTable {
    static const size_t BUCKET_COUNT = 16;
    std::vector<std::list<std::pair<std::string, int>>> buckets_;

    size_t hash(const std::string& key) const {
        size_t h = 0;
        for (char c : key) {
            h = h * 31 + static_cast<size_t>(c);
        }
        return h % BUCKET_COUNT;
    }

public:
    HashTable() : buckets_(BUCKET_COUNT) {}

    void insert(const std::string& key, int value) {
        size_t idx = hash(key);
        for (auto& p : buckets_[idx]) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        buckets_[idx].push_back({key, value});
    }

    bool find(const std::string& key, int& value) const {
        size_t idx = hash(key);
        for (const auto& p : buckets_[idx]) {
            if (p.first == key) {
                value = p.second;
                return true;
            }
        }
        return false;
    }
};

int main() {
    HashTable ht;
    ht.insert("apple", 100);
    ht.insert("banana", 200);
    int val;
    if (ht.find("apple", val)) {
        std::cout << "apple = " << val << std::endl;
    }
    return 0;
}
