#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Knuth-Morris-Pratt (All Occurrences)
// Purpose: Finds all zero-indexed starting positions of pattern in text using KMP failure function in O(N + M).
// Time Complexity: O(N + M) time
// Space Complexity: O(M) space
// Preconditions: Arbitrary non-empty strings.

class KMPAllOccurrences {
public:
    static std::vector<int> compute_pi(const std::string& p) {
        int m = p.size();
        std::vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) j = pi[j - 1];
            if (p[i] == p[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    static std::vector<int> search(const std::string& text, const std::string& pattern) {
        int n = text.size(), m = pattern.size();
        if (m == 0 || n < m) return {};

        auto pi = compute_pi(pattern);
        std::vector<int> matches;
        int j = 0;

        for (int i = 0; i < n; ++i) {
            while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
            if (text[i] == pattern[j]) j++;
            if (j == m) {
                matches.push_back(i - m + 1);
                j = pi[j - 1];
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";
    auto occs = KMPAllOccurrences::search(text, pattern);
    std::vector<int> expected = {0, 9, 12};
    assert(occs == expected);

    std::cout << "kmp_all_occurrences tests passed successfully.\n";
    return 0;
}
