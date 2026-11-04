// Algorithm: Longest Arithmetic Subsequence with Fixed Difference
// Purpose: Finds the length of the longest arithmetic subsequence with a fixed common difference d in linear time.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Array of integers, difference d.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>

int longest_subsequence_fixed_diff(const std::vector<int>& arr, int difference) {
    std::unordered_map<int, int> dp;
    int max_len = 0;
    for (int x : arr) {
        int prev = x - difference;
        int len = (dp.count(prev) ? dp[prev] : 0) + 1;
        dp[x] = len;
        max_len = std::max(max_len, len);
    }
    return max_len;
}

int main() {
    std::vector<int> arr = {1, 5, 7, 8, 5, 3, 4, 2, 1};
    assert(longest_subsequence_fixed_diff(arr, -2) == 4); // 7, 5, 3, 1
    return 0;
}
