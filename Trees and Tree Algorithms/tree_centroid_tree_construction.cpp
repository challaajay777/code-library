// Algorithm: Centroid Tree Decomposition Hierarchy
// Purpose: Builds the centroid tree hierarchy of depth O(log N) for multi-query tree paths.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Connected tree.

#include <iostream>
#include <vector>
#include <cassert>

struct CentroidTree {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> sz, parent;
    std::vector<bool> removed;

    CentroidTree(int n, const std::vector<std::vector<int>>& adj)
        : n(n), adj(adj), sz(n), parent(n, -1), removed(n, false) {
        build(0, -1);
    }

    void get_sz(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) if (v != p && !removed[v]) { get_sz(v, u); sz[u] += sz[v]; }
    }

    int get_centroid(int u, int p, int total) {
        for (int v : adj[u]) if (v != p && !removed[v] && sz[v] > total / 2) return get_centroid(v, u, total);
        return u;
    }

    int build(int entry, int p) {
        get_sz(entry, -1);
        int c = get_centroid(entry, -1, sz[entry]);
        removed[c] = true;
        parent[c] = p;

        for (int v : adj[c]) {
            if (!removed[v]) build(v, c);
        }
        return c;
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    CentroidTree ct(n, adj);
    // Center node 0 is root of centroid tree
    assert(ct.parent[0] == -1);
    return 0;
}
