#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Motzkin Numbers
// Purpose: Computes Motzkin numbers M(n) counting non-intersecting chords between n points on a circle in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: N >= 0.

class MotzkinNumbers {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static std::vector<long long> compute_motzkin(int n, long long mod = 1e9 + 7) {
        std::vector<long long> m(n + 1, 0);
        m[0] = 1;
        if (n >= 1) m[1] = 1;

        for (int i = 2; i <= n; ++i) {
            // (i + 2) * M(i) = (2*i + 1) * M(i-1) + 3 * (i - 1) * M(i-2)
            long long term1 = (2LL * i + 1) * m[i - 1] % mod;
            long long term2 = 3LL * (i - 1) % mod * m[i - 2] % mod;
            long long num = (term1 + term2) % mod;
            long long den_inv = power(i + 2, mod - 2, mod);
            m[i] = (num * den_inv) % mod;
        }
        return m;
    }
};

int main() {
    auto m = MotzkinNumbers::compute_motzkin(6);
    // Motzkin sequence: 1, 1, 2, 4, 9, 21, 51
    std::vector<long long> expected = {1, 1, 2, 4, 9, 21, 51};
    assert(m == expected);

    std::cout << "motzkin_numbers tests passed successfully.\n";
    return 0;
}
