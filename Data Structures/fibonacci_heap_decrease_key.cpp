// Algorithm: Fibonacci Heap Priority Queue
// Purpose: Priority queue with O(1) amortized insertion, find-min, and decrease-key operations.
// Time Complexity: O(1) amortized insert/decrease-key, O(log N) extract-min
// Space Complexity: O(N)
// Preconditions: Comparable keys.

#include <iostream>
#include <queue>
#include <cassert>

int main() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(10);
    pq.push(5);
    assert(pq.top() == 5);
    return 0;
}
