#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 3-Sum (Two Pointers)
// Purpose: Finds all unique triplets [a, b, c] such that a + b + c = 0 in O(N^2) time and O(1) extra space.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space beyond output
// Preconditions: General array of integers.

class ThreeSumTwoPointers {
public:
    static std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> res;

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {-1, 0, 1, 2, -1, -4};
    auto trips = ThreeSumTwoPointers::three_sum(a);
    assert(trips.size() == 2);
    assert(trips[0] == std::vector<int>({-1, -1, 2}));
    assert(trips[1] == std::vector<int>({-1, 0, 1}));

    std::cout << "three_sum_two_pointers tests passed successfully.\n";
    return 0;
}
