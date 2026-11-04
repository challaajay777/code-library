#include <iostream>
#include <cassert>

// Algorithm: Wilson's Theorem Primality Check
// Purpose: Verifies primality of small integer N using Wilson's identity (N - 1)! = -1 (mod N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 2.

class WilsonPrimality {
public:
    static bool is_prime(long long n) {
        if (n <= 1) return false;
        long long fact = 1;
        for (long long i = 2; i < n; ++i) {
            fact = (__int128)fact * i % n;
        }
        return fact == n - 1;
    }
};

int main() {
    assert(WilsonPrimality::is_prime(5) == true);
    assert(WilsonPrimality::is_prime(7) == true);
    assert(WilsonPrimality::is_prime(6) == false);

    std::cout << "wilson_theorem_primality tests passed successfully.\n";
    return 0;
}
