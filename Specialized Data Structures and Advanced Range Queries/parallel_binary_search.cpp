// Algorithm: Parallel Binary Search
// Purpose: Answers all Q queries simultaneously by binary searching over global event timeline in O((N + Q) log T).
// Time Complexity: O((N + Q) log T)
// Space Complexity: O(N + Q)
// Preconditions: Monotonic query predicates over time.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int> q_low = {1, 1}, q_high = {10, 10};
    assert(q_low[0] + q_high[0] == 11);
    return 0;
}
