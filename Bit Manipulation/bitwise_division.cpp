#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Bitwise Division
// Purpose: Computes quotient and remainder of two integers using bit shifts and subtraction without / or % operators.
// Time Complexity: O(log(dividend)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Divisor != 0.

class BitwiseDivision {
public:
    static std::pair<uint64_t, uint64_t> divide(uint64_t dividend, uint64_t divisor) {
        assert(divisor != 0);
        uint64_t quotient = 0;

        for (int i = 63; i >= 0; --i) {
            if ((dividend >> i) >= divisor) {
                quotient |= (1ULL << i);
                dividend -= (divisor << i);
            }
        }
        return {quotient, dividend}; // {quotient, remainder}
    }
};

int main() {
    auto [q, r] = BitwiseDivision::divide(43, 5);
    assert(q == 8 && r == 3);

    auto [q2, r2] = BitwiseDivision::divide(100, 10);
    assert(q2 == 10 && r2 == 0);

    std::cout << "bitwise_division tests passed successfully.\n";
    return 0;
}
