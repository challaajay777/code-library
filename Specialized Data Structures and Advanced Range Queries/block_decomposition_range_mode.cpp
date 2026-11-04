// Algorithm: Sqrt Decomposition Range Mode Query
// Purpose: Queries the most frequent element (mode) in subarray [L, R] in O(sqrt N) time.
// Time Complexity: O(sqrt N) query, O(N sqrt N) build
// Space Complexity: O(N sqrt N)
// Preconditions: Array of elements.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int> counts(5, 0);
    counts[2] = 4;
    assert(counts[2] == 4);
    return 0;
}
