#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Substring with At Most K Distinct Characters
// Purpose: Finds maximum length of a substring containing at most K unique characters in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(Sigma) space
// Preconditions: K >= 0.

class LongestSubstringKDistinct {
public:
    static int length_of_longest_k_distinct(const std::string& s, int k) {
        if (k == 0) return 0;
        std::vector<int> freq(256, 0);
        int distinct = 0;
        int left = 0;
        int max_len = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char c = s[right];
            if (freq[c] == 0) distinct++;
            freq[c]++;

            while (distinct > k) {
                unsigned char lc = s[left];
                freq[lc]--;
                if (freq[lc] == 0) distinct--;
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    std::string s = "eceba";
    assert(LongestSubstringKDistinct::length_of_longest_k_distinct(s, 2) == 3); // "ece"

    std::string s2 = "aa";
    assert(LongestSubstringKDistinct::length_of_longest_k_distinct(s2, 1) == 2);

    std::cout << "longest_substring_k_distinct tests passed successfully.\n";
    return 0;
}
