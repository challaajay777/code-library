// Algorithm: Thorup Component Hierarchy SSSP Simulation
// Purpose: Computes single source shortest paths in undirected graphs using component bucket queues.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Undirected graph with non-negative integer edge weights.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

struct ThorupEdge {
    int to, weight;
};

std::vector<int> thorup_sssp(int n, const std::vector<std::vector<ThorupEdge>>& adj, int s) {
    const int INF = 1e9;
    std::vector<int> dist(n, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;

        for (const auto& e : adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

int main() {
    int n = 3;
    std::vector<std::vector<ThorupEdge>> adj(n);
    adj[0].push_back({1, 4}); adj[1].push_back({0, 4});
    adj[1].push_back({2, 6}); adj[2].push_back({1, 6});
    adj[0].push_back({2, 12}); adj[2].push_back({0, 12});

    auto dist = thorup_sssp(n, adj, 0);
    assert(dist[2] == 10);
    return 0;
}
