#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Jump Game (Reachability)
// Purpose: Determines whether the last index of an array is reachable from index 0 in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements represent maximum forward jump lengths.

class JumpGameReachability {
public:
    static bool can_jump(const std::vector<int>& nums) {
        int max_reach = 0;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if (i > max_reach) return false;
            max_reach = std::max(max_reach, i + nums[i]);
            if (max_reach >= n - 1) return true;
        }
        return true;
    }
};

int main() {
    std::vector<int> a = {2, 3, 1, 1, 4};
    assert(JumpGameReachability::can_jump(a) == true);

    std::vector<int> b = {3, 2, 1, 0, 4};
    assert(JumpGameReachability::can_jump(b) == false);

    std::cout << "jump_game_reachability tests passed successfully.\n";
    return 0;
}
