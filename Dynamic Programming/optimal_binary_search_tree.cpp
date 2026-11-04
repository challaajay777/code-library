// Algorithm: Optimal Binary Search Tree Interval DP
// Purpose: Calculates minimum search cost for binary search tree given key frequencies.
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: Sorted keys and positive frequencies.

#include <iostream>
#include <vector>
#include <cassert>
#include <climits>

int optimal_bst_cost(const std::vector<int>& freq) {
    int n = freq.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    std::vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + freq[i];

    auto sum = [&](int i, int j) {
        return pref[j + 1] - pref[i];
    };

    for (int i = 0; i < n; ++i) dp[i][i] = freq[i];

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            int s = sum(i, j);
            for (int r = i; r <= j; ++r) {
                int left = (r > i) ? dp[i][r - 1] : 0;
                int right = (r < j) ? dp[r + 1][j] : 0;
                dp[i][j] = std::min(dp[i][j], left + right + s);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> freq = {34, 8, 50};
    assert(optimal_bst_cost(freq) == 142);
    return 0;
}
