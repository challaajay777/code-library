// Algorithm: Distinct Subsequences Matching Count DP
// Purpose: Counts the number of distinct subsequences of string S that equal target string T.
// Time Complexity: O(N * M)
// Space Complexity: O(M)
// Preconditions: Strings s and t.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

long long num_distinct_subsequences(const std::string& s, const std::string& t) {
    int m = t.size();
    std::vector<unsigned long long> dp(m + 1, 0);
    dp[0] = 1;

    for (char c : s) {
        for (int j = m; j >= 1; --j) {
            if (c == t[j - 1]) {
                dp[j] += dp[j - 1];
            }
        }
    }
    return dp[m];
}

int main() {
    assert(num_distinct_subsequences("rabbbit", "rabbit") == 3);
    assert(num_distinct_subsequences("babgbag", "bag") == 5);
    return 0;
}
