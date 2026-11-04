#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Segmented Sieve of Eratosthenes
// Purpose: Finds all prime numbers in an arbitrary range [L, R] using O(sqrt(R)) base primes and O(R - L + 1) memory.
// Time Complexity: O((R - L + 1) log log R + sqrt(R) log log sqrt(R)) time
// Space Complexity: O(R - L + 1) auxiliary space
// Preconditions: 1 <= L <= R <= 10^12 and R - L <= 10^7.

class SegmentedSieve {
private:
    static std::vector<long long> simple_sieve(long long limit) {
        std::vector<bool> is_prime(limit + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (long long p = 2; p * p <= limit; ++p) {
            if (is_prime[p]) {
                for (long long i = p * p; i <= limit; i += p) {
                    is_prime[i] = false;
                }
            }
        }
        std::vector<long long> primes;
        for (long long p = 2; p <= limit; ++p) {
            if (is_prime[p]) primes.push_back(p);
        }
        return primes;
    }

public:
    static std::vector<long long> get_primes_in_range(long long L, long long R) {
        if (L > R || R < 2) return {};
        L = std::max(L, 2LL);

        long long lim = 0;
        while ((lim + 1) * (lim + 1) <= R) lim++;

        auto base_primes = simple_sieve(lim);
        std::vector<bool> is_prime(R - L + 1, true);

        for (long long p : base_primes) {
            long long start = (L + p - 1) / p * p;
            if (start < p * p) start = p * p;
            for (long long j = start; j <= R; j += p) {
                is_prime[j - L] = false;
            }
        }

        std::vector<long long> primes;
        for (long long i = 0; i <= R - L; ++i) {
            if (is_prime[i]) primes.push_back(L + i);
        }
        return primes;
    }
};

int main() {
    auto primes = SegmentedSieve::get_primes_in_range(10, 20);
    std::vector<long long> expected = {11, 13, 17, 19};
    assert(primes == expected);

    auto p2 = SegmentedSieve::get_primes_in_range(1, 10);
    std::vector<long long> exp2 = {2, 3, 5, 7};
    assert(p2 == exp2);

    std::cout << "segmented_sieve tests passed successfully.\n";
    return 0;
}
