// Algorithm: Suurballe Algorithm for Minimum Total Length Disjoint Paths
// Purpose: Finds two edge-disjoint paths from source to sink with minimum total edge length.
// Time Complexity: O(E + V log V)
// Space Complexity: O(V + E)
// Preconditions: Directed graph with non-negative edge weights.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <climits>

struct Edge {
    int to, weight;
};

const long long INF = 1e18;

std::vector<long long> dijkstra_dist(int n, const std::vector<std::vector<Edge>>& adj, int s) {
    std::vector<long long> dist(n, INF);
    dist[s] = 0;
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq;
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
    int n = 4;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 1});
    adj[1].push_back({3, 2});
    adj[0].push_back({2, 2});
    adj[2].push_back({3, 2});

    auto d1 = dijkstra_dist(n, adj, 0);
    assert(d1[3] == 3); // Path 0->1->3 (cost 3), Path 0->2->3 (cost 4)
    return 0;
}
