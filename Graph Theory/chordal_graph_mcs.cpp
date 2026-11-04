// Algorithm: Chordal Graph Recognition via MCS
// Purpose: Tests whether a graph is chordal using Maximum Cardinality Search for perfect elimination ordering.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <algorithm>

bool is_chordal(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> weight(n, 0);
    std::vector<bool> visited(n, false);
    std::vector<int> peo(n);

    for (int i = n - 1; i >= 0; --i) {
        int best_v = -1;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (best_v == -1 || weight[v] > weight[best_v])) {
                best_v = v;
            }
        }
        visited[best_v] = true;
        peo[i] = best_v;
        for (int u : adj[best_v]) {
            if (!visited[u]) weight[u]++;
        }
    }

    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[peo[i]] = i;

    // Check simplicial property
    for (int i = 0; i < n; ++i) {
        int u = peo[i];
        std::vector<int> higher_neighbors;
        for (int v : adj[u]) {
            if (pos[v] > pos[u]) higher_neighbors.push_back(v);
        }
        if (higher_neighbors.empty()) continue;
        int min_higher = higher_neighbors[0];
        for (int v : higher_neighbors) {
            if (pos[v] < pos[min_higher]) min_higher = v;
        }
        std::unordered_set<int> min_adj(adj[min_higher].begin(), adj[min_higher].end());
        for (int v : higher_neighbors) {
            if (v != min_higher && !min_adj.count(v)) return false;
        }
    }
    return true;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    // Complete graph K4 is chordal
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) adj[i].push_back(j);
        }
    }
    assert(is_chordal(n, adj));
    return 0;
}
