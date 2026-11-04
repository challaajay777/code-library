// Algorithm: Interleaving String DP Check
// Purpose: Determines whether string s3 is formed by an interleaving of strings s1 and s2.
// Time Complexity: O(N * M)
// Space Complexity: O(M)
// Preconditions: |s1| + |s2| == |s3|.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

bool is_interleave(const std::string& s1, const std::string& s2, const std::string& s3) {
    if (s1.size() + s2.size() != s3.size()) return false;
    int n = s1.size(), m = s2.size();
    std::vector<bool> dp(m + 1, false);

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 && j == 0) {
                dp[j] = true;
            } else if (i == 0) {
                dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
            } else if (j == 0) {
                dp[j] = dp[j] && (s1[i - 1] == s3[i - 1]);
            } else {
                dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                        (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
    }
    return dp[m];
}

int main() {
    assert(is_interleave("aabcc", "dbbca", "aadbbcbcac"));
    assert(!is_interleave("aabcc", "dbbca", "aadbbbaccc"));
    return 0;
}
