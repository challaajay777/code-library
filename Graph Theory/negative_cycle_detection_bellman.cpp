// Algorithm: Negative Cycle Detection and Extraction via Bellman-Ford
// Purpose: Detects if directed graph contains a negative weight cycle and reconstructs the cycle vertices.
// Time Complexity: O(V * E)
// Space Complexity: O(V)
// Preconditions: Directed graph with arbitrary real/integer edge weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Edge {
    int u, v, weight;
};

std::vector<int> find_negative_cycle(int n, const std::vector<Edge>& edges) {
    std::vector<long long> dist(n, 0);
    std::vector<int> parent(n, -1);
    int x = -1;

    for (int i = 0; i < n; ++i) {
        x = -1;
        for (const auto& e : edges) {
            if (dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;
                parent[e.v] = e.u;
                x = e.v;
            }
        }
    }

    if (x == -1) return {}; // No negative cycle

    for (int i = 0; i < n; ++i) x = parent[x];

    std::vector<int> cycle;
    for (int cur = x;; cur = parent[cur]) {
        cycle.push_back(cur);
        if (cur == x && cycle.size() > 1) break;
    }
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
}

int main() {
    int n = 4;
    std::vector<Edge> edges = {
        {0, 1, 1},
        {1, 2, -2},
        {2, 3, -1},
        {3, 1, 1}
    };
    // Cycle 1 -> 2 -> 3 -> 1 has weight -2 + -1 + 1 = -2 < 0
    auto cycle = find_negative_cycle(n, edges);
    assert(!cycle.empty());
    assert(cycle.front() == cycle.back());
    return 0;
}
