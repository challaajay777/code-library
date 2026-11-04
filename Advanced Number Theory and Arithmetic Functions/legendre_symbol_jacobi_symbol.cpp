#include <iostream>
#include <cassert>

// Algorithm: Legendre and Jacobi Symbol Computation
// Purpose: Computes Jacobi symbol (a / n) in O(log(min(a, n))) time using quadratic reciprocity without factoring n.
// Time Complexity: O(log(min(a, n))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n is a positive odd integer.

class JacobiSymbol {
public:
    static int jacobi(long long a, long long n) {
        assert(n > 0 && n % 2 == 1);
        a %= n;
        if (a < 0) a += n;
        int result = 1;

        while (a != 0) {
            while (a % 2 == 0) {
                a /= 2;
                long long rem = n % 8;
                if (rem == 3 || rem == 5) {
                    result = -result;
                }
            }
            std::swap(a, n);
            if (a % 4 == 3 && n % 4 == 3) {
                result = -result;
            }
            a %= n;
        }
        return n == 1 ? result : 0;
    }
};

int main() {
    assert(JacobiSymbol::jacobi(2, 7) == 1); // 2 is quadratic residue mod 7 (3^2 = 2 mod 7)
    assert(JacobiSymbol::jacobi(3, 7) == -1); // 3 is non-residue mod 7
    assert(JacobiSymbol::jacobi(7, 7) == 0);

    std::cout << "legendre_symbol_jacobi_symbol tests passed successfully.\n";
    return 0;
}
