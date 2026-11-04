// Algorithm: Tree Jump Pointers Level Ancestor
// Purpose: Computes level ancestors using jump pointers in O(log N) query time.
// Time Complexity: O(N log N) precomputation, O(log N) query
// Space Complexity: O(N log N)
// Preconditions: Rooted tree.

#include <iostream>
#include <vector>
#include <cassert>

int jump_ancestor(int u, int k, const std::vector<std::vector<int>>& up) {
    for (int i = 0; (1 << i) <= k; ++i) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == -1) break;
        }
    }
    return u;
}

int main() {
    std::vector<std::vector<int>> up(3, std::vector<int>(2, -1));
    up[2][0] = 1; up[2][1] = 0;
    up[1][0] = 0;
    assert(jump_ancestor(2, 2, up) == 0);
    return 0;
}
