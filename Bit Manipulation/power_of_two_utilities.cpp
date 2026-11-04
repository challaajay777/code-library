#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Power of Two Utilities
// Purpose: Rounds up to next power of 2, rounds down to previous power of 2, and tests power of 2 in O(1).
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: X > 0.

class PowerOfTwoUtils {
public:
    static uint64_t next_power_of_two(uint64_t x) {
        if (x <= 1) return 1;
        return 1ULL << (64 - __builtin_clzll(x - 1));
    }

    static uint64_t prev_power_of_two(uint64_t x) {
        assert(x > 0);
        return 1ULL << (63 - __builtin_clzll(x));
    }
};

int main() {
    assert(PowerOfTwoUtils::next_power_of_two(5) == 8);
    assert(PowerOfTwoUtils::next_power_of_two(16) == 16);
    assert(PowerOfTwoUtils::prev_power_of_two(15) == 8);
    assert(PowerOfTwoUtils::prev_power_of_two(16) == 16);

    std::cout << "power_of_two_utilities tests passed successfully.\n";
    return 0;
}
