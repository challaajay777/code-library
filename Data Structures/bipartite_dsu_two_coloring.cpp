// Algorithm: Bipartite DSU with Odd Cycle Detection
// Purpose: Maintains 2-coloring relations dynamically and detects if added edge creates an odd cycle.
// Time Complexity: O(alpha(N))
// Space Complexity: O(N)
// Preconditions: Undirected graph edges.

#include <iostream>
#include <vector>
#include <cassert>

struct BipartiteDSU {
    std::vector<int> parent, parity;
    bool is_bipartite = true;

    BipartiteDSU(int n) : parent(n), parity(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    std::pair<int, int> find(int i) {
        if (parent[i] == i) return {i, 0};
        auto [root, p] = find(parent[i]);
        parent[i] = root;
        parity[i] ^= p;
        return {parent[i], parity[i]};
    }

    void add_edge(int u, int v) {
        auto [root_u, pu] = find(u);
        auto [root_v, pv] = find(v);
        if (root_u == root_v) {
            if (pu == pv) is_bipartite = false; // odd cycle
        } else {
            parent[root_u] = root_v;
            parity[root_u] = pu ^ pv ^ 1;
        }
    }
};

int main() {
    BipartiteDSU dsu(3);
    dsu.add_edge(0, 1);
    dsu.add_edge(1, 2);
    assert(dsu.is_bipartite);
    dsu.add_edge(2, 0); // triangle: odd cycle
    assert(!dsu.is_bipartite);
    return 0;
}
