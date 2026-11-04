#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Wildcard Matching (Dynamic Programming)
// Purpose: Evaluates wildcard pattern matching where '?' matches any single character and '*' matches any sequence of characters in O(N * M).
// Time Complexity: O(N * M) time
// Space Complexity: O(N * M) space
// Preconditions: String characters printable ASCII.

class WildcardDP {
public:
    static bool is_match(const std::string& s, const std::string& p) {
        int m = s.size(), n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    assert(WildcardDP::is_match("aa", "a") == false);
    assert(WildcardDP::is_match("aa", "*") == true);
    assert(WildcardDP::is_match("cb", "?a") == false);
    assert(WildcardDP::is_match("adceb", "*a*b") == true);

    std::cout << "wildcard_pattern_matching_dp tests passed successfully.\n";
    return 0;
}
