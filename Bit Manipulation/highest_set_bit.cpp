#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Most Significant Set Bit (MSB)
// Purpose: Finds the highest set bit and the largest power of 2 less than or equal to X in O(1) time.
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: X > 0.

class MostSignificantBit {
public:
    static int highest_bit_index(uint64_t x) {
        assert(x > 0);
        return 63 - __builtin_clzll(x);
    }

    static uint64_t largest_power_of_two_le(uint64_t x) {
        assert(x > 0);
        return 1ULL << highest_bit_index(x);
    }
};

int main() {
    assert(MostSignificantBit::highest_bit_index(16) == 4);
    assert(MostSignificantBit::highest_bit_index(18) == 4);
    assert(MostSignificantBit::largest_power_of_two_le(18) == 16);
    assert(MostSignificantBit::largest_power_of_two_le(31) == 16);

    std::cout << "highest_set_bit tests passed successfully.\n";
    return 0;
}
