#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Operations to Reduce X to Zero
// Purpose: Finds minimum operations to reduce X to 0 by removing leftmost or rightmost elements via max subarray sum in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements positive.

class ReduceXToZero {
public:
    static int min_operations(const std::vector<int>& nums, int x) {
        long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
        long long target = total - x;
        if (target < 0) return -1;
        if (target == 0) return nums.size();

        int max_len = -1;
        long long cur_sum = 0;
        int left = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            cur_sum += nums[right];
            while (cur_sum > target && left <= right) {
                cur_sum -= nums[left++];
            }
            if (cur_sum == target) {
                max_len = std::max(max_len, right - left + 1);
            }
        }
        return max_len == -1 ? -1 : (int)nums.size() - max_len;
    }
};

int main() {
    std::vector<int> a = {1, 1, 4, 2, 3};
    assert(ReduceXToZero::min_operations(a, 5) == 2); // 2 and 3 from right

    std::vector<int> b = {5, 6, 7, 8, 9};
    assert(ReduceXToZero::min_operations(b, 4) == -1);

    std::cout << "minimum_operations_reduce_x_to_zero tests passed successfully.\n";
    return 0;
}
