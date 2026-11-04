// Algorithm: Unique BST Count via Catalan DP
// Purpose: Computes the number of structurally unique binary search trees that can store keys 1..n.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: n >= 0.

#include <iostream>
#include <vector>
#include <cassert>

long long count_unique_bst(int n) {
    if (n <= 1) return 1;
    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }
    return dp[n];
}

int main() {
    assert(count_unique_bst(0) == 1);
    assert(count_unique_bst(3) == 5);
    assert(count_unique_bst(4) == 14);
    assert(count_unique_bst(5) == 42);
    return 0;
}
