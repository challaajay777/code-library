#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Polya Enumeration Theorem (Bracelet Counting)
// Purpose: Counts number of distinct bracelets of N beads with K colors under rotation and reflection (dihedral group D_n).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 1, k >= 1.

class PolyaBracelet {
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
    static long long count_bracelets(int n, int k, long long mod = 1e9 + 7) {
        long long sum = 0;

        // Rotations
        for (int i = 0; i < n; ++i) {
            sum = (sum + power(k, std::gcd(i, n), mod)) % mod;
        }

        // Reflections
        if (n % 2 == 1) {
            sum = (sum + (long long)n * power(k, (n + 1) / 2, mod)) % mod;
        } else {
            long long refl1 = (long long)(n / 2) * power(k, n / 2 + 1, mod) % mod;
            long long refl2 = (long long)(n / 2) * power(k, n / 2, mod) % mod;
            sum = (sum + refl1 + refl2) % mod;
        }

        long long inv_2n = power(2 * n, mod - 2, mod);
        return (sum * inv_2n) % mod;
    }
};

int main() {
    // 4 beads, 2 colors under rotation and reflection: 6 necklaces -> 6 bracelets?
    // Reflections: 2 through vertices (cycles 1+1+2/2=3), 2 through edges (cycles 2).
    // Sum = 24 + 2 * 2^3 + 2 * 2^2 = 24 + 16 + 8 = 48. 48 / 8 = 6 bracelets
    assert(PolyaBracelet::count_bracelets(4, 2) == 6);

    std::cout << "polya_enumeration_bracelet tests passed successfully.\n";
    return 0;
}
