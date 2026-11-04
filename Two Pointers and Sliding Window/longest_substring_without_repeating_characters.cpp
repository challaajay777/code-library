#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Substring Without Repeating Characters
// Purpose: Finds the length of the longest contiguous substring containing all distinct characters in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(Sigma) auxiliary space
// Preconditions: String characters in ASCII range.

class LongestSubstringDistinct {
public:
    static int length_of_longest_substring(const std::string& s) {
        std::vector<int> last_pos(256, -1);
        int max_len = 0;
        int left = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char c = s[right];
            if (last_pos[c] >= left) {
                left = last_pos[c] + 1;
            }
            last_pos[c] = right;
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    assert(LongestSubstringDistinct::length_of_longest_substring("abcabcbb") == 3);
    assert(LongestSubstringDistinct::length_of_longest_substring("bbbbb") == 1);
    assert(LongestSubstringDistinct::length_of_longest_substring("pwwkew") == 3);

    std::cout << "longest_substring_without_repeating_characters tests passed successfully.\n";
    return 0;
}
