// Algorithm: Lengauer-Tarjan Dominator Tree
// Purpose: Constructs the immediate dominator tree of a directed control-flow graph.
// Time Complexity: O(M log N)
// Space Complexity: O(N + M)
// Preconditions: Directed graph with designated source root.

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <algorithm>

struct LengauerTarjan {
    int n, timer;
    std::vector<std::vector<int>> adj, radj, bucket;
    std::vector<int> dfn, idfn, parent, semi, idom, ancestor, best;

    LengauerTarjan(int n) : n(n), timer(0), adj(n), radj(n), bucket(n),
                            dfn(n, 0), idfn(n, 0), parent(n, 0), semi(n, 0),
                            idom(n, 0), ancestor(n, 0), best(n, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    void dfs(int u) {
        dfn[u] = ++timer;
        idfn[timer] = u;
        semi[u] = ancestor[u] = best[u] = u;
        for (int v : adj[u]) {
            if (!dfn[v]) {
                parent[v] = u;
                dfs(v);
            }
        }
    }

    int find(int u) {
        if (ancestor[u] == u) return u;
        int root = find(ancestor[u]);
        if (dfn[semi[best[ancestor[u]]]] < dfn[semi[best[u]]]) {
            best[u] = best[ancestor[u]];
        }
        return ancestor[u] = root;
    }

    void build(int root = 0) {
        dfs(root);
        for (int i = timer; i >= 2; --i) {
            int w = idfn[i];
            for (int v : radj[w]) {
                if (!dfn[v]) continue;
                find(v);
                if (dfn[semi[best[v]]] < dfn[semi[w]]) {
                    semi[w] = semi[best[v]];
                }
            }
            bucket[semi[w]].push_back(w);
            ancestor[w] = parent[w];

            for (int v : bucket[parent[w]]) {
                find(v);
                idom[v] = (semi[best[v]] == semi[v]) ? parent[w] : best[v];
            }
            bucket[parent[w]].clear();
        }

        for (int i = 2; i <= timer; ++i) {
            int w = idfn[i];
            if (idom[w] != semi[w]) {
                idom[w] = idom[idom[w]];
            }
        }
        idom[root] = root;
    }
};

int main() {
    LengauerTarjan lt(4);
    lt.add_edge(0, 1);
    lt.add_edge(1, 2);
    lt.add_edge(0, 2);
    lt.add_edge(2, 3);
    lt.build(0);

    assert(lt.idom[3] == 2);
    assert(lt.idom[2] == 0);
    return 0;
}
