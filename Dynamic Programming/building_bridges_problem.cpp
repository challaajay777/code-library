// Algorithm: Building Bridges Problem via LIS
// Purpose: Finds the maximum number of non-crossing bridges between two river banks.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Pairs of north and south bank coordinates.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Bridge {
    int north, south;
};

int max_non_crossing_bridges(std::vector<Bridge>& bridges) {
    std::sort(bridges.begin(), bridges.end(), [](const Bridge& a, const Bridge& b) {
        if (a.north != b.north) return a.north < b.north;
        return a.south < b.south;
    });

    std::vector<int> tails;
    for (const auto& b : bridges) {
        auto it = std::lower_bound(tails.begin(), tails.end(), b.south);
        if (it == tails.end()) {
            tails.push_back(b.south);
        } else {
            *it = b.south;
        }
    }
    return tails.size();
}

int main() {
    std::vector<Bridge> bridges = {{6, 2}, {4, 3}, {2, 6}, {1, 5}};
    assert(max_non_crossing_bridges(bridges) == 2);
    return 0;
}
