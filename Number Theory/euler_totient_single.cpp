#include <iostream>
#include <cassert>

// Algorithm: Euler's Totient Function (Single Integer)
// Purpose: Computes phi(N), the number of integers 1 <= k <= N coprime to N, in O(sqrt(N)) time.
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class EulerTotientSingle {
public:
    static long long phi(long long n) {
        long long result = n;
        for (long long p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                result -= result / p;
            }
        }
        if (n > 1) {
            result -= result / n;
        }
        return result;
    }
};

int main() {
    assert(EulerTotientSingle::phi(9) == 6);
    assert(EulerTotientSingle::phi(36) == 12);
    assert(EulerTotientSingle::phi(1) == 1);

    std::cout << "euler_totient_single tests passed successfully.\n";
    return 0;
}
