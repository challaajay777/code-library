#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Find Two Unique Non-Repeating Elements
// Purpose: Finds the two elements that appear once in an array where every other element appears twice in O(N) and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array contains exactly two distinct elements appearing once, all others twice.

class TwoUniqueElements {
public:
    static std::pair<int, int> find_unique_pair(const std::vector<int>& nums) {
        int xor_all = 0;
        for (int x : nums) xor_all ^= x;

        // Find any set bit in xor_all (lowest set bit)
        int diff_bit = xor_all & -xor_all;

        int a = 0, b = 0;
        for (int x : nums) {
            if (x & diff_bit) {
                a ^= x;
            } else {
                b ^= x;
            }
        }
        if (a > b) std::swap(a, b);
        return {a, b};
    }
};

int main() {
    std::vector<int> nums = {1, 2, 1, 3, 2, 5};
    auto [x, y] = TwoUniqueElements::find_unique_pair(nums);
    assert(x == 3 && y == 5);

    std::cout << "find_two_non_repeating_elements tests passed successfully.\n";
    return 0;
}
