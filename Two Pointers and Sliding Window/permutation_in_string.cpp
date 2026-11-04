#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Permutation in String (Sliding Window Frequency Match)
// Purpose: Determines whether string s2 contains a contiguous permutation of string s1 in O(|s2|) time.
// Time Complexity: O(|s2|) time
// Space Complexity: O(26) space
// Preconditions: Strings consist of lowercase English letters.

class PermutationInString {
public:
    static bool check_inclusion(const std::string& s1, const std::string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n1 > n2) return false;

        std::vector<int> count1(26, 0), count2(26, 0);
        for (int i = 0; i < n1; ++i) {
            count1[s1[i] - 'a']++;
            count2[s2[i] - 'a']++;
        }

        int matches = 0;
        for (int i = 0; i < 26; ++i) {
            if (count1[i] == count2[i]) matches++;
        }

        for (int i = 0; i < n2 - n1; ++i) {
            if (matches == 26) return true;

            int right = s2[i + n1] - 'a';
            int left = s2[i] - 'a';

            count2[right]++;
            if (count2[right] == count1[right]) matches++;
            else if (count2[right] == count1[right] + 1) matches--;

            count2[left]--;
            if (count2[left] == count1[left]) matches++;
            else if (count2[left] == count1[left] - 1) matches--;
        }
        return matches == 26;
    }
};

int main() {
    assert(PermutationInString::check_inclusion("ab", "eidbaooo") == true);
    assert(PermutationInString::check_inclusion("ab", "eidboaoo") == false);

    std::cout << "permutation_in_string tests passed successfully.\n";
    return 0;
}
