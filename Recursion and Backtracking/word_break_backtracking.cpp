#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

// Algorithm: Word Break II (Sentence Generation)
// Purpose: Constructs all valid sentences formed by inserting spaces in string S such that each word is in the dictionary.
// Time Complexity: O(2^N) worst case
// Space Complexity: O(N^2) memoization table
// Preconditions: Non-empty string and dictionary.

class WordBreakSentences {
private:
    static std::vector<std::string> dfs(const std::string& s, const std::unordered_set<std::string>& dict,
                                        std::unordered_map<std::string, std::vector<std::string>>& memo) {
        if (memo.count(s)) return memo[s];
        if (s.empty()) return {""};

        std::vector<std::string> sentences;
        for (size_t len = 1; len <= s.size(); ++len) {
            std::string prefix = s.substr(0, len);
            if (dict.count(prefix)) {
                auto suffixes = dfs(s.substr(len), dict, memo);
                for (const auto& suf : suffixes) {
                    sentences.push_back(prefix + (suf.empty() ? "" : " ") + suf);
                }
            }
        }
        return memo[s] = sentences;
    }

public:
    static std::vector<std::string> word_break(const std::string& s, const std::vector<std::string>& word_dict) {
        std::unordered_set<std::string> dict(word_dict.begin(), word_dict.end());
        std::unordered_map<std::string, std::vector<std::string>> memo;
        return dfs(s, dict, memo);
    }
};

int main() {
    std::string s = "catsanddog";
    std::vector<std::string> dict = {"cat", "cats", "and", "sand", "dog"};
    auto sentences = WordBreakSentences::word_break(s, dict);
    // "cats and dog", "cat sand dog"
    assert(sentences.size() == 2);

    std::cout << "word_break_backtracking tests passed successfully.\n";
    return 0;
}
