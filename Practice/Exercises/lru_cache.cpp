#include <cassert>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

// 链表头部是最近访问的条目，哈希表保存链表迭代器。
template <class Key, class Value>
class LruCache {
    using Entries = std::list<std::pair<Key, Value>>;
    std::size_t capacity_;
    Entries entries_;
    std::unordered_map<Key, typename Entries::iterator> index_;
public:
    explicit LruCache(std::size_t capacity) : capacity_(capacity) {}
    // 迭代器属于当前链表，禁止默认复制；需要复制时应重建索引。
    LruCache(const LruCache&) = delete;
    LruCache& operator=(const LruCache&) = delete;
    std::optional<Value> get(const Key& key) {
        auto it = index_.find(key);
        if (it == index_.end()) return std::nullopt;
        entries_.splice(entries_.begin(), entries_, it->second);
        return it->second->second;
    }
    void put(const Key& key, Value value) {
        auto it = index_.find(key);
        if (it != index_.end()) {
            it->second->second = std::move(value);
            entries_.splice(entries_.begin(), entries_, it->second);
            return;
        }
        if (!capacity_) return;
        entries_.emplace_front(key, std::move(value));
        try { index_.emplace(entries_.front().first, entries_.begin()); }
        catch (...) { entries_.pop_front(); throw; }
        if (entries_.size() > capacity_) {
            index_.erase(entries_.back().first);
            entries_.pop_back();
        }
    }
    std::size_t size() const { return entries_.size(); }
};
int main() {
    LruCache<int, std::string> cache(2);
    cache.put(1, "one"); cache.put(2, "two");
    assert(cache.get(1) == "one");
    cache.put(3, "three");
    assert(!cache.get(2)); assert(cache.get(3) == "three");
    cache.put(1, "ONE"); assert(cache.get(1) == "ONE");
    LruCache<int, int> empty(0); empty.put(1, 1); assert(empty.size() == 0);
    std::cout << "LRU: 访问顺序、淘汰、更新和零容量检查通过\n";
}
