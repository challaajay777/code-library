#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Regular Expression Matching ('.' and '*')
// Purpose: Implements full regular expression matcher supporting '.' (any character) and '*' (zero or more of preceding element).
// Time Complexity: O(N * M) time
// Space Complexity: O(N * M) space
// Preconditions: Valid regex pattern string.

class RegexMatchingDP {
public:
    static bool is_match(const std::string& s, const std::string& p) {
        int m = s.size(), n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int j = 2; j <= n; j += 2) {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '.' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2]; // zero occurrences
                    if (p[j - 2] == '.' || s[i - 1] == p[j - 2]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    assert(RegexMatchingDP::is_match("aa", "a*") == true);
    assert(RegexMatchingDP::is_match("ab", ".*") == true);
    assert(RegexMatchingDP::is_match("aab", "c*a*b") == true);
    assert(RegexMatchingDP::is_match("mississippi", "mis*is*p*.") == false);

    std::cout << "regular_expression_matching_dp tests passed successfully.\n";
    return 0;
}
