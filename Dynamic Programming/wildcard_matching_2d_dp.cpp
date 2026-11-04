// Algorithm: Wildcard Pattern Matching 2D DP
// Purpose: Matches string against pattern containing '?' (any single character) and '*' (any sequence).
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// Preconditions: String and pattern with ascii characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

bool is_wildcard_match(const std::string& s, const std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= m; ++j) {
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}

int main() {
    assert(is_wildcard_match("aa", "*"));
    assert(!is_wildcard_match("cb", "?a"));
    assert(is_wildcard_match("adceb", "*a*b"));
    return 0;
}
