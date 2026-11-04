// Algorithm: 3D Box Stacking via DAG Dynamic Programming
// Purpose: Finds the maximum height of a stack of boxes where each box must have strictly smaller 2D base.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: List of 3D box dimensions (length, width, height).

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Box {
    int l, w, h;
};

int max_box_stack_height(const std::vector<Box>& boxes) {
    std::vector<Box> rot;
    for (const auto& b : boxes) {
        std::vector<int> d = {b.l, b.w, b.h};
        std::sort(d.begin(), d.end());
        // 3 rotations for each box
        rot.push_back({d[1], d[0], d[2]});
        rot.push_back({d[2], d[0], d[1]});
        rot.push_back({d[2], d[1], d[0]});
    }

    std::sort(rot.begin(), rot.end(), [](const Box& a, const Box& b) {
        return 1LL * a.l * a.w > 1LL * b.l * b.w;
    });

    int m = rot.size();
    std::vector<int> dp(m, 0);
    int ans = 0;

    for (int i = 0; i < m; ++i) {
        dp[i] = rot[i].h;
        for (int j = 0; j < i; ++j) {
            if (rot[i].l < rot[j].l && rot[i].w < rot[j].w) {
                dp[i] = std::max(dp[i], dp[j] + rot[i].h);
            }
        }
        ans = std::max(ans, dp[i]);
    }
    return ans;
}

int main() {
    std::vector<Box> boxes = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};
    assert(max_box_stack_height(boxes) == 60);
    return 0;
}
