// Algorithm: Dial Algorithm (0-C Shortest Path Bucket Queue)
// Purpose: Finds single-source shortest paths when all edge weights are small integers in [0..C].
// Time Complexity: O(V * C + E)
// Space Complexity: O(V + C)
// Preconditions: Edge weights are non-negative integers <= C.

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

struct Edge {
    int to, weight;
};

const int INF = 1e9;

std::vector<int> dial_shortest_paths(int n, const std::vector<std::vector<Edge>>& adj, int s, int max_w) {
    std::vector<int> dist(n, INF);
    dist[s] = 0;

    int bucket_count = max_w * n + 1;
    std::vector<std::vector<int>> buckets(bucket_count);
    buckets[0].push_back(s);

    int idx = 0;
    while (idx < bucket_count) {
        while (idx < bucket_count && buckets[idx].empty()) idx++;
        if (idx == bucket_count) break;

        int u = buckets[idx].back();
        buckets[idx].pop_back();

        if (dist[u] < idx) continue;

        for (const auto& e : adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                buckets[dist[e.to]].push_back(e.to);
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
    adj[1].push_back({2, 2});
    adj[2].push_back({3, 1});

    auto dist = dial_shortest_paths(n, adj, 0, 4);
    assert(dist[3] == 4); // 0 -> 1 (1) -> 2 (2) -> 3 (1) = 4
    return 0;
}
