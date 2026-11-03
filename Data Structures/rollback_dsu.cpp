// Algorithm: Rollback DSU (Undoable Union-Find)
// Supports: Union, find, snapshot, rollback to previous history state
// Indexing: 0-based element indices [0, n - 1]
// Complexity: O(log n) per find/union (no path compression), O(1) rollback step, O(n) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct RollbackDSU {
    struct Operation {
        int u, v;
        int sz_u;
    };

    int n;
    int num_components;
    vector<int> parent, sz;
    vector<Operation> history;

    explicit RollbackDSU(int n) : n(n), num_components(n), parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) const {
        assert(0 <= u && u < n);
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    }

    bool same(int u, int v) const {
        return find(u) == find(v);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        history.push_back({u, v, sz[u]});
        parent[v] = u;
        sz[u] += sz[v];
        num_components--;
        return true;
    }

    int snapshot() const {
        return (int)history.size();
    }

    void rollback(int checkpoint) {
        assert(checkpoint <= (int)history.size());
        while ((int)history.size() > checkpoint) {
            auto op = history.back();
            history.pop_back();
            parent[op.v] = op.v;
            sz[op.u] = op.sz_u;
            num_components++;
        }
    }
};
