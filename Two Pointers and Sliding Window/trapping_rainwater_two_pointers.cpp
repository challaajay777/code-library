#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Trapping Rainwater (Two Pointers)
// Purpose: Computes total rainwater trapped between elevation bars in O(N) time using O(1) extra space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elevation heights are non-negative.

class TrappingRainwaterTwoPointers {
public:
    static long long trap(const std::vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int left_max = 0, right_max = 0;
        long long water = 0;

        while (left < right) {
            if (height[left] <= height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    water += left_max - height[left];
                }
                left++;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    water += right_max - height[right];
                }
                right--;
            }
        }
        return water;
    }
};

int main() {
    std::vector<int> h = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(TrappingRainwaterTwoPointers::trap(h) == 6);

    std::vector<int> h2 = {4, 2, 0, 3, 2, 5};
    assert(TrappingRainwaterTwoPointers::trap(h2) == 9);

    std::cout << "trapping_rainwater_two_pointers tests passed successfully.\n";
    return 0;
}
