// Algorithm: Palindrome Partitioning Minimum Cuts DP
// Purpose: Finds minimum cuts needed to partition a string such that every part is a palindrome.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: Non-empty string.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int min_cut_palindrome(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<bool>> is_pal(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) is_pal[i][i] = true;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                is_pal[i][j] = (len == 2) ? true : is_pal[i + 1][j - 1];
            }
        }
    }

    std::vector<int> dp(n, 0);
    for (int i = 0; i < n; ++i) {
        if (is_pal[0][i]) {
            dp[i] = 0;
        } else {
            dp[i] = i;
            for (int j = 0; j < i; ++j) {
                if (is_pal[j + 1][i]) {
                    dp[i] = std::min(dp[i], dp[j] + 1);
                }
            }
        }
    }
    return dp[n - 1];
}

int main() {
    assert(min_cut_palindrome("aab") == 1); // "aa" | "b"
    assert(min_cut_palindrome("a") == 0);
    assert(min_cut_palindrome("ab") == 1);
    return 0;
}
