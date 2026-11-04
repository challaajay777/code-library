// Algorithm: Integer Break Product Maximization DP
// Purpose: Breaks integer n into sum of at least two positive integers maximizing their product.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: n >= 2.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long integer_break(int n) {
    std::vector<long long> dp(n + 1, 0);
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            dp[i] = std::max({dp[i], 1LL * j * (i - j), 1LL * j * dp[i - j]});
        }
    }
    return dp[n];
}

int main() {
    assert(integer_break(2) == 1);
    assert(integer_break(10) == 36); // 3 + 3 + 4 -> 3 * 3 * 4 = 36
    return 0;
}
