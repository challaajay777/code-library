#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

// Algorithm: Min25 Sieve (Prime Counting Function pi(N))
// Purpose: Computes exact number of primes up to N in O(N^(3/4) / log N) time.
// Time Complexity: O(N^(3/4) / log N) time
// Space Complexity: O(sqrt(N)) space
// Preconditions: 1 <= N <= 10^11.

class Min25PrimeCount {
public:
    static long long pi(long long n) {
        if (n < 2) return 0;
        int v = std::sqrt(n);
        std::vector<long long> val;
        for (long long l = 1, r; l <= n; l = r + 1) {
            val.push_back(n / l);
            r = n / (n / l);
        }

        int m = val.size();
        std::vector<long long> g(m);
        for (int i = 0; i < m; ++i) {
            g[i] = val[i] - 1;
        }

        auto get_idx = [&](long long x) {
            return (x <= v) ? m - x : n / x - 1;
        };

        for (long long p = 2; p <= v; ++p) {
            if (g[m - p] > g[m - p + 1]) { // p is prime
                long long sp = g[m - p + 1];
                for (int i = 0; i < m; ++i) {
                    if (val[i] < p * p) break;
                    g[i] -= (g[get_idx(val[i] / p)] - sp);
                }
            }
        }
        return g[0];
    }
};

int main() {
    assert(Min25PrimeCount::pi(10) == 4);
    assert(Min25PrimeCount::pi(100) == 25);
    assert(Min25PrimeCount::pi(1000) == 168);

    std::cout << "min25_sieve_prime_counting tests passed successfully.\n";
    return 0;
}
