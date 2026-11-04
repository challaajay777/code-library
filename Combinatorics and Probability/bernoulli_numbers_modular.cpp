#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Bernoulli Numbers Modulo P
// Purpose: Computes first N Bernoulli numbers B_n modulo prime P in O(N^2) using recurrence sum_{k=0}^m C(m+1, k) * B_k = 0.
// Time Complexity: O(N^2) time
// Space Complexity: O(N) space
// Preconditions: Modulus P is prime > N + 1.

class ModularBernoulli {
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
    static std::vector<long long> compute_bernoulli(int n, long long p) {
        std::vector<long long> b(n + 1, 0);
        b[0] = 1;

        std::vector<std::vector<long long>> c(n + 2, std::vector<long long>(n + 2, 0));
        for (int i = 0; i <= n + 1; ++i) {
            c[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
            }
        }

        for (int m = 1; m <= n; ++m) {
            long long sum = 0;
            for (int k = 0; k < m; ++k) {
                sum = (sum + c[m + 1][k] * b[k]) % p;
            }
            long long inv_coeff = power(c[m + 1][m], p - 2, p);
            b[m] = (-sum % p + p) % p * inv_coeff % p;
        }
        return b;
    }
};

int main() {
    auto b = ModularBernoulli::compute_bernoulli(4, 1000000007);
    // B_0 = 1, B_1 = -1/2, B_2 = 1/6, B_3 = 0, B_4 = -1/30
    assert(b[0] == 1);
    assert(b[3] == 0); // odd Bernoulli numbers >= 3 are zero

    std::cout << "bernoulli_numbers_modular tests passed successfully.\n";
    return 0;
}
