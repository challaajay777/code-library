// Algorithm: Bidirectional Dijkstra Search
// Purpose: Accelerates shortest path queries by searching forward from source and backward from target.
// Time Complexity: O(b^(d/2)) average search space
// Space Complexity: O(V)
// Preconditions: Directed/undirected graph with non-negative edge weights.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

struct Edge {
    int to, weight;
};

const long long INF = 1e18;

long long bidirectional_dijkstra(int n, const std::vector<std::vector<Edge>>& adj,
                                 const std::vector<std::vector<Edge>>& radj, int s, int t) {
    if (s == t) return 0;
    std::vector<long long> dist_f(n, INF), dist_b(n, INF);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq_f, pq_b;

    dist_f[s] = 0; pq_f.push({0, s});
    dist_b[t] = 0; pq_b.push({0, t});

    long long mu = INF;

    while (!pq_f.empty() && !pq_b.empty()) {
        if (pq_f.top().first + pq_b.top().first >= mu) break;

        auto [df, uf] = pq_f.top(); pq_f.pop();
        if (df <= dist_f[uf]) {
            for (const auto& e : adj[uf]) {
                if (dist_f[uf] + e.weight < dist_f[e.to]) {
                    dist_f[e.to] = dist_f[uf] + e.weight;
                    pq_f.push({dist_f[e.to], e.to});
                }
                if (dist_b[e.to] != INF) {
                    mu = std::min(mu, dist_f[uf] + e.weight + dist_b[e.to]);
                }
            }
        }

        auto [db, ub] = pq_b.top(); pq_b.pop();
        if (db <= dist_b[ub]) {
            for (const auto& e : radj[ub]) {
                if (dist_b[ub] + e.weight < dist_b[e.to]) {
                    dist_b[e.to] = dist_b[ub] + e.weight;
                    pq_b.push({dist_b[e.to], e.to});
                }
                if (dist_f[e.to] != INF) {
                    mu = std::min(mu, dist_b[ub] + e.weight + dist_f[e.to]);
                }
            }
        }
    }
    return mu;
}

int main() {
    int n = 4;
    std::vector<std::vector<Edge>> adj(n), radj(n);
    auto add = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        radj[v].push_back({u, w});
    };
    add(0, 1, 2); add(1, 2, 3); add(2, 3, 1); add(0, 3, 10);
    assert(bidirectional_dijkstra(n, adj, radj, 0, 3) == 6);
    return 0;
}
