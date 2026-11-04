// Algorithm: Maximal Rectangle in Binary Matrix via Histogram DP
// Purpose: Finds the largest rectangle of 1s in a 2D binary matrix in O(R * C) time.
// Time Complexity: O(R * C)
// Space Complexity: O(C)
// Preconditions: 2D binary grid of characters '0' and '1'.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>

int largest_rectangle_in_histogram(const std::vector<int>& heights) {
    std::stack<int> s;
    int max_area = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        int h = (i == n ? 0 : heights[i]);
        while (!s.empty() && heights[s.top()] > h) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            max_area = std::max(max_area, height * width);
        }
        s.push(i);
    }
    return max_area;
}

int maximal_rectangle(const std::vector<std::vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int r = matrix.size(), c = matrix[0].size();
    std::vector<int> heights(c, 0);
    int max_area = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == '1') heights[j]++;
            else heights[j] = 0;
        }
        max_area = std::max(max_area, largest_rectangle_in_histogram(heights));
    }
    return max_area;
}

int main() {
    std::vector<std::vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    assert(maximal_rectangle(matrix) == 6);
    return 0;
}
