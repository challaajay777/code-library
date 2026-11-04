#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Max Consecutive Ones III (Two Pointers)
// Purpose: Computes maximum consecutive 1s after flipping at most K zeros using standard two-pointer sliding window.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Binary array; K >= 0.

class MaxConsecutiveOnesIII {
public:
    static int longest_ones(const std::vector<int>& nums, int k) {
        int left = 0;
        int zeros = 0;
        int max_len = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            if (nums[right] == 0) zeros++;
            while (zeros > k) {
                if (nums[left] == 0) zeros--;
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    std::vector<int> a = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    assert(MaxConsecutiveOnesIII::longest_ones(a, 2) == 6);

    std::cout << "max_consecutive_ones_iii tests passed successfully.\n";
    return 0;
}
