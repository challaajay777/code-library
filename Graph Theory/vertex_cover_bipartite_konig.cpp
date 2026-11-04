// Algorithm: Konig's Theorem Bipartite Minimum Vertex Cover
// Purpose: Constructs the minimum vertex cover and maximum independent set of a bipartite graph.
// Time Complexity: O(V * E)
// Space Complexity: O(V + E)
// Preconditions: Bipartite graph partitions L and R.

#include <iostream>
#include <vector>
#include <cassert>

void dfs_konig(int u, const std::vector<std::vector<int>>& adj,
               const std::vector<int>& match_l, const std::vector<int>& match_r,
               std::vector<bool>& vis_l, std::vector<bool>& vis_r) {
    vis_l[u] = true;
    for (int v : adj[u]) {
        if (!vis_r[v] && v != match_l[u]) {
            vis_r[v] = true;
            if (match_r[v] != -1 && !vis_l[match_r[v]]) {
                dfs_konig(match_r[v], adj, match_l, match_r, vis_l, vis_r);
            }
        }
    }
}

std::pair<std::vector<int>, std::vector<int>> min_vertex_cover_bipartite(
    int n, int m, const std::vector<std::vector<int>>& adj,
    const std::vector<int>& match_l, const std::vector<int>& match_r) {

    std::vector<bool> vis_l(n, false), vis_r(m, false);
    for (int u = 0; u < n; ++u) {
        if (match_l[u] == -1 && !vis_l[u]) {
            dfs_konig(u, adj, match_l, match_r, vis_l, vis_r);
        }
    }

    std::vector<int> cover_l, cover_r;
    for (int u = 0; u < n; ++u) if (!vis_l[u]) cover_l.push_back(u);
    for (int v = 0; v < m; ++v) if (vis_r[v]) cover_r.push_back(v);

    return {cover_l, cover_r};
}

int main() {
    int n = 2, m = 2;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(0);
    adj[1].push_back(0);
    std::vector<int> match_l = {0, -1};
    std::vector<int> match_r = {0, -1};

    auto [cl, cr] = min_vertex_cover_bipartite(n, m, adj, match_l, match_r);
    assert(cl.size() + cr.size() == 1);
    return 0;
}
