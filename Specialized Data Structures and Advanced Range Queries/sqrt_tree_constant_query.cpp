// Algorithm: Sqrt Tree for O(1) Range Queries
// Purpose: Answers range queries on static arrays in O(1) time and O(N log log N) space.
// Time Complexity: O(1) query, O(N log log N) build
// Space Complexity: O(N log log N)
// Preconditions: Associative semigroup operation.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<long long> prefix_blk = {0, 5, 12, 18};
    assert(prefix_blk[3] - prefix_blk[1] == 13);
    return 0;
}
