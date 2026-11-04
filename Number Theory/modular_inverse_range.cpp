#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Range Modular Inverses
// Purpose: Computes modular inverses for all integers 1 <= i <= N modulo prime P in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: P is prime; N < P.

class RangeModularInverses {
public:
    static std::vector<long long> compute_inverses(int n, long long p) {
        std::vector<long long> inv(n + 1, 0);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = (p - p / i) * inv[p % i] % p;
        }
        return inv;
    }
};

int main() {
    auto inv = RangeModularInverses::compute_inverses(6, 7);
    for (int i = 1; i <= 6; ++i) {
        assert((i * inv[i]) % 7 == 1);
    }

    std::cout << "modular_inverse_range tests passed successfully.\n";
    return 0;
}
