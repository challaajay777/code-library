// Algorithm: Maximal Square in Binary Matrix DP
// Purpose: Finds the largest square containing only 1s and returns its area.
// Time Complexity: O(R * C)
// Space Complexity: O(C)
// Preconditions: Grid of characters '0' and '1'.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int maximal_square(const std::vector<std::vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int r = matrix.size(), c = matrix[0].size();
    std::vector<int> dp(c + 1, 0);
    int max_side = 0, prev = 0;

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            int temp = dp[j];
            if (matrix[i - 1][j - 1] == '1') {
                dp[j] = std::min({dp[j], dp[j - 1], prev}) + 1;
                max_side = std::max(max_side, dp[j]);
            } else {
                dp[j] = 0;
            }
            prev = temp;
        }
    }
    return max_side * max_side;
}

int main() {
    std::vector<std::vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    assert(maximal_square(matrix) == 4);
    return 0;
}
