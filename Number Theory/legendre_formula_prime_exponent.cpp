#include <iostream>
#include <cassert>

// Algorithm: Legendre's Formula (Prime Factor Multiplicity in N!)
// Purpose: Calculates the exact exponent of prime P in the prime factorization of N! in O(log_P N) time.
// Time Complexity: O(log_P N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: P is prime; N >= 1.

class LegendreFormula {
public:
    static long long prime_multiplicity_in_factorial(long long n, long long p) {
        assert(p >= 2);
        long long count = 0;
        while (n > 0) {
            count += n / p;
            n /= p;
        }
        return count;
    }
};

int main() {
    // In 10!: 5 appears with exponent 10/5 = 2 (trailing zeros of 10! = 2)
    assert(LegendreFormula::prime_multiplicity_in_factorial(10, 5) == 2);
    // 2 appears with exponent 10/2 + 10/4 + 10/8 = 5 + 2 + 1 = 8
    assert(LegendreFormula::prime_multiplicity_in_factorial(10, 2) == 8);

    std::cout << "legendre_formula_prime_exponent tests passed successfully.\n";
    return 0;
}
