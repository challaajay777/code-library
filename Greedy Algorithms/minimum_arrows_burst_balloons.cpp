#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Arrows to Burst Balloons (Interval Covering)
// Purpose: Finds minimum number of vertical arrows required to shoot all horizontal balloon intervals in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Points formatted as [start, end] with start <= end.

class MinimumArrowsBurstBalloons {
public:
    static int find_min_arrow_shots(std::vector<std::pair<int, int>>& points) {
        if (points.empty()) return 0;
        std::sort(points.begin(), points.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });

        int arrows = 1;
        int end = points[0].second;

        for (size_t i = 1; i < points.size(); ++i) {
            if (points[i].first > end) {
                arrows++;
                end = points[i].second;
            }
        }
        return arrows;
    }
};

int main() {
    std::vector<std::pair<int, int>> p = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    assert(MinimumArrowsBurstBalloons::find_min_arrow_shots(p) == 2);

    std::cout << "minimum_arrows_burst_balloons tests passed successfully.\n";
    return 0;
}
