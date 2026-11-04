// Algorithm: Egg Dropping Puzzle DP with Binary Search
// Purpose: Finds minimum attempts needed in worst case to find critical floor with K eggs and N floors.
// Time Complexity: O(K * N)
// Space Complexity: O(K * N)
// Preconditions: k >= 1, n >= 1.

#include <iostream>
#include <vector>
#include <cassert>

int egg_drop(int k, int n) {
    // dp[m][k] = maximum floors that can be checked with m moves and k eggs
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
    int m = 0;
    while (dp[m][k] < n) {
        m++;
        for (int i = 1; i <= k; ++i) {
            dp[m][i] = dp[m - 1][i - 1] + dp[m - 1][i] + 1;
        }
    }
    return m;
}

int main() {
    assert(egg_drop(1, 2) == 2);
    assert(egg_drop(2, 6) == 3);
    assert(egg_drop(3, 14) == 4);
    return 0;
}
