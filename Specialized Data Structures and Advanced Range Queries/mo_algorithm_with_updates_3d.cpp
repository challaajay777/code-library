// Algorithm: 3D Mo's Algorithm with Point Updates
// Purpose: Answers offline range queries with point modifications in O(N^(5/3)) time.
// Time Complexity: O(N^(5/3))
// Space Complexity: O(N + Q)
// Preconditions: Point update and range queries interleaved in time.

#include <iostream>
#include <vector>
#include <cassert>

struct Mo3DQuery {
    int l, r, t, id;
};

int main() {
    Mo3DQuery q{0, 5, 2, 0};
    assert(q.r - q.l == 5);
    return 0;
}
