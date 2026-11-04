#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Burnside's Lemma (Necklace Counting Under Rotation)
// Purpose: Counts the number of distinct necklaces of N beads using K colors up to rotational symmetry.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 1, k >= 1.

class BurnsideNecklace {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static long long count_necklaces(int n, int k, long long mod = 1e9 + 7) {
        long long sum_fixed = 0;
        for (int i = 0; i < n; ++i) {
            int g = std::gcd(i, n);
            sum_fixed = (sum_fixed + power(k, g, mod)) % mod;
        }
        long long inv_n = power(n, mod - 2, mod);
        return (sum_fixed * inv_n) % mod;
    }
};

int main() {
    // 4 beads, 2 colors: total distinct under rotation = (2^4 + 2^1 + 2^2 + 2^1) / 4 = 24 / 4 = 6
    assert(BurnsideNecklace::count_necklaces(4, 2) == 6);

    std::cout << "burnside_lemma_necklace tests passed successfully.\n";
    return 0;
}
