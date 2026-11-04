#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Range Euler's Totient Sieve
// Purpose: Computes phi(x) for all integers x in range [L, R] in O((R - L + 1) log log R + sqrt(R)).
// Time Complexity: O((R - L + 1) log log R + sqrt(R)) time
// Space Complexity: O(R - L + 1) space
// Preconditions: 1 <= L <= R.

class RangeEulerTotient {
public:
    static std::vector<long long> compute_range_phi(long long L, long long R) {
        long long len = R - L + 1;
        std::vector<long long> phi(len);
        std::vector<long long> rem(len);

        for (long long i = 0; i < len; ++i) {
            phi[i] = L + i;
            rem[i] = L + i;
        }

        for (long long p = 2; p * p <= R; ++p) {
            long long start = (L + p - 1) / p * p;
            for (long long j = start; j <= R; j += p) {
                if (rem[j - L] % p == 0) {
                    while (rem[j - L] % p == 0) rem[j - L] /= p;
                    phi[j - L] -= phi[j - L] / p;
                }
            }
        }

        for (long long i = 0; i < len; ++i) {
            if (rem[i] > 1) {
                phi[i] -= phi[i] / rem[i];
            }
        }
        return phi;
    }
};

int main() {
    auto phis = RangeEulerTotient::compute_range_phi(1, 10);
    // phi(1..10): 1, 1, 2, 2, 4, 2, 6, 4, 6, 4
    std::vector<long long> expected = {1, 1, 2, 2, 4, 2, 6, 4, 6, 4};
    assert(phis == expected);

    std::cout << "euler_totient_range_sieve tests passed successfully.\n";
    return 0;
}
