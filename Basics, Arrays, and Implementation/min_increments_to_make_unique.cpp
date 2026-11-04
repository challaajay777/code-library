#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Increments to Make Array Unique
// Purpose: Computes minimum number of +1 increment operations required to make all elements in an array unique.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Elements non-negative.

class MinIncrementsUnique {
public:
    static long long min_increment_for_unique(std::vector<int>& a) {
        if (a.empty()) return 0;
        std::sort(a.begin(), a.end());
        long long moves = 0;
        int needed = a[0];

        for (int x : a) {
            if (x < needed) {
                moves += (needed - x);
                needed++;
            } else {
                needed = x + 1;
            }
        }
        return moves;
    }
};

int main() {
    std::vector<int> a = {1, 2, 2};
    assert(MinIncrementsUnique::min_increment_for_unique(a) == 1); // 2 -> 3

    std::vector<int> b = {3, 2, 1, 2, 1, 7};
    assert(MinIncrementsUnique::min_increment_for_unique(b) == 6);

    std::cout << "min_increments_to_make_unique tests passed successfully.\n";
    return 0;
}
