#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Egyptian Fraction (Greedy Algorithm)
// Purpose: Represents any positive rational fraction P/Q as a sum of distinct unit fractions 1/d in greedy fashion.
// Time Complexity: O(terms) steps
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= P < Q.

class EgyptianFraction {
public:
    static std::vector<long long> get_unit_denominators(long long p, long long q) {
        assert(p > 0 && q > 0);
        std::vector<long long> denominators;

        while (p != 0) {
            long long d = (q + p - 1) / p; // ceil(q / p)
            denominators.push_back(d);

            p = p * d - q;
            q = q * d;
            long long g = std::gcd(p, q);
            p /= g;
            q /= g;
        }
        return denominators;
    }
};

int main() {
    auto denoms = EgyptianFraction::get_unit_denominators(2, 3);
    // 2/3 = 1/2 + 1/6
    assert(denoms.size() == 2);
    assert(denoms[0] == 2 && denoms[1] == 6);

    std::cout << "egyptian_fraction tests passed successfully.\n";
    return 0;
}
