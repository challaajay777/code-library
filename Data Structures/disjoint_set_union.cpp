// Algorithm: Disjoint Set Union (DSU / Union-Find)
// Supports: Union, find with path compression, component size, component count
// Indexing: 0-based element indices [0, n - 1]
// Complexity: O(alpha(n)) amortized per operation, O(n) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct DSU {
    int n;
    int num_components;
    vector<int> parent, sz;

    explicit DSU(int n) : n(n), num_components(n), parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        assert(0 <= u && u < n);
        return parent[u] == u ? u : (parent[u] = find(parent[u]));
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        num_components--;
        return true;
    }

    int get_size(int u) {
        return sz[find(u)];
    }

    int count() const {
        return num_components;
    }
};
