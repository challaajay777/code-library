// Algorithm: Tree Metric Recognition (Four-Point Condition)
// Purpose: Tests if a distance matrix represents a tree metric using Buneman's 4-point condition.
// Time Complexity: O(N^4)
// Space Complexity: O(N^2)
// Preconditions: Symmetric distance matrix with zero diagonal.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

bool is_tree_metric(int n, const std::vector<std::vector<int>>& d) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                for (int l = k + 1; l < n; ++l) {
                    std::vector<int> sums = {
                        d[i][j] + d[k][l],
                        d[i][k] + d[j][l],
                        d[i][l] + d[j][k]
                    };
                    std::sort(sums.begin(), sums.end());
                    // The two largest sums must be equal
                    if (sums[1] != sums[2]) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    // Star tree: center 0, leaves 1, 2, 3
    int n = 4;
    std::vector<std::vector<int>> d = {
        {0, 1, 1, 1},
        {1, 0, 2, 2},
        {1, 2, 0, 2},
        {1, 2, 2, 0}
    };
    assert(is_tree_metric(n, d));
    return 0;
}
