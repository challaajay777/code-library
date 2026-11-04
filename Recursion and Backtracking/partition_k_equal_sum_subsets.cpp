#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Partition to K Equal Sum Subsets
// Purpose: Determines whether an array of integers can be partitioned into K non-empty subsets with equal sum.
// Time Complexity: O(K * 2^N) time with pruning
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= K <= N.

class PartitionKEqualSubsets {
private:
    static bool dfs(int idx, int count_k, int cur_sum, int target,
                    const std::vector<int>& nums, std::vector<bool>& used) {
        if (count_k == 0) return true;
        if (cur_sum == target) {
            return dfs(0, count_k - 1, 0, target, nums, used);
        }

        for (int i = idx; i < (int)nums.size(); ++i) {
            if (used[i] || cur_sum + nums[i] > target) continue;
            used[i] = true;
            if (dfs(i + 1, count_k, cur_sum + nums[i], target, nums, used)) {
                return true;
            }
            used[i] = false;
            // Prune duplicate failures
            while (i + 1 < (int)nums.size() && nums[i + 1] == nums[i]) i++;
            if (cur_sum == 0) break;
        }
        return false;
    }

public:
    static bool can_partition_k_subsets(std::vector<int> nums, int k) {
        int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;
        int target = total / k;

        std::sort(nums.rbegin(), nums.rend());
        if (nums[0] > target) return false;

        std::vector<bool> used(nums.size(), false);
        return dfs(0, k, 0, target, nums, used);
    }
};

int main() {
    std::vector<int> a = {4, 3, 2, 3, 5, 2, 1};
    assert(PartitionKEqualSubsets::can_partition_k_subsets(a, 4) == true);

    std::vector<int> b = {1, 2, 3, 4};
    assert(PartitionKEqualSubsets::can_partition_k_subsets(b, 3) == false);

    std::cout << "partition_k_equal_sum_subsets tests passed successfully.\n";
    return 0;
}
