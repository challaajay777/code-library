// Algorithm: Connected Components via BFS
// Purpose: Partitions vertices into connected components using iterative BFS queue traversal.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::pair<int, std::vector<int>> find_components_bfs(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> comp(n, -1);
    int num_comp = 0;
    for (int i = 0; i < n; ++i) {
        if (comp[i] != -1) continue;
        std::queue<int> q;
        q.push(i);
        comp[i] = num_comp;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    comp[v] = num_comp;
                    q.push(v);
                }
            }
        }
        num_comp++;
    }
    return {num_comp, comp};
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    auto [c, comp] = find_components_bfs(n, adj);
    assert(c == 3);
    return 0;
}
