#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Multinomial Coefficient
// Purpose: Computes multinomial coefficient N! / (k1! * k2! * ... * km!) modulo prime P in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space for factorials
// Preconditions: sum(k_i) == N; prime mod P.

class Multinomial {
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
    static long long coefficient(const std::vector<int>& k, long long mod = 1e9 + 7) {
        int n = std::accumulate(k.begin(), k.end(), 0);
        std::vector<long long> fact(n + 1, 1);
        for (int i = 2; i <= n; ++i) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        long long num = fact[n];
        long long den = 1;
        for (int part : k) {
            den = (den * fact[part]) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }
};

int main() {
    // Permutations of "MISSISSIPPI": M=1, I=4, S=4, P=2. N = 11.
    // 11! / (1! * 4! * 4! * 2!) = 34650
    std::vector<int> k = {1, 4, 4, 2};
    assert(Multinomial::coefficient(k) == 34650);

    std::cout << "multinomial_coefficient tests passed successfully.\n";
    return 0;
}
