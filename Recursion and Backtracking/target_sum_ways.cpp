#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Target Sum (+ and - Assignments)
// Purpose: Calculates number of ways to assign + and - to array elements so that they sum to target.
// Time Complexity: O(2^N) time recursion, O(N * Sum) with memoization
// Space Complexity: O(N) recursion depth
// Preconditions: Array elements non-negative.

class TargetSumWays {
private:
    static int dfs(int idx, long long current_sum, long long target, const std::vector<int>& nums) {
        if (idx == (int)nums.size()) {
            return current_sum == target ? 1 : 0;
        }
        return dfs(idx + 1, current_sum + nums[idx], target, nums) +
               dfs(idx + 1, current_sum - nums[idx], target, nums);
    }

public:
    static int find_target_sum_ways(const std::vector<int>& nums, long long target) {
        return dfs(0, 0, target, nums);
    }
};

int main() {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    assert(TargetSumWays::find_target_sum_ways(nums, 3) == 5);

    std::vector<int> nums2 = {1};
    assert(TargetSumWays::find_target_sum_ways(nums2, 1) == 1);

    std::cout << "target_sum_ways tests passed successfully.\n";
    return 0;
}
