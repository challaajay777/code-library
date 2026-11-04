#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Z-Algorithm for Pattern Matching
// Purpose: Finds all occurrences of pattern in text in O(N + M) time using Z-array on combined string P + '$' + T.
// Time Complexity: O(N + M) time
// Space Complexity: O(N + M) space
// Preconditions: Sentinel '$' does not appear in text or pattern.

class ZAlgorithm {
public:
    static std::vector<int> compute_z(const std::string& s) {
        int n = s.size();
        std::vector<int> z(n, 0);
        int l = 0, r = 0;

        for (int i = 1; i < n; ++i) {
            if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    static std::vector<int> match(const std::string& text, const std::string& pattern) {
        std::string concat = pattern + "$" + text;
        auto z = compute_z(concat);
        std::vector<int> matches;
        int m = pattern.size();

        for (size_t i = m + 1; i < z.size(); ++i) {
            if (z[i] == m) {
                matches.push_back(i - m - 1);
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "baabaa";
    std::string pat = "aab";
    auto m = ZAlgorithm::match(text, pat);
    assert(m.size() == 1 && m[0] == 1);

    std::cout << "z_algorithm_search tests passed successfully.\n";
    return 0;
}
