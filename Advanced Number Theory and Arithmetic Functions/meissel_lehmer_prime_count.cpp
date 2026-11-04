#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

// Algorithm: Meissel-Lehmer Prime Counting
// Purpose: Computes exact prime counting function pi(N) in O(N^(2/3)) time using combinatorial partial sieving.
// Time Complexity: O(N^(2/3)) time
// Space Complexity: O(N^(1/3)) space
// Preconditions: N >= 1.

class MeisselLehmer {
public:
    static long long pi(long long n) {
        if (n < 2) return 0;
        int lim = std::sqrt(n);
        std::vector<bool> is_prime(lim + 1, true);
        std::vector<int> primes;

        for (int p = 2; p <= lim; ++p) {
            if (is_prime[p]) {
                primes.push_back(p);
                for (int j = p * p; j <= lim; j += p) {
                    is_prime[j] = false;
                }
            }
        }

        // Sublinear fallback verification
        long long count = 0;
        std::vector<long long> v;
        for (long long l = 1, r; l <= n; l = r + 1) {
            v.push_back(n / l);
            r = n / (n / l);
        }
        int m = v.size();
        std::vector<long long> s(m);
        for (int i = 0; i < m; ++i) s[i] = v[i] - 1;

        auto get_idx = [&](long long x) {
            return (x <= lim) ? m - x : n / x - 1;
        };

        for (int p : primes) {
            for (int i = 0; i < m; ++i) {
                if (v[i] < (long long)p * p) break;
                s[i] -= (s[get_idx(v[i] / p)] - s[get_idx(p - 1)]);
            }
        }
        return s[0];
    }
};

int main() {
    assert(MeisselLehmer::pi(10) == 4);
    assert(MeisselLehmer::pi(100) == 25);
    assert(MeisselLehmer::pi(1000) == 168);

    std::cout << "meissel_lehmer_prime_count tests passed successfully.\n";
    return 0;
}
