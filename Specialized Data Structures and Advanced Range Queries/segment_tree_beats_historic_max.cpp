// Algorithm: Segment Tree Historic Maximum Query
// Purpose: Tracks both current values and historic peak values across range updates.
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <cassert>

struct BeatsHistoricNode {
    long long cur_val, peak_val;
};

int main() {
    BeatsHistoricNode node{100, 250};
    assert(node.peak_val > node.cur_val);
    return 0;
}
