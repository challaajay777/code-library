// Algorithm: Longest Common Increasing Subsequence (LCIS)
// Purpose: Finds the length of the longest subsequence common to both arrays that is strictly increasing.
// Time Complexity: O(N * M)
// Space Complexity: O(M)
// Preconditions: Two integer arrays.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int lcis(const std::vector<int>& a, const std::vector<int>& b) {
    int n = a.size(), m = b.size();
    std::vector<int> dp(m, 0);

    for (int i = 0; i < n; ++i) {
        int current_max = 0;
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                dp[j] = std::max(dp[j], current_max + 1);
            }
            if (a[i] > b[j]) {
                current_max = std::max(current_max, dp[j]);
            }
        }
    }
    int ans = 0;
    for (int x : dp) ans = std::max(ans, x);
    return ans;
}

int main() {
    std::vector<int> a = {3, 4, 9, 1};
    std::vector<int> b = {5, 3, 8, 9, 4, 1};
    // LCIS: {3, 9} (len 2)
    assert(lcis(a, b) == 2);
    return 0;
}
