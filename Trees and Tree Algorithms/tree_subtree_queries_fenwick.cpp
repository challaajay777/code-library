// Algorithm: Subtree Queries and Point Updates via Fenwick Tree
// Purpose: Answers subtree sum queries and supports node value point updates in O(log N) using Euler tour.
// Time Complexity: O(log N) per query and update
// Space Complexity: O(N)
// Preconditions: Rooted tree.

#include <iostream>
#include <vector>
#include <cassert>

struct Fenwick {
    int n;
    std::vector<long long> tree;
    Fenwick(int n) : n(n), tree(n + 1, 0) {}
    void add(int i, long long delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
    long long query_range(int l, int r) {
        return query(r) - query(l - 1);
    }
};

struct SubtreeFenwick {
    int timer;
    std::vector<int> tin, tout;
    Fenwick fenw;

    SubtreeFenwick(int n, const std::vector<std::vector<int>>& adj, int root = 0)
        : timer(0), tin(n), tout(n), fenw(n) {
        dfs(root, -1, adj);
    }

    void dfs(int u, int p, const std::vector<std::vector<int>>& adj) {
        tin[u] = ++timer;
        for (int v : adj[u]) if (v != p) dfs(v, u, adj);
        tout[u] = timer;
    }

    void update(int u, long long val) { fenw.add(tin[u], val); }
    long long query(int u) { return fenw.query_range(tin[u], tout[u]); }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};

    SubtreeFenwick sf(n, adj, 0);
    sf.update(1, 10);
    sf.update(2, 20);
    sf.update(0, 5);

    assert(sf.query(0) == 35);
    assert(sf.query(1) == 10);
    return 0;
}
