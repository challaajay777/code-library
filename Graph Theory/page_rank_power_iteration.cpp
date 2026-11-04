// Algorithm: PageRank via Power Iteration
// Purpose: Computes stationary probability distribution (PageRank centrality) of directed graph.
// Time Complexity: O(Iterations * (V + E))
// Space Complexity: O(V)
// Preconditions: Directed web graph, damping factor d in (0, 1).

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

std::vector<double> pagerank(int n, const std::vector<std::vector<int>>& adj, double d = 0.85, int max_iter = 100) {
    std::vector<double> r(n, 1.0 / n);
    for (int it = 0; it < max_iter; ++it) {
        std::vector<double> next_r(n, (1.0 - d) / n);
        for (int u = 0; u < n; ++u) {
            if (!adj[u].empty()) {
                double share = d * r[u] / adj[u].size();
                for (int v : adj[u]) next_r[v] += share;
            } else {
                for (int v = 0; v < n; ++v) next_r[v] += d * r[u] / n;
            }
        }
        r = next_r;
    }
    return r;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    auto ranks = pagerank(n, adj);
    assert(std::abs(ranks[0] - ranks[1]) < 1e-4);
    return 0;
}
