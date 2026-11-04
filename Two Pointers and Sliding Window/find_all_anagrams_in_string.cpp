#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Find All Anagrams in a String
// Purpose: Finds all start indices of anagrams of pattern P in string S in O(|S|) time using sliding window.
// Time Complexity: O(|S|) time
// Space Complexity: O(26) space
// Preconditions: Strings consist of lowercase English letters.

class FindAllAnagrams {
public:
    static std::vector<int> find_anagrams(const std::string& s, const std::string& p) {
        int ns = s.size(), np = p.size();
        if (ns < np) return {};

        std::vector<int> p_count(26, 0), s_count(26, 0);
        for (int i = 0; i < np; ++i) {
            p_count[p[i] - 'a']++;
            s_count[s[i] - 'a']++;
        }

        std::vector<int> result;
        if (p_count == s_count) result.push_back(0);

        for (int i = np; i < ns; ++i) {
            s_count[s[i] - 'a']++;
            s_count[s[i - np] - 'a']--;
            if (s_count == p_count) {
                result.push_back(i - np + 1);
            }
        }
        return result;
    }
};

int main() {
    std::string s = "cbaebabacd";
    std::string p = "abc";
    auto idxs = FindAllAnagrams::find_anagrams(s, p);
    std::vector<int> expected = {0, 6};
    assert(idxs == expected);

    std::cout << "find_all_anagrams_in_string tests passed successfully.\n";
    return 0;
}
