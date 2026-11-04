// Algorithm: Longest Valid Parentheses Substring DP
// Purpose: Finds the length of the longest valid (well-formed) parentheses substring.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: String of '(' and ')' characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int longest_valid_parentheses(const std::string& s) {
    int n = s.size();
    std::vector<int> dp(n, 0);
    int max_len = 0;

    for (int i = 1; i < n; ++i) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + ((i - dp[i - 1] >= 2) ? dp[i - dp[i - 1] - 2] : 0) + 2;
            }
            max_len = std::max(max_len, dp[i]);
        }
    }
    return max_len;
}

int main() {
    assert(longest_valid_parentheses(")()())") == 4);
    assert(longest_valid_parentheses("(()") == 2);
    assert(longest_valid_parentheses("") == 0);
    return 0;
}
