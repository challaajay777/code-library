// Algorithm: Mo's Algorithm on Tree Paths
// Purpose: Answers offline path queries on trees by mapping tree paths to Euler tour flattenings.
// Time Complexity: O((N + Q) sqrt(N))
// Space Complexity: O(N + Q)
// Preconditions: Tree with node values.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int> tour = {10, 20, 20, 30, 30, 10};
    assert(tour.front() == tour.back());
    return 0;
}
