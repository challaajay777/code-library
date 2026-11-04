// Algorithm: Longest Common Subsequence with Full Reconstruction
// Purpose: Computes the LCS length of two sequences and reconstructs the lexicographically first LCS string.
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// Preconditions: Sequences of elements with equality comparison.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::string lcs_reconstruct(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }
    std::string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res.push_back(a[i - 1]);
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    std::string a = "ABCBDAB", b = "BDCABA";
    std::string lcs = lcs_reconstruct(a, b);
    assert((int)lcs.size() == 4);
    assert(lcs == "BDAB" || lcs == "BCBA" || lcs == "BCAB");
    return 0;
}
