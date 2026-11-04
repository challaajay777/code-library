// Algorithm: Welsh-Powell Graph Coloring
// Purpose: Greedy graph vertex coloring ordering vertices by descending degree.
// Time Complexity: O(V^2 + E)
// Space Complexity: O(V)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <algorithm>

std::vector<int> welsh_powell_coloring(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return adj[a].size() > adj[b].size();
    });

    std::vector<int> color(n, -1);
    for (int u : order) {
        std::vector<bool> used(n, false);
        for (int v : adj[u]) {
            if (color[v] != -1) used[color[v]] = true;
        }
        for (int c = 0; c < n; ++c) {
            if (!used[c]) {
                color[u] = c;
                break;
            }
        }
    }
    return color;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {0, 2};
    adj[2] = {0, 1};

    auto col = welsh_powell_coloring(n, adj);
    assert(col[0] != col[1] && col[1] != col[2] && col[0] != col[2]);
    return 0;
}
