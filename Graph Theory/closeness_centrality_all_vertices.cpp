// Algorithm: Closeness Centrality for All Vertices
// Purpose: Calculates reciprocal of sum of shortest path distances from vertex to all others.
// Time Complexity: O(V * (V + E))
// Space Complexity: O(V)
// Preconditions: Connected graph.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::vector<double> closeness_centrality(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<double> closeness(n, 0.0);
    for (int i = 0; i < n; ++i) {
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        dist[i] = 0;
        q.push(i);
        int sum_d = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            sum_d += dist[u];
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        if (sum_d > 0) closeness[i] = (double)(n - 1) / sum_d;
    }
    return closeness;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1};
    auto cc = closeness_centrality(n, adj);
    // Center node 1 has shortest total distance (2), so highest closeness
    assert(cc[1] > cc[0]);
    return 0;
}
