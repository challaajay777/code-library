// Algorithm: K-th Ancestor via Binary Lifting
// Purpose: Queries the k-th ancestor of a tree vertex in O(log N) time.
// Time Complexity: O(N log N) precomputation, O(log N) per query
// Space Complexity: O(N log N)
// Preconditions: Rooted tree, valid k >= 0.

#include <iostream>
#include <vector>
#include <cassert>

struct KthAncestor {
    int LOGN;
    std::vector<std::vector<int>> up;

    KthAncestor(int n, const std::vector<int>& parent) {
        LOGN = 18;
        up.assign(n, std::vector<int>(LOGN, -1));
        for (int i = 0; i < n; ++i) up[i][0] = parent[i];

        for (int j = 1; j < LOGN; ++j) {
            for (int i = 0; i < n; ++i) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
    }

    int get_kth(int node, int k) {
        for (int i = 0; i < LOGN; ++i) {
            if (k & (1 << i)) {
                node = up[node][i];
                if (node == -1) break;
            }
        }
        return node;
    }
};

int main() {
    std::vector<int> parent = {-1, 0, 0, 1, 1, 2, 2};
    KthAncestor ka(7, parent);
    assert(ka.get_kth(3, 1) == 1);
    assert(ka.get_kth(3, 2) == 0);
    assert(ka.get_kth(3, 3) == -1);
    return 0;
}
