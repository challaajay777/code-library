#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: 3-Sum Closest
// Purpose: Finds three integers in array whose sum is closest to a target integer in O(N^2) time.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space beyond sorting
// Preconditions: Array length >= 3.

class ThreeSumClosest {
public:
    static int three_sum_closest(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        assert(n >= 3);
        int closest_sum = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (std::abs(sum - target) < std::abs(closest_sum - target)) {
                    closest_sum = sum;
                }
                if (sum < target) {
                    left++;
                } else if (sum > target) {
                    right--;
                } else {
                    return target;
                }
            }
        }
        return closest_sum;
    }
};

int main() {
    std::vector<int> a = {-1, 2, 1, -4};
    assert(ThreeSumClosest::three_sum_closest(a, 1) == 2); // (-1 + 2 + 1 = 2)

    std::vector<int> b = {0, 0, 0};
    assert(ThreeSumClosest::three_sum_closest(b, 1) == 0);

    std::cout << "three_sum_closest tests passed successfully.\n";
    return 0;
}
