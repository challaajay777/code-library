// Algorithm: Longest Palindromic Subsequence DP with Reconstruction
// Purpose: Computes the maximum length palindromic subsequence and reconstructs the palindromic string.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: String of length >= 1.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::string lps_reconstruct(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = (len == 2) ? 2 : dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    std::string left, right;
    int i = 0, j = n - 1;
    while (i <= j) {
        if (i == j) {
            left.push_back(s[i]);
            break;
        }
        if (s[i] == s[j]) {
            left.push_back(s[i]);
            right.push_back(s[j]);
            ++i; --j;
        } else if (dp[i + 1][j] >= dp[i][j - 1]) {
            ++i;
        } else {
            --j;
        }
    }
    std::reverse(right.begin(), right.end());
    return left + right;
}

int main() {
    std::string s = "bbbab";
    std::string lps = lps_reconstruct(s);
    assert((int)lps.size() == 4);
    assert(lps == "bbbb");
    return 0;
}
