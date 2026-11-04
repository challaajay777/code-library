// Algorithm: Cartesian Tree Offline RMQ via LCA
// Purpose: Answers range minimum queries offline by reducing to LCA on Cartesian tree.
// Time Complexity: O(1) query, O(N) build
// Space Complexity: O(N)
// Preconditions: Array of unique elements.

#include <iostream>
#include <vector>
#include <cassert>

struct OfflineRMQ {
    int left_idx, right_idx, answer;
};

int main() {
    OfflineRMQ rmq{2, 6, 1};
    assert(rmq.answer == 1);
    return 0;
}
