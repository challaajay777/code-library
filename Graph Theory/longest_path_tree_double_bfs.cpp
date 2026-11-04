// Algorithm: Tree Diameter and Endpoints via Double BFS
// Purpose: Computes the exact diameter and peripheral endpoints of an unweighted tree via 2 BFS sweeps.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Connected unweighted tree.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::pair<int, int> bfs_farthest(int n, const std::vector<std::vector<int>>& adj, int start) {
    std::vector<int> dist(n, -1);
    std::queue<int> q;
    dist[start] = 0;
    q.push(start);
    int farthest = start;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] > dist[farthest]) farthest = u;

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return {farthest, dist[farthest]};
}

int tree_diameter(int n, const std::vector<std::vector<int>>& adj) {
    auto [u, _] = bfs_farthest(n, adj, 0);
    auto [v, d] = bfs_farthest(n, adj, u);
    return d;
}

int main() {
    int n = 5;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);
    adj[3].push_back(4); adj[4].push_back(3);

    assert(tree_diameter(n, adj) == 4);
    return 0;
}
