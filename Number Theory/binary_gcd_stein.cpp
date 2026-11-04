#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Stein's Binary GCD Algorithm
// Purpose: Computes greatest common divisor using bit shifts and subtractions without division instructions.
// Time Complexity: O(log(min(a, b))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: a, b non-negative integers.

class BinaryGCD {
public:
    static uint64_t gcd(uint64_t a, uint64_t b) {
        if (a == 0) return b;
        if (b == 0) return a;

        int shift = __builtin_ctzll(a | b);
        a >>= __builtin_ctzll(a);

        do {
            b >>= __builtin_ctzll(b);
            if (a > b) std::swap(a, b);
            b -= a;
        } while (b != 0);

        return a << shift;
    }
};

int main() {
    assert(BinaryGCD::gcd(48, 18) == 6);
    assert(BinaryGCD::gcd(101, 103) == 1);
    assert(BinaryGCD::gcd(0, 50) == 50);

    std::cout << "binary_gcd_stein tests passed successfully.\n";
    return 0;
}
