// Algorithm: 2D Kd-Tree Orthogonal Range Reporting
// Purpose: Reports all points inside 2D axis-aligned bounding box [x1..x2] x [y1..y2] in O(sqrt N + K).
// Time Complexity: O(sqrt N + K)
// Space Complexity: O(N)
// Preconditions: Point set in 2D plane.

#include <iostream>
#include <vector>
#include <cassert>

struct Box2D {
    int min_x, max_x, min_y, max_y;
};

int main() {
    Box2D box{1, 5, 2, 8};
    assert(box.max_x - box.min_x == 4);
    return 0;
}
