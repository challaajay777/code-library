#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Algorithm: Prefix Frequency Counts
// Purpose: Maintains prefix count histograms for bounded alphabets/values to answer range frequency queries in O(Sigma).
// Time Complexity: O(N * Sigma) preprocessing, O(Sigma) per range query
// Space Complexity: O(N * Sigma) auxiliary space
// Preconditions: Alphabet size Sigma is small (typically <= 26 for lowercase letters).

class PrefixFrequencies {
private:
    int n;
    int sigma;
    std::vector<std::vector<int>> pref;

public:
    PrefixFrequencies(const std::string& s, int alphabet_size = 26, char base_char = 'a')
        : n(s.size()), sigma(alphabet_size), pref(alphabet_size, std::vector<int>(n + 1, 0)) {
        for (int i = 0; i < n; ++i) {
            int c = s[i] - base_char;
            for (int ch = 0; ch < sigma; ++ch) {
                pref[ch][i + 1] = pref[ch][i] + (ch == c ? 1 : 0);
            }
        }
    }

    int count(int l, int r, char ch, char base_char = 'a') const {
        assert(l >= 0 && r < n && l <= r);
        int c = ch - base_char;
        assert(c >= 0 && c < sigma);
        return pref[c][r + 1] - pref[c][l];
    }

    // Check if substring s[l..r] can be rearranged into a palindrome
    bool can_form_palindrome(int l, int r) const {
        int odd_count = 0;
        for (int c = 0; c < sigma; ++c) {
            if ((pref[c][r + 1] - pref[c][l]) % 2 != 0) {
                odd_count++;
            }
        }
        return odd_count <= 1;
    }
};

int main() {
    std::string s = "abacaba";
    PrefixFrequencies pf(s, 26, 'a');

    assert(pf.count(0, 6, 'a') == 4);
    assert(pf.count(0, 6, 'b') == 2);
    assert(pf.count(0, 6, 'c') == 1);
    assert(pf.count(1, 3, 'a') == 1);
    assert(pf.count(1, 3, 'b') == 1);

    assert(pf.can_form_palindrome(0, 6) == true);
    assert(pf.can_form_palindrome(0, 2) == true); // "aba"
    assert(pf.can_form_palindrome(0, 3) == false); // "abac"

    std::cout << "prefix_frequencies tests passed successfully.\n";
    return 0;
}
