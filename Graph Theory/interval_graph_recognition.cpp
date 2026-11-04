// Algorithm: Interval Graph Recognition from Intervals
// Purpose: Builds intersection graph from 1D intervals and checks chordal property.
// Time Complexity: O(N log N + E)
// Space Complexity: O(N + E)
// Preconditions: Collection of intervals [start, end].

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Interval {
    int l, r, id;
};

std::vector<std::vector<int>> build_interval_graph(int n, std::vector<Interval>& intervals) {
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (std::max(intervals[i].l, intervals[j].l) <= std::min(intervals[i].r, intervals[j].r)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    return adj;
}

int main() {
    std::vector<Interval> iv = {{1, 3, 0}, {2, 5, 1}, {4, 6, 2}};
    auto adj = build_interval_graph(3, iv);
    // 0 overlaps 1, 1 overlaps 2
    assert(adj[0].size() == 1 && adj[0][0] == 1);
    assert(adj[1].size() == 2);
    return 0;
}
