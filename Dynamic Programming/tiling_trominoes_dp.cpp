// Algorithm: Domino and Tromino Tiling 2xN DP
// Purpose: Finds number of ways to tile a 2 x N board with dominoes and L-shaped trominoes modulo 10^9+7.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: N >= 1.

#include <iostream>
#include <vector>
#include <cassert>

long long domino_tromino_tiling(int n) {
    static const int MOD = 1000000007;
    if (n <= 1) return 1;
    if (n == 2) return 2;

    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1; dp[1] = 1; dp[2] = 2;

    for (int i = 3; i <= n; ++i) {
        // dp[i] = 2 * dp[i-1] + dp[i-3]
        dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
    }
    return dp[n];
}

int main() {
    assert(domino_tromino_tiling(3) == 5);
    assert(domino_tromino_tiling(1) == 1);
    return 0;
}
