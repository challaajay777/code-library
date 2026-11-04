// Algorithm: Hopcroft-Karp Maximum Bipartite Matching
// Purpose: Finds maximum cardinality bipartite matching in O(E sqrt(V)) time using layered BFS/DFS.
// Time Complexity: O(E sqrt(V))
// Space Complexity: O(V + E)
// Preconditions: Bipartite graph with left part size N and right part size M.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class HopcroftKarp {
    int n, m;
    std::vector<std::vector<int>> adj;
    std::vector<int> pair_u, pair_v, dist;

public:
    HopcroftKarp(int n, int m) : n(n), m(m), adj(n + 1), pair_u(n + 1, 0), pair_v(m + 1, 0), dist(n + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        std::queue<int> q;
        for (int u = 1; u <= n; ++u) {
            if (pair_u[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = 1e9;
            }
        }
        dist[0] = 1e9;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[pair_v[v]] == 1e9) {
                        dist[pair_v[v]] = dist[u] + 1;
                        q.push(pair_v[v]);
                    }
                }
            }
        }
        return dist[0] != 1e9;
    }

    bool dfs(int u) {
        if (u != 0) {
            for (int v : adj[u]) {
                if (dist[pair_v[v]] == dist[u] + 1) {
                    if (dfs(pair_v[v])) {
                        pair_v[v] = u;
                        pair_u[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = 1e9;
            return false;
        }
        return true;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; ++u) {
                if (pair_u[u] == 0 && dfs(u)) matching++;
            }
        }
        return matching;
    }
};

int main() {
    HopcroftKarp hk(3, 3);
    hk.add_edge(1, 1);
    hk.add_edge(1, 2);
    hk.add_edge(2, 2);
    hk.add_edge(3, 3);
    assert(hk.max_matching() == 3);
    return 0;
}
