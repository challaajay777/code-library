// Algorithm: Longest Repeating Subsequence DP
// Purpose: Finds the length of the longest subsequence that appears at least twice without using the same indices.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: String of characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int longest_repeating_subsequence(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

int main() {
    std::string s = "AABEBCDD";
    // Repeating subsequence: "ABD" of length 3
    assert(longest_repeating_subsequence(s) == 3);
    return 0;
}
