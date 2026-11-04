#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Inclusion-Exclusion Coprime Counting
// Purpose: Counts total numbers in range [1, N] that are coprime to a given set of prime factors via principle of inclusion-exclusion.
// Time Complexity: O(2^K) time where K is number of distinct prime factors
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1; prime factors distinct.

class InclusionExclusionCoprime {
public:
    static long long count_coprime(long long n, const std::vector<long long>& primes) {
        int k = primes.size();
        long long count = 0;

        for (int mask = 1; mask < (1 << k); ++mask) {
            long long prod = 1;
            int bits = 0;
            for (int i = 0; i < k; ++i) {
                if (mask & (1 << i)) {
                    prod *= primes[i];
                    bits++;
                }
            }
            if (bits % 2 == 1) {
                count += n / prod;
            } else {
                count -= n / prod;
            }
        }
        return n - count;
    }
};

int main() {
    // Numbers up to 10 coprime to {2, 5} -> {1, 3, 7, 9} = 4
    std::vector<long long> p = {2, 5};
    assert(InclusionExclusionCoprime::count_coprime(10, p) == 4);

    std::cout << "inclusion_exclusion_coprime_count tests passed successfully.\n";
    return 0;
}
