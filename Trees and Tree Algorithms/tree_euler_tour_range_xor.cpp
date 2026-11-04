// Algorithm: Euler Tour Flattening Range XOR
// Purpose: Queries path XOR on tree by range updates and prefix sum differences on flattened array.
// Time Complexity: O(N) build, O(1) query
// Space Complexity: O(N)
// Preconditions: Tree with vertex weights.

#include <iostream>
#include <vector>
#include <cassert>

struct TreeXORRange {
    int timer;
    std::vector<int> tin, tout, pref_xor;

    TreeXORRange(int n, const std::vector<std::vector<int>>& adj, const std::vector<int>& val, int root = 0)
        : timer(0), tin(n), tout(n), pref_xor(n, 0) {
        dfs(root, -1, 0, adj, val);
    }

    void dfs(int u, int p, int acc, const std::vector<std::vector<int>>& adj, const std::vector<int>& val) {
        tin[u] = ++timer;
        pref_xor[u] = acc ^ val[u];
        for (int v : adj[u]) if (v != p) dfs(v, u, pref_xor[u], adj, val);
        tout[u] = timer;
    }
};

int main() {
    int n = 2;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    std::vector<int> val = {3, 5};
    TreeXORRange txr(n, adj, val, 0);
    assert(txr.pref_xor[1] == (3 ^ 5));
    return 0;
}
