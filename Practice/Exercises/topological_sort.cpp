#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

// Kahn 算法：优先输出编号小的节点，输出不足时存在环。
std::vector<int> topological_sort(const std::vector<std::vector<int>>& graph) {
    std::vector<int> indegree(graph.size());
    for (const auto& edges : graph) {
        for (int v : edges) {
            if (v < 0 || static_cast<std::size_t>(v) >= graph.size())
                throw std::out_of_range("边指向不存在的节点");
            ++indegree[v];
        }
    }
    std::priority_queue<int, std::vector<int>, std::greater<int>> ready;
    for (std::size_t i = 0; i < indegree.size(); ++i) if (indegree[i] == 0) ready.push(static_cast<int>(i));
    std::vector<int> result;
    while (!ready.empty()) {
        const int u = ready.top(); ready.pop(); result.push_back(u);
        for (int v : graph[u]) if (--indegree[v] == 0) ready.push(v);
    }
    if (result.size() != graph.size()) throw std::invalid_argument("图中存在环");
    return result;
}
int main() {
    const std::vector<std::vector<int>> tasks{{1, 2}, {3}, {3}, {}};
    const auto order = topological_sort(tasks);
    assert((order == std::vector<int>{0, 1, 2, 3}));
    bool rejected = false;
    try { topological_sort({{1}, {0}}); } catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    std::cout << "任务顺序:"; for (int task : order) std::cout << ' ' << task; std::cout << '\n';
}
