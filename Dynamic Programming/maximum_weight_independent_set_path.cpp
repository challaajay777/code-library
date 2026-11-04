// Algorithm: Max Weight Independent Set on Path Graph
// Purpose: Computes max weight subset of elements with no two adjacent selected (House Robber problem).
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Array of non-negative weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long max_weight_path_independent_set(const std::vector<int>& weights) {
    long long prev2 = 0, prev1 = 0;
    for (int w : weights) {
        long long cur = std::max(prev1, prev2 + w);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    std::vector<int> weights = {2, 7, 9, 3, 1};
    // Choose 2 + 9 + 1 = 12
    assert(max_weight_path_independent_set(weights) == 12);
    return 0;
}
