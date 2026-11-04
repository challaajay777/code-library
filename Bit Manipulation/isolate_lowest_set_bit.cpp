#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Lowbit and Bit Clearing Tricks
// Purpose: Implements classical lowbit tricks: x & (-x), x & (x - 1), x | (x + 1) in O(1).
// Time Complexity: O(1) time
// Space Complexity: O(1) space
// Preconditions: Any 64-bit integer.

class BitTricks {
public:
    static uint64_t lowbit(uint64_t x) {
        return x & -x;
    }

    static uint64_t clear_lowest_bit(uint64_t x) {
        return x & (x - 1);
    }

    static uint64_t set_lowest_unset_bit(uint64_t x) {
        return x | (x + 1);
    }

    static bool is_power_of_two(uint64_t x) {
        return x > 0 && (x & (x - 1)) == 0;
    }
};

int main() {
    assert(BitTricks::lowbit(12) == 4); // 1100 -> lowest bit is 4
    assert(BitTricks::clear_lowest_bit(12) == 8); // 1100 -> 1000
    assert(BitTricks::set_lowest_unset_bit(10) == 11); // 1010 -> 1011
    assert(BitTricks::is_power_of_two(16) == true);
    assert(BitTricks::is_power_of_two(18) == false);

    std::cout << "isolate_lowest_set_bit tests passed successfully.\n";
    return 0;
}
