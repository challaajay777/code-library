// Algorithm: Bidirectional Breadth-First Search
// Purpose: Finds shortest unweighted path expanding forward and backward levels simultaneously.
// Time Complexity: O(b^(d/2))
// Space Complexity: O(b^(d/2))
// Preconditions: Unweighted graph, valid source and target.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

int bidirectional_bfs(int n, const std::vector<std::vector<int>>& adj, int s, int t) {
    if (s == t) return 0;
    std::vector<int> dist_f(n, -1), dist_b(n, -1);
    std::queue<int> q_f, q_b;

    dist_f[s] = 0; q_f.push(s);
    dist_b[t] = 0; q_b.push(t);

    while (!q_f.empty() && !q_b.empty()) {
        int uf = q_f.front(); q_f.pop();
        for (int v : adj[uf]) {
            if (dist_b[v] != -1) return dist_f[uf] + 1 + dist_b[v];
            if (dist_f[v] == -1) {
                dist_f[v] = dist_f[uf] + 1;
                q_f.push(v);
            }
        }

        int ub = q_b.front(); q_b.pop();
        for (int v : adj[ub]) {
            if (dist_f[v] != -1) return dist_b[ub] + 1 + dist_f[v];
            if (dist_b[v] == -1) {
                dist_b[v] = dist_b[ub] + 1;
                q_b.push(v);
            }
        }
    }
    return -1;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1, 3}; adj[3] = {2};
    assert(bidirectional_bfs(n, adj, 0, 3) == 3);
    return 0;
}
