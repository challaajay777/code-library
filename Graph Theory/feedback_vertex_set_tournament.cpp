// Algorithm: Feedback Vertex Set in Tournament Graph
// Purpose: Finds a minimum set of vertices whose removal eliminates all directed cycles in a tournament.
// Time Complexity: O(2^K * N)
// Space Complexity: O(N)
// Preconditions: Complete directed tournament graph.

#include <iostream>
#include <vector>
#include <cassert>

bool has_3_cycle(int n, const std::vector<std::vector<bool>>& adj, const std::vector<bool>& removed,
                 int& c1, int& c2, int& c3) {
    for (int i = 0; i < n; ++i) {
        if (removed[i]) continue;
        for (int j = 0; j < n; ++j) {
            if (removed[j] || !adj[i][j]) continue;
            for (int k = 0; k < n; ++k) {
                if (removed[k] || !adj[j][k]) continue;
                if (adj[k][i]) {
                    c1 = i; c2 = j; c3 = k;
                    return true;
                }
            }
        }
    }
    return false;
}

bool branch_fvs(int n, const std::vector<std::vector<bool>>& adj, std::vector<bool>& removed, int k) {
    int c1, c2, c3;
    if (!has_3_cycle(n, adj, removed, c1, c2, c3)) return true;
    if (k == 0) return false;

    for (int v : {c1, c2, c3}) {
        removed[v] = true;
        if (branch_fvs(n, adj, removed, k - 1)) return true;
        removed[v] = false;
    }
    return false;
}

int min_fvs_tournament(int n, const std::vector<std::vector<bool>>& adj) {
    std::vector<bool> removed(n, false);
    for (int k = 0; k <= n; ++k) {
        if (branch_fvs(n, adj, removed, k)) return k;
    }
    return n;
}

int main() {
    int n = 3;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    adj[0][1] = true;
    adj[1][2] = true;
    adj[2][0] = true;
    assert(min_fvs_tournament(n, adj) == 1);
    return 0;
}
