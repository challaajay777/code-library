// Algorithm: Johnson All-Pairs Shortest Paths
// Purpose: Computes all-pairs shortest paths on sparse graphs with negative edge weights using reweighting.
// Time Complexity: O(V * E + V^2 log V)
// Space Complexity: O(V^2)
// Preconditions: Graph contains no negative weight cycles.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <climits>

struct Edge {
    int to, weight;
};

const long long INF = 1e18;

std::vector<std::vector<long long>> johnson_apsp(int n, const std::vector<std::vector<Edge>>& adj) {
    // Add dummy node n with 0-weight edges to all nodes
    std::vector<long long> h(n + 1, INF);
    h[n] = 0;

    for (int i = 0; i <= n; ++i) {
        for (int u = 0; u < n; ++u) {
            if (h[u] == INF) continue;
            for (const auto& e : adj[u]) {
                if (h[u] + e.weight < h[e.to]) {
                    h[e.to] = h[u] + e.weight;
                }
            }
        }
        for (int u = 0; u < n; ++u) {
            if (h[n] + 0 < h[u]) h[u] = 0;
        }
    }

    std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, INF));

    for (int s = 0; s < n; ++s) {
        dist[s][s] = 0;
        std::priority_queue<std::pair<long long, int>,
                            std::vector<std::pair<long long, int>>,
                            std::greater<std::pair<long long, int>>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[s][u]) continue;

            for (const auto& e : adj[u]) {
                long long reweighted = e.weight + h[u] - h[e.to];
                if (dist[s][u] + reweighted < dist[s][e.to]) {
                    dist[s][e.to] = dist[s][u] + reweighted;
                    pq.push({dist[s][e.to], e.to});
                }
            }
        }

        for (int v = 0; v < n; ++v) {
            if (dist[s][v] != INF) {
                dist[s][v] += h[v] - h[s];
            }
        }
    }
    return dist;
}

int main() {
    int n = 3;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, -2});
    adj[1].push_back({2, 3});
    adj[0].push_back({2, 2});

    auto d = johnson_apsp(n, adj);
    assert(d[0][1] == -2);
    assert(d[0][2] == 1);
    assert(d[1][2] == 3);
    return 0;
}
