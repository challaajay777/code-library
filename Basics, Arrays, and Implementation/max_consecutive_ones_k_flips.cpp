#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Max Consecutive Ones with K Flips
// Purpose: Finds maximum length of contiguous 1s achievable by flipping at most K zeros to 1s using sliding window.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array elements in {0, 1}, K >= 0.

class MaxConsecutiveOnesKFlips {
public:
    static int longest_ones(const std::vector<int>& a, int k) {
        int left = 0;
        int zero_count = 0;
        int max_len = 0;

        for (int right = 0; right < (int)a.size(); ++right) {
            if (a[right] == 0) {
                zero_count++;
            }
            while (zero_count > k) {
                if (a[left] == 0) {
                    zero_count--;
                }
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    std::vector<int> a = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    assert(MaxConsecutiveOnesKFlips::longest_ones(a, 2) == 6);

    std::vector<int> b = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    assert(MaxConsecutiveOnesKFlips::longest_ones(b, 3) == 10);

    std::cout << "max_consecutive_ones_k_flips tests passed successfully.\n";
    return 0;
}
