// Algorithm: Minimum Perfect Squares Sum DP
// Purpose: Finds least number of perfect square numbers which sum to n (Lagrange's 4-square theorem bounded).
// Time Complexity: O(N * sqrt(N))
// Space Complexity: O(N)
// Preconditions: n >= 1.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int num_squares(int n) {
    std::vector<int> dp(n + 1, 1e9);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            dp[i] = std::min(dp[i], dp[i - j * j] + 1);
        }
    }
    return dp[n];
}

int main() {
    assert(num_squares(12) == 3); // 4 + 4 + 4
    assert(num_squares(13) == 2); // 4 + 9
    return 0;
}
