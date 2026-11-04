#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Furthest Building Reachable
// Purpose: Finds the furthest building index reachable using available bricks and ladders greedily using a min-heap in O(N log K).
// Time Complexity: O(N log ladders) time
// Space Complexity: O(ladders) space
// Preconditions: Heights non-negative; bricks >= 0, ladders >= 0.

class FurthestBuilding {
public:
    static int furthest_building(const std::vector<int>& heights, int bricks, int ladders) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        for (size_t i = 0; i + 1 < heights.size(); ++i) {
            int diff = heights[i + 1] - heights[i];
            if (diff > 0) {
                min_heap.push(diff);
                if ((int)min_heap.size() > ladders) {
                    bricks -= min_heap.top();
                    min_heap.pop();
                    if (bricks < 0) return i;
                }
            }
        }
        return heights.size() - 1;
    }
};

int main() {
    std::vector<int> h = {4, 2, 7, 6, 9, 14, 12};
    assert(FurthestBuilding::furthest_building(h, 5, 1) == 4);

    std::cout << "furthest_building_ladders_bricks tests passed successfully.\n";
    return 0;
}
