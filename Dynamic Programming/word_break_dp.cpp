// Algorithm: Word Break Problem DP
// Purpose: Determines if a string can be segmented into a space-separated sequence of dictionary words.
// Time Complexity: O(N^2)
// Space Complexity: O(N + TotalDictChars)
// Preconditions: String s and dictionary of non-empty words.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cassert>

bool word_break(const std::string& s, const std::vector<std::string>& dict) {
    std::unordered_set<std::string> word_set(dict.begin(), dict.end());
    int n = s.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && word_set.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

int main() {
    std::vector<std::string> dict = {"apple", "pen"};
    assert(word_break("applepenapple", dict));
    assert(!word_break("catsandog", {"cats", "dog", "sand", "and", "cat"}));
    return 0;
}
