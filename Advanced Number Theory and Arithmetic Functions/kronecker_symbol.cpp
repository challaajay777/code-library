#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Kronecker Symbol
// Purpose: Extends Jacobi symbol (a / n) to all integer denominators n, including zero and negative values.
// Time Complexity: O(log(min(|a|, |n|))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Any integers a and n.

class KroneckerSymbol {
public:
    static int kronecker(long long a, long long b) {
        if (b == 0) return std::abs(a) == 1 ? 1 : 0;

        int res = 1;
        if (b < 0) {
            b = -b;
            if (a < 0) res = -res;
        }

        while (b % 2 == 0) {
            b /= 2;
            long long rem = a % 8;
            if (rem < 0) rem += 8;
            if (rem == 3 || rem == 5) res = -res;
            else if (rem != 1 && rem != 7) return 0;
        }

        // Jacobi part
        a %= b;
        if (a < 0) a += b;

        while (a != 0) {
            while (a % 2 == 0) {
                a /= 2;
                long long rem = b % 8;
                if (rem == 3 || rem == 5) res = -res;
            }
            std::swap(a, b);
            if (a % 4 == 3 && b % 4 == 3) res = -res;
            a %= b;
        }
        return b == 1 ? res : 0;
    }
};

int main() {
    assert(KroneckerSymbol::kronecker(2, 7) == 1);
    assert(KroneckerSymbol::kronecker(-1, 5) == 1);
    assert(KroneckerSymbol::kronecker(-1, 3) == -1);

    std::cout << "kronecker_symbol tests passed successfully.\n";
    return 0;
}
