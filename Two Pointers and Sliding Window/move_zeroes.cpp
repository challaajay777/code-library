#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Move Zeroes to End
// Purpose: Moves all 0s to the end of the array while maintaining the relative order of the non-zero elements in O(N).
// Time Complexity: O(N) time with minimal writes
// Space Complexity: O(1) auxiliary space
// Preconditions: Arbitrary integer array.

class MoveZeroes {
public:
    static void move_zeroes(std::vector<int>& nums) {
        int last_non_zero = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                std::swap(nums[last_non_zero++], nums[i]);
            }
        }
    }
};

int main() {
    std::vector<int> a = {0, 1, 0, 3, 12};
    MoveZeroes::move_zeroes(a);
    std::vector<int> expected = {1, 3, 12, 0, 0};
    assert(a == expected);

    std::cout << "move_zeroes tests passed successfully.\n";
    return 0;
}
