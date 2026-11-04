#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Repeating Character Replacement
// Purpose: Finds the length of the longest substring containing identical letters after changing at most K letters in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(26) space
// Preconditions: String consists of uppercase English letters; K >= 0.

class CharacterReplacement {
public:
    static int character_replacement(const std::string& s, int k) {
        std::vector<int> count(26, 0);
        int max_freq = 0;
        int left = 0;
        int max_len = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            count[s[right] - 'A']++;
            max_freq = std::max(max_freq, count[s[right] - 'A']);

            // If remaining characters to change exceeds k, shrink window
            while ((right - left + 1) - max_freq > k) {
                count[s[left] - 'A']--;
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    assert(CharacterReplacement::character_replacement("ABAB", 2) == 4);
    assert(CharacterReplacement::character_replacement("AABABBA", 1) == 4);

    std::cout << "longest_repeating_character_replacement tests passed successfully.\n";
    return 0;
}
