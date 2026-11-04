// Algorithm: Tree Path XOR Query in O(1)
// Purpose: Queries XOR sum of vertex weights along path between u and v in O(1) using root prefix XOR.
// Time Complexity: O(N) precomputation, O(1) query
// Space Complexity: O(N)
// Preconditions: Rooted tree with vertex XOR values.

#include <iostream>
#include <vector>
#include <cassert>

struct TreePathXOR {
    std::vector<int> pref_xor;

    TreePathXOR(int n, const std::vector<std::vector<int>>& adj, const std::vector<int>& val, int root = 0)
        : pref_xor(n, 0) {
        dfs(root, -1, 0, adj, val);
    }

    void dfs(int u, int p, int cur_xor, const std::vector<std::vector<int>>& adj, const std::vector<int>& val) {
        pref_xor[u] = cur_xor ^ val[u];
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, pref_xor[u], adj, val);
            }
        }
    }

    int query(int u, int v, int lca_val) {
        return pref_xor[u] ^ pref_xor[v] ^ lca_val;
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> val = {5, 3, 6};

    TreePathXOR txor(n, adj, val, 0);
    // Path 1 -> 0 -> 2: 3 ^ 5 ^ 6 = 0
    assert(txor.query(1, 2, 5) == 0);
    return 0;
}
