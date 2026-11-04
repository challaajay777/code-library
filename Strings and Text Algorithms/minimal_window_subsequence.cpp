#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Minimal Window Subsequence
// Purpose: Finds smallest contiguous substring in S that contains string T as a subsequence in O(|S| * |T|).
// Time Complexity: O(|S| * |T|) time
// Space Complexity: O(|S| * |T|) space
// Preconditions: Non-empty strings S and T.

class MinWindowSubsequence {
public:
    static std::string min_window(const std::string& s, const std::string& t) {
        int m = s.size(), n = t.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, -1));

        for (int i = 0; i <= m; ++i) dp[i][0] = i;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        int min_len = 1e9, start = -1;
        for (int i = 1; i <= m; ++i) {
            if (dp[i][n] != -1) {
                int len = i - dp[i][n];
                if (len < min_len) {
                    min_len = len;
                    start = dp[i][n];
                }
            }
        }
        return (start == -1) ? "" : s.substr(start, min_len);
    }
};

int main() {
    std::string s = "abcdebdde";
    std::string t = "bde";
    assert(MinWindowSubsequence::min_window(s, t) == "bcde");

    std::cout << "minimal_window_subsequence tests passed successfully.\n";
    return 0;
}
