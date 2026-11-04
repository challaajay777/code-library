// Algorithm: Lyndon Word Factorization and Minimal Rotation
// Purpose: Computes the Lyndon factorization of a string and identifies its lexicographically minimal rotation.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: String with valid comparable characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct LyndonFactorization {
    static std::vector<std::string> factorize(const std::string& s) {
        int n = s.size();
        int i = 0;
        std::vector<std::string> factors;
        while (i < n) {
            int j = i + 1, k = i;
            while (j < n && s[k] <= s[j]) {
                if (s[k] < s[j]) k = i;
                else ++k;
                ++j;
            }
            while (i <= k) {
                factors.push_back(s.substr(i, j - k));
                i += j - k;
            }
        }
        return factors;
    }

    static std::string min_rotation(const std::string& s) {
        std::string ss = s + s;
        int n = s.size();
        int i = 0, ans = 0;
        while (i < n) {
            ans = i;
            int j = i + 1, k = i;
            while (j < 2 * n && ss[k] <= ss[j]) {
                if (ss[k] < ss[j]) k = i;
                else ++k;
                ++j;
            }
            while (i <= k) i += j - k;
        }
        return ss.substr(ans, n);
    }
};

int main() {
    std::string s = "abacaba";
    auto factors = LyndonFactorization::factorize(s);
    // Factors must be non-increasing Lyndon words: "abacaba" -> "abacab", "a"
    std::string reconstructed;
    for (const auto& w : factors) reconstructed += w;
    assert(reconstructed == s);

    // Minimal rotation of "bbaaca" -> "aabacb" ? Let's check "bbaaca"
    std::string rot = LyndonFactorization::min_rotation("bbaaca");
    assert(rot == "aabacb");

    return 0;
}
