#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Swap Bits at Arbitrary Positions
// Purpose: Swaps the bits at index i and index j in an integer in O(1) time.
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= i, j < 64.

class SwapBits {
public:
    static uint64_t swap_bits(uint64_t n, int i, int j) {
        if (((n >> i) & 1) != ((n >> j) & 1)) {
            uint64_t mask = (1ULL << i) | (1ULL << j);
            n ^= mask;
        }
        return n;
    }
};

int main() {
    // 28 = 0001 1100. Swap bit 0 and bit 3:
    // bit 0 is 0, bit 3 is 1 -> becomes 0001 0101 = 21
    assert(SwapBits::swap_bits(28, 0, 3) == 21);

    std::cout << "swap_bits_in_integer tests passed successfully.\n";
    return 0;
}
