// Algorithm: Yen's Algorithm for K Shortest Loopless Paths
// Purpose: Finds the K shortest simple paths from source to target in weighted directed graph.
// Time Complexity: O(K * V * (E + V log V))
// Space Complexity: O(K * V + E)
// Preconditions: Non-negative edge weights.

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cassert>
#include <algorithm>

struct Edge {
    int to, weight;
};

struct Path {
    long long cost;
    std::vector<int> nodes;
    bool operator>(const Path& o) const { return cost > o.cost; }
};

Path dijkstra_yen(int n, const std::vector<std::vector<Edge>>& adj, int s, int t,
                  const std::set<std::pair<int, int>>& deleted_edges,
                  const std::set<int>& deleted_nodes) {
    const long long INF = 1e18;
    std::vector<long long> dist(n, INF);
    std::vector<int> parent(n, -1);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq;

    if (deleted_nodes.count(s) || deleted_nodes.count(t)) return {INF, {}};

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        if (u == t) break;

        for (const auto& e : adj[u]) {
            if (deleted_nodes.count(e.to) || deleted_edges.count({u, e.to})) continue;
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    if (dist[t] == INF) return {INF, {}};
    std::vector<int> path;
    for (int cur = t; cur != -1; cur = parent[cur]) path.push_back(cur);
    std::reverse(path.begin(), path.end());
    return {dist[t], path};
}

std::vector<Path> k_shortest_paths(int n, const std::vector<std::vector<Edge>>& adj, int s, int t, int K) {
    std::vector<Path> A;
    Path p0 = dijkstra_yen(n, adj, s, t, {}, {});
    if (p0.cost >= 1e18) return A;
    A.push_back(p0);

    std::priority_queue<Path, std::vector<Path>, std::greater<Path>> B;

    for (int k = 1; k < K; ++k) {
        const auto& prev = A[k - 1].nodes;
        for (size_t i = 0; i < prev.size() - 1; ++i) {
            int spur_node = prev[i];
            std::vector<int> root_path(prev.begin(), prev.begin() + i + 1);

            std::set<std::pair<int, int>> deleted_edges;
            for (const auto& path : A) {
                if (path.nodes.size() > i && std::equal(root_path.begin(), root_path.end(), path.nodes.begin())) {
                    deleted_edges.insert({path.nodes[i], path.nodes[i + 1]});
                }
            }

            std::set<int> deleted_nodes;
            for (size_t j = 0; j < i; ++j) {
                deleted_nodes.insert(root_path[j]);
            }

            Path spur_path = dijkstra_yen(n, adj, spur_node, t, deleted_edges, deleted_nodes);
            if (spur_path.cost < 1e18) {
                Path total_path;
                total_path.nodes = root_path;
                total_path.nodes.pop_back();
                for (int node : spur_path.nodes) total_path.nodes.push_back(node);

                long long total_cost = 0;
                for (size_t step = 0; step < total_path.nodes.size() - 1; ++step) {
                    int u = total_path.nodes[step], v = total_path.nodes[step + 1];
                    for (const auto& e : adj[u]) if (e.to == v) { total_cost += e.weight; break; }
                }
                total_path.cost = total_cost;
                B.push(total_path);
            }
        }

        if (B.empty()) break;
        A.push_back(B.top());
        B.pop();
    }
    return A;
}

int main() {
    int n = 4;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 2});
    adj[1].push_back({3, 4});
    adj[2].push_back({3, 1});
    adj[1].push_back({2, 1});

    auto paths = k_shortest_paths(n, adj, 0, 3, 2);
    // 0 -> 2 -> 3 has cost 3
    // 0 -> 1 -> 2 -> 3 has cost 3
    assert(paths.size() == 2);
    assert(paths[0].cost == 3);
    assert(paths[1].cost == 3);
    return 0;
}
