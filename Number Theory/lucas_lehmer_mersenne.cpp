#include <iostream>
#include <cassert>

// Algorithm: Lucas-Lehmer Primality Test
// Purpose: Deterministically tests whether Mersenne number M_p = 2^p - 1 is prime for odd prime exponent p.
// Time Complexity: O(p * M(p)) time where M(p) is multiplication complexity
// Space Complexity: O(p) auxiliary space
// Preconditions: Exponent p is prime.

class LucasLehmer {
public:
    static bool is_mersenne_prime(int p) {
        if (p == 2) return true;
        if (p < 2) return false;

        unsigned __int128 M_p = (1ULL << p) - 1ULL;
        unsigned __int128 s = 4;

        for (int i = 0; i < p - 2; ++i) {
            s = (s * s - 2) % M_p;
        }
        return s == 0;
    }
};

int main() {
    assert(LucasLehmer::is_mersenne_prime(3) == true);  // 2^3 - 1 = 7
    assert(LucasLehmer::is_mersenne_prime(5) == true);  // 2^5 - 1 = 31
    assert(LucasLehmer::is_mersenne_prime(7) == true);  // 2^7 - 1 = 127
    assert(LucasLehmer::is_mersenne_prime(11) == false); // 2^11 - 1 = 2047 = 23 * 89

    std::cout << "lucas_lehmer_mersenne tests passed successfully.\n";
    return 0;
}
