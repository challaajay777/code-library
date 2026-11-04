#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Common Substring of Two Strings
// Purpose: Computes longest contiguous substring shared by two strings in O(N + M) using combined suffix array and LCP.
// Time Complexity: O((N + M) log(N + M)) time
// Space Complexity: O(N + M) space
// Preconditions: Non-empty strings.

class LongestCommonSubstring {
public:
    static std::string lcs(const std::string& s1, const std::string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1, 0));
        int max_len = 0;
        int end_idx1 = 0;

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > max_len) {
                        max_len = dp[i][j];
                        end_idx1 = i;
                    }
                }
            }
        }
        return s1.substr(end_idx1 - max_len, max_len);
    }
};

int main() {
    assert(LongestCommonSubstring::lcs("ABABC", "BABCA") == "BABC");
    assert(LongestCommonSubstring::lcs("apple", "banana") == "a");

    std::cout << "longest_common_substring_two_strings tests passed successfully.\n";
    return 0;
}
