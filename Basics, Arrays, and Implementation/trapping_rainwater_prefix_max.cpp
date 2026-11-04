#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Trapping Rainwater via Prefix & Suffix Extrema
// Purpose: Calculates total units of rainwater trapped between elevation bars in O(N) time using prefix/suffix elevation maxima.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Elevation heights are non-negative.

class TrappingRainwaterPrefixMax {
public:
    static long long trap(const std::vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;

        std::vector<int> left_max(n);
        std::vector<int> right_max(n);

        left_max[0] = height[0];
        for (int i = 1; i < n; ++i) {
            left_max[i] = std::max(left_max[i - 1], height[i]);
        }

        right_max[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right_max[i] = std::max(right_max[i + 1], height[i]);
        }

        long long trapped = 0;
        for (int i = 0; i < n; ++i) {
            trapped += std::min(left_max[i], right_max[i]) - height[i];
        }
        return trapped;
    }
};

int main() {
    std::vector<int> h = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(TrappingRainwaterPrefixMax::trap(h) == 6);

    std::vector<int> h2 = {4, 2, 0, 3, 2, 5};
    assert(TrappingRainwaterPrefixMax::trap(h2) == 9);

    std::cout << "trapping_rainwater_prefix_max tests passed successfully.\n";
    return 0;
}
