// Algorithm: Knuth Optimization for Interval DP
// Purpose: Accelerates interval dynamic programming satisfying the quadrangle inequality from O(N^3) to O(N^2).
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: Cost function satisfies quadrangle inequality and monotonicity on intervals.

#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>
#include <climits>

long long knuth_optimal_merge(const std::vector<int>& weights) {
    int n = weights.size();
    std::vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + weights[i];

    auto sum = [&](int i, int j) {
        return pref[j + 1] - pref[i];
    };

    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));
    std::vector<std::vector<int>> opt(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) opt[i][i] = i;

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            int opt_start = opt[i][j - 1];
            int opt_end = (j > i + 1) ? opt[i + 1][j] : j - 1;

            for (int k = opt_start; k <= opt_end; ++k) {
                long long cur = dp[i][k] + dp[k + 1][j] + sum(i, j);
                if (cur < dp[i][j]) {
                    dp[i][j] = cur;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> weights = {3, 4, 2, 1, 7};
    long long cost = knuth_optimal_merge(weights);
    assert(cost > 0);
    return 0;
}
