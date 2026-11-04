#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Multi-Base String Hashing
// Purpose: Double polynomial string hashing using two independent prime bases and moduli to reduce collision probability to ~10^-18.
// Time Complexity: O(N) preprocessing, O(1) per range hash query
// Space Complexity: O(N) space
// Preconditions: ASCII string characters.

class DoubleStringHash {
private:
    static const long long MOD1 = 1000000007;
    static const long long MOD2 = 1000000009;
    static const long long BASE1 = 313;
    static const long long BASE2 = 317;

    std::vector<long long> h1, h2;
    std::vector<long long> p1, p2;

public:
    explicit DoubleStringHash(const std::string& s) {
        int n = s.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            h1[i + 1] = (h1[i] * BASE1 + s[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + s[i]) % MOD2;
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    std::pair<long long, long long> get_hash(int l, int r) const {
        long long hash1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % MOD1;
        if (hash1 < 0) hash1 += MOD1;

        long long hash2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % MOD2;
        if (hash2 < 0) hash2 += MOD2;

        return {hash1, hash2};
    }
};

int main() {
    std::string s = "abacaba";
    DoubleStringHash dsh(s);

    assert(dsh.get_hash(0, 2) == dsh.get_hash(4, 6)); // "aba" == "aba"
    assert(dsh.get_hash(0, 2) != dsh.get_hash(1, 3)); // "aba" != "bac"

    std::cout << "string_hashing_multi_base tests passed successfully.\n";
    return 0;
}
