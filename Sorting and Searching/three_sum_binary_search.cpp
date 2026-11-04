#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 3-Sum via Binary Search
// Purpose: Finds all unique triplets [a, b, c] such that a + b + c = 0 in O(N^2 log N) using binary search.
// Time Complexity: O(N^2 log N) time
// Space Complexity: O(1) auxiliary space beyond output
// Preconditions: 64-bit integer values.

class ThreeSumBinarySearch {
public:
    static std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> triplets;

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 1; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int target = -(nums[i] + nums[j]);
                if (std::binary_search(nums.begin() + j + 1, nums.end(), target)) {
                    triplets.push_back({nums[i], nums[j], target});
                }
            }
        }
        return triplets;
    }
};

int main() {
    std::vector<int> a = {-1, 0, 1, 2, -1, -4};
    auto trips = ThreeSumBinarySearch::three_sum(a);
    // Unique triplets: [-1, -1, 2], [-1, 0, 1]
    assert(trips.size() == 2);

    std::cout << "three_sum_binary_search tests passed successfully.\n";
    return 0;
}
