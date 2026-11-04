#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Modular Catalan Numbers
// Purpose: Computes first N Catalan numbers C_n = (2n)! / ((n+1)! * n!) modulo prime P in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Modulus P is prime > 2*N.

class ModularCatalan {
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
    static std::vector<long long> compute_catalan(int n, long long p) {
        std::vector<long long> cat(n + 1);
        cat[0] = 1;

        for (int i = 0; i < n; ++i) {
            long long num = (2LL * (2LL * i + 1)) % p;
            long long den = (i + 2) % p;
            long long inv_den = power(den, p - 2, p);
            cat[i + 1] = cat[i] * num % p * inv_den % p;
        }
        return cat;
    }
};

int main() {
    auto cat = ModularCatalan::compute_catalan(5, 1000000007);
    // Catalan numbers: 1, 1, 2, 5, 14, 42
    std::vector<long long> expected = {1, 1, 2, 5, 14, 42};
    assert(cat == expected);

    std::cout << "catalan_numbers_modular tests passed successfully.\n";
    return 0;
}
