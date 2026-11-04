// Algorithm: Stoer-Wagner Deterministic Global Min-Cut
// Purpose: Finds the global minimum cut in an undirected weighted graph in O(V^3) time.
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)
// Preconditions: Connected undirected graph with non-negative edge weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int stoer_wagner(int n, std::vector<std::vector<int>> g) {
    int min_cut = 1e9;
    std::vector<int> node(n);
    for (int i = 0; i < n; ++i) node[i] = i;

    for (int phase = 0; phase < n - 1; ++phase) {
        std::vector<int> w = g[node[0]];
        std::vector<bool> added(n, false);
        added[0] = true;
        int prev = 0, last = 0;

        for (int i = 1; i < n - phase; ++i) {
            int next_v = -1;
            for (int j = 1; j < n - phase; ++j) {
                if (!added[j] && (next_v == -1 || w[node[j]] > w[node[next_v]])) {
                    next_v = j;
                }
            }
            added[next_v] = true;
            prev = last;
            last = next_v;
            for (int j = 0; j < n - phase; ++j) {
                w[node[j]] += g[node[next_v]][node[j]];
            }
        }

        min_cut = std::min(min_cut, w[node[last]] - g[node[last]][node[last]]);

        // Merge last into prev
        for (int i = 0; i < n - phase; ++i) {
            g[node[prev]][node[i]] += g[node[last]][node[i]];
            g[node[i]][node[prev]] = g[node[prev]][node[i]];
        }
        node.erase(node.begin() + last);
    }
    return min_cut;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> g(n, std::vector<int>(n, 0));
    g[0][1] = g[1][0] = 2;
    g[1][2] = g[2][1] = 3;
    g[2][3] = g[3][2] = 2;
    g[3][0] = g[0][3] = 3;
    assert(stoer_wagner(n, g) == 4);
    return 0;
}
