#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using Edge = std::pair<int, int>; // 目标、非负权重
using Graph = std::vector<std::vector<Edge>>;
struct Paths { std::vector<long long> distance; std::vector<int> previous; };
constexpr long long INF = std::numeric_limits<long long>::max();

Paths dijkstra(const Graph& graph, int source) {
    if (source < 0 || static_cast<std::size_t>(source) >= graph.size()) throw std::out_of_range("source");
    for (const auto& edges : graph) for (auto [v, weight] : edges)
        if (v < 0 || static_cast<std::size_t>(v) >= graph.size() || weight < 0)
            throw std::invalid_argument("无效边或负权重");
    Paths p{std::vector<long long>(graph.size(), INF), std::vector<int>(graph.size(), -1)};
    using Item = std::pair<long long, int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> queue;
    p.distance[source] = 0; queue.emplace(0, source);
    while (!queue.empty()) {
        auto [distance, u] = queue.top(); queue.pop();
        if (distance != p.distance[u]) continue;
        for (auto [v, weight] : graph[u]) {
            if (distance <= INF - weight && distance + weight < p.distance[v]) {
                p.distance[v] = distance + weight; p.previous[v] = u;
                queue.emplace(p.distance[v], v);
            }
        }
    }
    return p;
}
std::vector<int> path_to(const Paths& paths, int target) {
    if (target < 0 || static_cast<std::size_t>(target) >= paths.distance.size()) throw std::out_of_range("target");
    if (paths.distance[target] == INF) return {};
    std::vector<int> path;
    for (int v = target; v != -1; v = paths.previous[v]) path.push_back(v);
    std::reverse(path.begin(), path.end()); return path;
}
int main() {
    Graph graph{{{1, 4}, {2, 1}}, {{3, 1}}, {{1, 2}, {3, 5}}, {}, {}};
    auto paths = dijkstra(graph, 0);
    assert(paths.distance[3] == 4);
    assert((path_to(paths, 3) == std::vector<int>{0, 2, 1, 3}));
    assert(path_to(paths, 4).empty());
    std::cout << "0 到 3 的距离: " << paths.distance[3] << "，路径:";
    for (int v : path_to(paths, 3)) std::cout << ' ' << v;
    std::cout << '\n';
}
