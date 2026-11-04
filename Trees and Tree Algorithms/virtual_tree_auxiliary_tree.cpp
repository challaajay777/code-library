// Algorithm: Virtual (Auxiliary) Tree Construction
// Purpose: Constructs compressed tree retaining only K marked nodes and their pairwise LCAs in O(K log K).
// Time Complexity: O(K log K)
// Space Complexity: O(K)
// Preconditions: Subset of K nodes from rooted tree.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>

struct VirtualTree {
    int n, timer;
    std::vector<int> tin, tout, depth;
    std::vector<std::vector<int>> up;

    VirtualTree(int n, const std::vector<std::vector<int>>& adj, int root = 0)
        : n(n), timer(0), tin(n), tout(n), depth(n), up(n, std::vector<int>(18, root)) {
        dfs(root, root, 0, adj);
    }

    void dfs(int u, int p, int d, const std::vector<std::vector<int>>& adj) {
        tin[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < 18; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) if (v != p) dfs(v, u, d + 1, adj);
        tout[u] = ++timer;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = 17; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }

    std::vector<std::pair<int, int>> build_virtual_tree(std::vector<int> nodes) {
        std::sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            return tin[a] < tin[b];
        });

        int k = nodes.size();
        for (int i = 0; i < k - 1; ++i) {
            nodes.push_back(lca(nodes[i], nodes[i + 1]));
        }
        std::sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            return tin[a] < tin[b];
        });
        nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());

        std::stack<int> st;
        std::vector<std::pair<int, int>> vtree_edges;

        for (int u : nodes) {
            while (!st.empty() && !is_ancestor(st.top(), u)) {
                st.pop();
            }
            if (!st.empty()) {
                vtree_edges.push_back({st.top(), u});
            }
            st.push(u);
        }
        return vtree_edges;
    }
};

int main() {
    int n = 5;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3, 4}; adj[2] = {0};
    adj[3] = {1}; adj[4] = {1};

    VirtualTree vt(n, adj, 0);
    auto edges = vt.build_virtual_tree({3, 4});
    // Virtual tree connects 1 -> 3 and 1 -> 4
    assert(edges.size() == 2);
    return 0;
}
