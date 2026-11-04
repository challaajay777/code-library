#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 4-Sum (Two Pointers)
// Purpose: Finds all unique quadruplets summing to target value in O(N^3) time and O(1) auxiliary space.
// Time Complexity: O(N^3) time
// Space Complexity: O(1) auxiliary space beyond output
// Preconditions: 64-bit integer sum calculations.

class FourSumTwoPointers {
public:
    static std::vector<std::vector<int>> four_sum(std::vector<int>& nums, long long target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> res;

        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int left = j + 1, right = n - 1;
                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 0, -1, 0, -2, 2};
    auto quad = FourSumTwoPointers::four_sum(a, 0);
    assert(quad.size() == 3);

    std::cout << "four_sum_two_pointers tests passed successfully.\n";
    return 0;
}
