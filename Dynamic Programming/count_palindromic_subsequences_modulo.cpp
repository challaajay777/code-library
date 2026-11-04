// Algorithm: Count Distinct Palindromic Subsequences Modulo 10^9+7
// Purpose: Computes the total number of non-empty palindromic subsequences modulo 10^9+7.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: String of printable ASCII characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

long long count_palindromic_subsequences(const std::string& s) {
    static const int MOD = 1000000007;
    int n = s.size();
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) dp[i][i] = 1;

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
            } else {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::string s = "abcb";
    // Palindromic subsequences: "a", "b", "c", "b", "bcb", "bb" -> 6
    assert(count_palindromic_subsequences(s) == 6);
    return 0;
}
