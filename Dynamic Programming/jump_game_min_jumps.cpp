// Algorithm: Jump Game Minimum Jumps DP/Greedy
// Purpose: Finds minimum number of jumps to reach the last index from the first index.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Array of non-negative integers where nums[i] is max jump length from i.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int jump_min_steps(const std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    int jumps = 0, cur_end = 0, farthest = 0;

    for (int i = 0; i < n - 1; ++i) {
        farthest = std::max(farthest, i + nums[i]);
        if (i == cur_end) {
            jumps++;
            cur_end = farthest;
            if (cur_end >= n - 1) break;
        }
    }
    return jumps;
}

int main() {
    std::vector<int> nums = {2, 3, 1, 1, 4};
    assert(jump_min_steps(nums) == 2); // 0 -> 1 -> 4
    return 0;
}
