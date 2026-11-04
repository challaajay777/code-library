// Algorithm: Shortest Cycle (Girth) via BFS
// Purpose: Computes the length of the shortest cycle in an unweighted undirected graph.
// Time Complexity: O(V * (V + E))
// Space Complexity: O(V)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

int find_girth(int n, const std::vector<std::vector<int>>& adj) {
    const int INF = 1e9;
    int min_cycle = INF;

    for (int start = 0; start < n; ++start) {
        std::vector<int> dist(n, INF);
        std::vector<int> parent(n, -1);
        std::queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                } else if (parent[u] != v) {
                    min_cycle = std::min(min_cycle, dist[u] + dist[v] + 1);
                }
            }
        }
    }
    return (min_cycle >= INF) ? -1 : min_cycle;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};
    // 4-cycle
    assert(find_girth(n, adj) == 4);
    return 0;
}
