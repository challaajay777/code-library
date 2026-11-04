// Algorithm: Shortest Path in DAG via Topological Sort
// Purpose: Finds single-source shortest paths in DAG in linear time O(V + E) even with negative edge weights.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Directed Acyclic Graph with source s.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <climits>

struct Edge {
    int to, weight;
};

std::vector<long long> shortest_path_dag(int n, const std::vector<std::vector<Edge>>& adj, int s) {
    std::vector<int> in_deg(n, 0);
    for (int u = 0; u < n; ++u) {
        for (const auto& e : adj[u]) in_deg[e.to]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_deg[i] == 0) q.push(i);
    }

    std::vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (const auto& e : adj[u]) {
            if (--in_deg[e.to] == 0) q.push(e.to);
        }
    }

    const long long INF = 1e18;
    std::vector<long long> dist(n, INF);
    dist[s] = 0;

    for (int u : topo) {
        if (dist[u] == INF) continue;
        for (const auto& e : adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
            }
        }
    }
    return dist;
}

int main() {
    int n = 4;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 4});
    adj[1].push_back({2, -2});
    adj[1].push_back({3, 3});
    adj[2].push_back({3, 1});

    auto dist = shortest_path_dag(n, adj, 0);
    // 0 -> 1 (1) -> 2 (-2) = -1, 0 -> 1 -> 2 -> 3 = 0
    assert(dist[2] == -1);
    assert(dist[3] == 0);
    return 0;
}
