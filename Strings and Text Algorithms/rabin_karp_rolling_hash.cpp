#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Rabin-Karp Rolling Hash Pattern Search
// Purpose: Finds pattern occurrences using rolling polynomial hash in O(N + M) average time.
// Time Complexity: O(N + M) average time, O(N * M) worst case
// Space Complexity: O(1) auxiliary space
// Preconditions: 64-bit integer hash values.

class RabinKarp {
public:
    static std::vector<int> search(const std::string& text, const std::string& pat) {
        int n = text.size(), m = pat.size();
        if (n < m) return {};

        const long long MOD = 1000000007;
        const long long BASE = 256;

        long long p_hash = 0, t_hash = 0, h = 1;
        for (int i = 0; i < m - 1; ++i) {
            h = (h * BASE) % MOD;
        }

        for (int i = 0; i < m; ++i) {
            p_hash = (p_hash * BASE + pat[i]) % MOD;
            t_hash = (t_hash * BASE + text[i]) % MOD;
        }

        std::vector<int> matches;
        for (int i = 0; i <= n - m; ++i) {
            if (p_hash == t_hash) {
                if (text.substr(i, m) == pat) {
                    matches.push_back(i);
                }
            }
            if (i < n - m) {
                t_hash = (BASE * (t_hash - text[i] * h) + text[i + m]) % MOD;
                if (t_hash < 0) t_hash += MOD;
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "GEEKS FOR GEEKS";
    std::string pat = "GEEK";
    auto res = RabinKarp::search(text, pat);
    std::vector<int> expected = {0, 10};
    assert(res == expected);

    std::cout << "rabin_karp_rolling_hash tests passed successfully.\n";
    return 0;
}
