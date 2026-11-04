#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Interval List Intersections
// Purpose: Computes the intersection of two disjoint, sorted lists of closed intervals in O(N + M) time using two pointers.
// Time Complexity: O(N + M) time
// Space Complexity: O(1) auxiliary space beyond result
// Preconditions: Intervals in both lists pairwise disjoint and sorted by start time.

class IntervalIntersections {
public:
    static std::vector<std::pair<int, int>> interval_intersection(
        const std::vector<std::pair<int, int>>& first_list,
        const std::vector<std::pair<int, int>>& second_list) {

        std::vector<std::pair<int, int>> res;
        int i = 0, j = 0;
        int n1 = first_list.size(), n2 = second_list.size();

        while (i < n1 && j < n2) {
            int start = std::max(first_list[i].first, second_list[j].first);
            int end = std::min(first_list[i].second, second_list[j].second);

            if (start <= end) {
                res.push_back({start, end});
            }

            if (first_list[i].second < second_list[j].second) {
                i++;
            } else {
                j++;
            }
        }
        return res;
    }
};

int main() {
    std::vector<std::pair<int, int>> l1 = {{0, 2}, {5, 10}, {13, 23}, {24, 25}};
    std::vector<std::pair<int, int>> l2 = {{1, 5}, {8, 12}, {15, 24}, {25, 26}};
    auto inter = IntervalIntersections::interval_intersection(l1, l2);
    std::vector<std::pair<int, int>> expected = {{1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}};
    assert(inter == expected);

    std::cout << "interval_list_intersections tests passed successfully.\n";
    return 0;
}
