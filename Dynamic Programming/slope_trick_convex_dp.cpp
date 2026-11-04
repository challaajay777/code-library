// Algorithm: Slope Trick for Piecewise Linear Convex Optimization
// Purpose: Optimizes functions maintaining slope change points using dual priority queues.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Convex objective with unit slope changes.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <cmath>

long long make_non_decreasing(const std::vector<int>& a) {
    // Minimum operations to make array non-decreasing with absolute deviation cost
    std::priority_queue<int> pq; // max-heap storing slope changing points
    long long cost = 0;

    for (int x : a) {
        if (!pq.empty() && pq.top() > x) {
            cost += pq.top() - x;
            pq.pop();
            pq.push(x);
        }
        pq.push(x);
    }
    return cost;
}

int main() {
    std::vector<int> a = {5, 4, 3, 2, 1};
    // Make non-decreasing: minimum modifications = 6
    assert(make_non_decreasing(a) == 6);
    return 0;
}
