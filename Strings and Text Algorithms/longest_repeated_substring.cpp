#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Longest Repeated Substring
// Purpose: Finds the longest substring that appears at least twice in a string in O(N log N) using SA and LCP.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: String length >= 1.

class LongestRepeatedSubstring {
public:
    static std::string find_longest_repeated(const std::string& s, const std::vector<int>& sa, const std::vector<int>& lcp) {
        int max_len = 0;
        int best_idx = -1;

        for (size_t i = 0; i < lcp.size(); ++i) {
            if (lcp[i] > max_len) {
                max_len = lcp[i];
                best_idx = sa[i];
            }
        }
        return (best_idx == -1) ? "" : s.substr(best_idx, max_len);
    }
};

int main() {
    std::string s = "banana";
    std::vector<int> sa = {5, 3, 1, 0, 4, 2};
    std::vector<int> lcp = {1, 3, 0, 0, 2};
    // Longest repeated substring is "ana" length 3
    assert(LongestRepeatedSubstring::find_longest_repeated(s, sa, lcp) == "ana");

    std::cout << "longest_repeated_substring tests passed successfully.\n";
    return 0;
}
