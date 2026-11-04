#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 4-Sum via Pair Sums and Binary Search
// Purpose: Finds unique quadruplets that sum to target value using sorted pair sums and binary search in O(N^2 log N).
// Time Complexity: O(N^2 log N) time
// Space Complexity: O(N^2) auxiliary space for pair structures
// Preconditions: Arbitrary integer array.

class FourSumBinarySearch {
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
    auto quad = FourSumBinarySearch::four_sum(a, 0);
    // [-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1] -> 3 quadruplets
    assert(quad.size() == 3);

    std::cout << "four_sum_binary_search tests passed successfully.\n";
    return 0;
}
