#include <iostream>
#include <cassert>

// Algorithm: Euler's Criterion for Quadratic Residues
// Purpose: Checks whether a is a quadratic residue modulo odd prime P using Euler's criterion a^((P-1)/2) mod P in O(log P).
// Time Complexity: O(log P) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Modulus P is an odd prime.

class QuadraticResidueCriterion {
public:
    static bool is_quadratic_residue(long long a, long long p) {
        a %= p;
        if (a < 0) a += p;
        if (a == 0) return true;

        long long exp = (p - 1) / 2;
        long long res = 1;
        long long base = a;

        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % p;
            base = (__int128)base * base % p;
            exp >>= 1;
        }
        return res == 1;
    }
};

int main() {
    assert(QuadraticResidueCriterion::is_quadratic_residue(4, 7) == true); // 2^2 = 4
    assert(QuadraticResidueCriterion::is_quadratic_residue(3, 7) == false);

    std::cout << "quadratic_residue_check tests passed successfully.\n";
    return 0;
}
