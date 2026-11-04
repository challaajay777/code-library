#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Russian Peasant Multiplication
// Purpose: Multiplies two numbers using only bitwise shifts and additions in O(log B) time.
// Time Complexity: O(log B) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-negative integers.

class RussianPeasantMultiplication {
public:
    static uint64_t multiply(uint64_t a, uint64_t b) {
        uint64_t res = 0;
        while (b > 0) {
            if (b & 1) {
                res += a;
            }
            a <<= 1;
            b >>= 1;
        }
        return res;
    }
};

int main() {
    assert(RussianPeasantMultiplication::multiply(18, 11) == 198);
    assert(RussianPeasantMultiplication::multiply(0, 100) == 0);
    assert(RussianPeasantMultiplication::multiply(12345, 6789) == 12345ULL * 6789ULL);

    std::cout << "bitwise_multiplication_russian_peasant tests passed successfully.\n";
    return 0;
}
