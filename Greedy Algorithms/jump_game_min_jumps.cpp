#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Jump Game II (Minimum Jumps)
// Purpose: Finds the minimum number of jumps to reach the last index in O(N) time using BFS-like greedy frontiers.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1; last index is reachable.

class JumpGameMinJumps {
public:
    static int jump(const std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int jumps = 0;
        int current_end = 0;
        int farthest = 0;

        for (int i = 0; i < n - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);
            if (i == current_end) {
                jumps++;
                current_end = farthest;
                if (current_end >= n - 1) break;
            }
        }
        return jumps;
    }
};

int main() {
    std::vector<int> a = {2, 3, 1, 1, 4};
    assert(JumpGameMinJumps::jump(a) == 2); // 0 -> 1 -> 4

    std::vector<int> b = {2, 3, 0, 1, 4};
    assert(JumpGameMinJumps::jump(b) == 2);

    std::cout << "jump_game_min_jumps tests passed successfully.\n";
    return 0;
}
