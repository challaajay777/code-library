// Algorithm: Longest Alternating Subsequence DP
// Purpose: Finds the length of the longest subsequence where differences between consecutive elements alternate sign.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int longest_alternating_subsequence(const std::vector<int>& a) {
    int n = a.size();
    if (n <= 1) return n;
    int up = 1, down = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) up = down + 1;
        else if (a[i] < a[i - 1]) down = up + 1;
    }
    return std::max(up, down);
}

int main() {
    std::vector<int> a = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    assert(longest_alternating_subsequence(a) == 7);
    return 0;
}
