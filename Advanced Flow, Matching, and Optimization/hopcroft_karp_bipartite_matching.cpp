// Algorithm: Hopcroft-Karp Maximum Bipartite Matching
// Supports: Maximum cardinality bipartite matching, matched pair extraction
// Indexing: 0-based vertex indices on Left [0, nL - 1] and Right [0, nR - 1]
// Complexity: O(E * sqrt(V)) time, O(V + E) memory
// Preconditions: Bipartite graph with partitions Left and Right

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct HopcroftKarp {
    static constexpr int INF_DIST = 1e9 + 7;

    int nL, nR;
    vector<vector<int>> adj;
    vector<int> match_left, match_right, dist;

    HopcroftKarp(int left_size, int right_size)
        : nL(left_size), nR(right_size), adj(nL + 1),
          match_left(nL + 1, 0), match_right(nR + 1, 0), dist(nL + 1, 0) {}

    // Adds edge between left node u and right node v (0-based)
    void add_edge(int u, int v) {
        assert(0 <= u && u < nL && 0 <= v && v < nR);
        adj[u + 1].push_back(v + 1); // 1-based internally
    }

private:
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= nL; ++u) {
            if (match_left[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF_DIST;
            }
        }
        dist[0] = INF_DIST;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[match_right[v]] == INF_DIST) {
                        dist[match_right[v]] = dist[u] + 1;
                        q.push(match_right[v]);
                    }
                }
            }
        }
        return dist[0] != INF_DIST;
    }

    bool dfs(int u) {
        if (u == 0) return true;
        for (int v : adj[u]) {
            if (dist[match_right[v]] == dist[u] + 1) {
                if (dfs(match_right[v])) {
                    match_right[v] = u;
                    match_left[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF_DIST;
        return false;
    }

public:
    int max_matching() {
        int matching = 0;
        fill(match_left.begin(), match_left.end(), 0);
        fill(match_right.begin(), match_right.end(), 0);

        while (bfs()) {
            for (int u = 1; u <= nL; ++u) {
                if (match_left[u] == 0 && dfs(u)) {
                    matching++;
                }
            }
        }
        return matching;
    }

    // Returns vector of matched {u, v} pairs (0-based)
    vector<pair<int, int>> get_matches() const {
        vector<pair<int, int>> res;
        for (int u = 1; u <= nL; ++u) {
            if (match_left[u] != 0) {
                res.push_back({u - 1, match_left[u] - 1});
            }
        }
        return res;
    }
};
