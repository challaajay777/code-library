// Algorithm: Shortest Palindromic Prefix & Suffix Cuts
// Purpose: Finds minimum operations to make string a palindrome by prepending or appending characters using KMP/Z.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Non-empty string.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct PalindromeCut {
    static int longest_prefix_palindrome(const std::string& s) {
        std::string rev = s;
        std::reverse(rev.begin(), rev.end());
        std::string temp = s + '#' + rev;
        int m = temp.size();
        std::vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && temp[i] != temp[j]) j = pi[j - 1];
            if (temp[i] == temp[j]) ++j;
            pi[i] = j;
        }
        return pi[m - 1];
    }

    static std::string shortest_palindrome_by_prepending(const std::string& s) {
        int lpp = longest_prefix_palindrome(s);
        std::string suffix_rem = s.substr(lpp);
        std::reverse(suffix_rem.begin(), suffix_rem.end());
        return suffix_rem + s;
    }
};

int main() {
    std::string s = "aacecaaa";
    // Longest prefix palindrome is "aacecaa" (len 7)
    assert(PalindromeCut::longest_prefix_palindrome(s) == 7);
    assert(PalindromeCut::shortest_palindrome_by_prepending(s) == "aaacecaaa");

    std::string s2 = "abcd";
    assert(PalindromeCut::longest_prefix_palindrome(s2) == 1);
    assert(PalindromeCut::shortest_palindrome_by_prepending(s2) == "dcbabcd");
    return 0;
}
