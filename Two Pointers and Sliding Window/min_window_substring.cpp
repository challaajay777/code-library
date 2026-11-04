#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Minimum Window Substring
// Purpose: Finds the minimum length substring of S that contains all characters of pattern T in O(|S| + |T|).
// Time Complexity: O(|S| + |T|) time
// Space Complexity: O(Sigma) space for character frequency table
// Preconditions: String characters in ASCII range.

class MinimumWindowSubstring {
public:
    static std::string min_window(const std::string& s, const std::string& t) {
        if (s.empty() || t.empty() || s.size() < t.size()) return "";

        std::vector<int> need(128, 0);
        for (char c : t) need[(unsigned char)c]++;

        int remaining = t.size();
        int left = 0, min_start = 0, min_len = 1e9;

        for (int right = 0; right < (int)s.size(); ++right) {
            if (need[(unsigned char)s[right]] > 0) {
                remaining--;
            }
            need[(unsigned char)s[right]]--;

            while (remaining == 0) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    min_start = left;
                }
                need[(unsigned char)s[left]]++;
                if (need[(unsigned char)s[left]] > 0) {
                    remaining++;
                }
                left++;
            }
        }
        return (min_len == 1e9) ? "" : s.substr(min_start, min_len);
    }
};

int main() {
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";
    assert(MinimumWindowSubstring::min_window(s, t) == "BANC");

    assert(MinimumWindowSubstring::min_window("a", "a") == "a");
    assert(MinimumWindowSubstring::min_window("a", "aa") == "");

    std::cout << "min_window_substring tests passed successfully.\n";
    return 0;
}
