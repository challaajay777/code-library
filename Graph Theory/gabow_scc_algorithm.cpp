// Algorithm: Gabow Strongly Connected Components (Two Stacks)
// Purpose: Finds SCCs using path-based depth-first search with two stacks (Cheriyan-Mehlhorn / Gabow).
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Directed graph.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

struct GabowSCC {
    int n, timer, scc_count;
    std::vector<std::vector<int>> adj;
    std::vector<int> preorder, scc;
    std::stack<int> s, p;

    GabowSCC(int n) : n(n), timer(0), scc_count(0), adj(n), preorder(n, -1), scc(n, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    void dfs(int u) {
        preorder[u] = ++timer;
        s.push(u);
        p.push(u);

        for (int v : adj[u]) {
            if (preorder[v] == -1) {
                dfs(v);
            } else if (scc[v] == -1) {
                while (preorder[p.top()] > preorder[v]) p.pop();
            }
        }

        if (p.top() == u) {
            p.pop();
            while (true) {
                int x = s.top();
                s.pop();
                scc[x] = scc_count;
                if (x == u) break;
            }
            scc_count++;
        }
    }

    void build() {
        for (int i = 0; i < n; ++i) if (preorder[i] == -1) dfs(i);
    }
};

int main() {
    GabowSCC gs(3);
    gs.add_edge(0, 1);
    gs.add_edge(1, 2);
    gs.add_edge(2, 0);
    gs.build();
    assert(gs.scc_count == 1);
    return 0;
}
