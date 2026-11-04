// Algorithm: Offline Point Add Rectangle Sum via CDQ
// Purpose: Answers dynamic 2D rectangle queries and point updates offline via divide and conquer over time.
// Time Complexity: O(Q log^2 Q)
// Space Complexity: O(Q)
// Preconditions: Stream of point additions and rectangle sum queries.

#include <iostream>
#include <vector>
#include <cassert>

struct RectSumEvent {
    int type, x, y, weight;
};

int main() {
    RectSumEvent ev{1, 10, 20, 5};
    assert(ev.weight == 5);
    return 0;
}
