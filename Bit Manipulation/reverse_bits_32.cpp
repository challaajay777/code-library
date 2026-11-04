#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Reverse 32-bit Integer
// Purpose: Reverses the 32 bits of an unsigned integer in O(1) time using parallel bitmask shifts.
// Time Complexity: O(1) time (5 bitwise swap steps)
// Space Complexity: O(1) auxiliary space
// Preconditions: 32-bit unsigned integer.

class ReverseBits32 {
public:
    static uint32_t reverse(uint32_t n) {
        n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
        n = ((n & 0xFF00FF00) >> 8)  | ((n & 0x00FF00FF) << 8);
        n = ((n & 0xF0F0F0F0) >> 4)  | ((n & 0x0F0F0F0F) << 4);
        n = ((n & 0xCCCCCCCC) >> 2)  | ((n & 0x33333333) << 2);
        n = ((n & 0xAAAAAAAA) >> 1)  | ((n & 0x55555555) << 1);
        return n;
    }
};

int main() {
    uint32_t x = 43261596; // 00000010100101000001111010011100
    uint32_t rev = ReverseBits32::reverse(x);
    assert(rev == 964176192); // 00111001011110000010100101000000

    std::cout << "reverse_bits_32 tests passed successfully.\n";
    return 0;
}
