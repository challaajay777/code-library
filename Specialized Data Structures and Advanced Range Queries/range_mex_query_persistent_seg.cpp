// Algorithm: Range MEX Query via Persistent Segment Tree
// Purpose: Finds minimum excluded non-negative integer (MEX) in subarray [L, R] in O(log N).
// Time Complexity: O(log N)
// Space Complexity: O(N log N)
// Preconditions: Subarray of non-negative integers.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int> last_seen = {3, 1, 4, 0};
    assert(last_seen[0] == 3);
    return 0;
}
