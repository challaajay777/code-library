// Algorithm: Regular Expression Matching NFA DP
// Purpose: Matches string against regular expression with '.' and '*' characters via 2D DP.
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// Preconditions: String s and regex pattern p.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

bool is_regex_match(const std::string& s, const std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= m; ++j) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2]; // zero occurrences of previous char
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }
    return dp[n][m];
}

int main() {
    assert(is_regex_match("aa", "a*"));
    assert(is_regex_match("ab", ".*"));
    assert(!is_regex_match("mississippi", "mis*is*p*."));
    return 0;
}
