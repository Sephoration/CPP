#include <cassert>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

class UnionFind {
    std::vector<int> parent_, size_;
    int components_;
public:
    explicit UnionFind(int n) : components_(n) {
        if (n < 0) throw std::invalid_argument("negative size");
        parent_.resize(static_cast<std::size_t>(n)); size_.assign(static_cast<std::size_t>(n), 1);
        std::iota(parent_.begin(), parent_.end(), 0);
    }
    int find(int x) {
        if (x < 0 || static_cast<std::size_t>(x) >= parent_.size()) throw std::out_of_range("index");
        int root = x;
        while (parent_[root] != root) root = parent_[root];
        while (parent_[x] != x) { int next = parent_[x]; parent_[x] = root; x = next; }
        return root;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b); if (a == b) return false;
        if (size_[a] < size_[b]) std::swap(a, b);
        parent_[b] = a; size_[a] += size_[b]; --components_; return true;
    }
    int component_size(int x) { return size_[find(x)]; }
    int components() const { return components_; }
};
int main() {
    UnionFind groups(6);
    groups.unite(0, 1); groups.unite(1, 2); groups.unite(3, 4);
    assert(groups.find(0) == groups.find(2));
    assert(groups.find(0) != groups.find(3));
    assert(groups.component_size(1) == 3 && groups.components() == 3);
    std::cout << "连通分量: " << groups.components() << '\n';
}
