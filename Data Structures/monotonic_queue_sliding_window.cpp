// Algorithm: Sliding Window Min/Max via Monotonic Queue
// Purpose: Maintains minimum and maximum in sliding window of width K in amortized O(1) per step.
// Time Complexity: O(N)
// Space Complexity: O(K)
// Preconditions: 1 <= K <= N.

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

std::vector<int> sliding_window_max(const std::vector<int>& nums, int k) {
    int n = nums.size();
    std::deque<int> dq;
    std::vector<int> res;

    for (int i = 0; i < n; ++i) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

int main() {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto maxs = sliding_window_max(nums, 3);
    assert(maxs == std::vector<int>({3, 3, 5, 5, 6, 7}));
    return 0;
}
