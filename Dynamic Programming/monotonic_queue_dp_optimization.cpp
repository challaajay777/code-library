// Algorithm: Monotonic Queue 1D DP Optimization
// Purpose: Optimizes DP transitions over sliding window bounds [i - k, i - 1] in strict O(N) total time.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Array of values, jump length k >= 1.

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

long long max_score_jump(const std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<long long> dp(n, 0);
    dp[0] = nums[0];

    std::deque<int> dq;
    dq.push_back(0);

    for (int i = 1; i < n; ++i) {
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        dp[i] = dp[dq.front()] + nums[i];

        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    return dp[n - 1];
}

int main() {
    std::vector<int> nums = {1, -1, -2, 4, -7, 3};
    // Jump at most 2 steps: 0 -> 1 -> 3 -> 5: 1 + (-1) + 4 + 3 = 7
    assert(max_score_jump(nums, 2) == 7);
    return 0;
}
