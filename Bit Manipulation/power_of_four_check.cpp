#include <iostream>
#include <cassert>

// Algorithm: Power of Four Check
// Purpose: Determines whether a number is a power of 4 in O(1) time without loops or recursion.
// Time Complexity: O(1) time
// Space Complexity: O(1) space
// Preconditions: 32-bit signed integer.

class PowerOfFour {
public:
    static bool is_power_of_four(int n) {
        // n > 0, exactly one bit set, and the bit is at an even position (0x55555555 mask)
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
    }
};

int main() {
    assert(PowerOfFour::is_power_of_four(16) == true);
    assert(PowerOfFour::is_power_of_four(5) == false);
    assert(PowerOfFour::is_power_of_four(1) == true);
    assert(PowerOfFour::is_power_of_four(8) == false); // power of 2, but not 4

    std::cout << "power_of_four_check tests passed successfully.\n";
    return 0;
}
