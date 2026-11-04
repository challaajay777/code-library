// Algorithm: Maximum Independent Set via Complement Clique
// Purpose: Solves maximum independent set by finding maximum clique on the complement graph.
// Time Complexity: O(2^V)
// Space Complexity: O(V^2)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int solve_mis(int n, const std::vector<std::vector<bool>>& adj) {
    std::vector<std::vector<bool>> comp(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && !adj[i][j]) comp[i][j] = true;
        }
    }

    int max_set = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int i = 0; i < n && ok; ++i) {
            if (mask & (1 << i)) {
                for (int j = i + 1; j < n; ++j) {
                    if ((mask & (1 << j)) && adj[i][j]) {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (ok) max_set = std::max(max_set, __builtin_popcount(mask));
    }
    return max_set;
}

int main() {
    int n = 4;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    adj[0][1] = adj[1][0] = true;
    adj[1][2] = adj[2][1] = true;
    adj[2][3] = adj[3][2] = true;
    // Path 0-1-2-3 has MIS of size 2 ({0, 2} or {0, 3} or {1, 3})
    assert(solve_mis(n, adj) == 2);
    return 0;
}
