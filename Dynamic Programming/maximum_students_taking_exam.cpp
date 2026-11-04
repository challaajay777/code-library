// Algorithm: Maximum Students Taking Exam Profile DP
// Purpose: Finds max students seated in classroom without cheating diagonally or horizontally.
// Time Complexity: O(R * 2^C * 2^C)
// Space Complexity: O(2^C)
// Preconditions: Classroom grid with '.' (available) and '#' (broken).

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_students(const std::vector<std::vector<char>>& seats) {
    int r = seats.size(), c = seats[0].size();
    std::vector<int> valid_seats(r, 0);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (seats[i][j] == '.') {
                valid_seats[i] |= (1 << j);
            }
        }
    }

    int total_masks = 1 << c;
    std::vector<int> dp(total_masks, -1);
    dp[0] = 0;

    for (int i = 0; i < r; ++i) {
        std::vector<int> next_dp(total_masks, -1);
        for (int mask = 0; mask < total_masks; ++mask) {
            if ((mask & valid_seats[i]) != mask) continue;
            if (mask & (mask >> 1)) continue; // no adjacent seats in same row

            int count = __builtin_popcount(mask);
            for (int prev_mask = 0; prev_mask < total_masks; ++prev_mask) {
                if (dp[prev_mask] == -1) continue;
                if ((mask & (prev_mask >> 1)) || (mask & (prev_mask << 1))) continue; // diagonal cheat
                next_dp[mask] = std::max(next_dp[mask], dp[prev_mask] + count);
            }
        }
        dp = next_dp;
    }

    int ans = 0;
    for (int val : dp) ans = std::max(ans, val);
    return ans;
}

int main() {
    std::vector<std::vector<char>> seats = {
        {'#', '.', '#', '#', '.', '#'},
        {'.', '#', '#', '#', '#', '.'},
        {'#', '.', '#', '#', '.', '#'}
    };
    assert(max_students(seats) == 4);
    return 0;
}
