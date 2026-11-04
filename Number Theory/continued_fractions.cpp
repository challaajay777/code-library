#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Continued Fraction Expansion
// Purpose: Computes continued fraction coefficients [a0; a1, a2, ...] of rational P/Q and convergents in O(log(Q)).
// Time Complexity: O(log(Q)) time
// Space Complexity: O(log(Q)) auxiliary space
// Preconditions: Q > 0.

class ContinuedFraction {
public:
    static std::vector<long long> expand(long long p, long long q) {
        assert(q > 0);
        std::vector<long long> a;
        while (q != 0) {
            a.push_back(p / q);
            long long rem = p % q;
            p = q;
            q = rem;
        }
        return a;
    }
};

int main() {
    // 649 / 200 = 3 + 1 / (4 + 1 / (12 + 1 / 4))
    auto cf = ContinuedFraction::expand(649, 200);
    std::vector<long long> expected = {3, 4, 12, 4};
    assert(cf == expected);

    std::cout << "continued_fractions tests passed successfully.\n";
    return 0;
}
