#include <iostream>
#include <vector>
#include <queue>
#include <stack>

// DFS / BFS 练习 — 图的遍历
using Graph = std::vector<std::vector<int>>;

void dfs(const Graph& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stk;
    stk.push(start);
    while (!stk.empty()) {
        int v = stk.top(); stk.pop();
        if (visited[v]) continue;
        visited[v] = true;
        std::cout << v << " ";
        for (auto it = graph[v].rbegin(); it != graph[v].rend(); ++it) {
            if (!visited[*it]) stk.push(*it);
        }
    }
    std::cout << std::endl;
}

void bfs(const Graph& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        std::cout << v << " ";
        for (int u : graph[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    Graph graph = {
        {1, 2},    // 0
        {0, 3, 4}, // 1
        {0, 5},    // 2
        {1},       // 3
        {1},       // 4
        {2}        // 5
    };
    std::cout << "DFS: "; dfs(graph, 0);
    std::cout << "BFS: "; bfs(graph, 0);
    return 0;
}
