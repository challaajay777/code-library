// Algorithm: Bipartite Graph 2-Coloring Check
// Purpose: Verifies whether a graph is bipartite and assigns colors 0 and 1 to every vertex.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

bool is_bipartite(int n, const std::vector<std::vector<int>>& adj, std::vector<int>& color) {
    color.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
        std::queue<int> q;
        q.push(i);
        color[i] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};

    std::vector<int> color;
    assert(is_bipartite(n, adj, color));

    adj[0].push_back(2);
    adj[2].push_back(0); // forms odd cycle 0-1-2-0
    assert(!is_bipartite(n, adj, color));
    return 0;
}
