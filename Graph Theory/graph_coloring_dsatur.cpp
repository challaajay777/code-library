// Algorithm: DSatur Graph Vertex Coloring
// Purpose: Heuristic vertex coloring using degree of saturation (number of differently colored neighbors).
// Time Complexity: O(V^2)
// Space Complexity: O(V^2)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>

std::vector<int> dsatur_coloring(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> color(n, -1);
    std::vector<std::set<int>> neighbor_colors(n);
    std::vector<int> deg(n);
    for (int i = 0; i < n; ++i) deg[i] = adj[i].size();

    for (int step = 0; step < n; ++step) {
        int best_v = -1;
        for (int i = 0; i < n; ++i) {
            if (color[i] != -1) continue;
            if (best_v == -1 ||
                neighbor_colors[i].size() > neighbor_colors[best_v].size() ||
                (neighbor_colors[i].size() == neighbor_colors[best_v].size() && deg[i] > deg[best_v])) {
                best_v = i;
            }
        }

        std::vector<bool> used(n, false);
        for (int c : neighbor_colors[best_v]) used[c] = true;
        int chosen_c = 0;
        while (used[chosen_c]) chosen_c++;

        color[best_v] = chosen_c;
        for (int neighbor : adj[best_v]) {
            if (color[neighbor] == -1) {
                neighbor_colors[neighbor].insert(chosen_c);
            }
        }
    }
    return color;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2, 3};
    adj[1] = {0, 2};
    adj[2] = {0, 1};
    adj[3] = {0};

    auto col = dsatur_coloring(n, adj);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) assert(col[u] != col[v]);
    }
    return 0;
}
