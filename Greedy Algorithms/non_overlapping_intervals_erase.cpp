#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Non-Overlapping Intervals (Minimum Removals)
// Purpose: Finds minimum number of intervals to remove to make the remainder non-overlapping in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Intervals valid (start <= end).

class NonOverlappingIntervals {
public:
    static int erase_overlap_intervals(std::vector<std::pair<int, int>>& intervals) {
        if (intervals.empty()) return 0;
        std::sort(intervals.begin(), intervals.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });

        int non_overlap = 1;
        int last_end = intervals[0].second;

        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i].first >= last_end) {
                non_overlap++;
                last_end = intervals[i].second;
            }
        }
        return intervals.size() - non_overlap;
    }
};

int main() {
    std::vector<std::pair<int, int>> invs = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    assert(NonOverlappingIntervals::erase_overlap_intervals(invs) == 1);

    std::vector<std::pair<int, int>> invs2 = {{1, 2}, {1, 2}, {1, 2}};
    assert(NonOverlappingIntervals::erase_overlap_intervals(invs2) == 2);

    std::cout << "non_overlapping_intervals_erase tests passed successfully.\n";
    return 0;
}
