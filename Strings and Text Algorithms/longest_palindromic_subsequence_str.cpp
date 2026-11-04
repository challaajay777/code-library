#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Palindromic Subsequence (Reconstruction)
// Purpose: Computes the length and reconstructs the actual longest palindromic subsequence string in O(N^2).
// Time Complexity: O(N^2) time
// Space Complexity: O(N^2) space
// Preconditions: Non-empty string.

class PalindromicSubsequence {
public:
    static std::string get_longest_palindrome(const std::string& s) {
        int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        for (int i = 0; i < n; ++i) dp[i][i] = 1;

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        // Reconstruction
        int i = 0, j = n - 1;
        std::string left = "", right = "";

        while (i <= j) {
            if (i == j) {
                left.push_back(s[i]);
                break;
            }
            if (s[i] == s[j]) {
                left.push_back(s[i]);
                right.push_back(s[j]);
                i++;
                j--;
            } else if (dp[i + 1][j] >= dp[i][j - 1]) {
                i++;
            } else {
                j--;
            }
        }
        std::reverse(right.begin(), right.end());
        return left + right;
    }
};

int main() {
    std::string s = "bbbab";
    auto lps = PalindromicSubsequence::get_longest_palindrome(s);
    assert(lps.size() == 4); // "bbbb"

    std::cout << "longest_palindromic_subsequence_str tests passed successfully.\n";
    return 0;
}
