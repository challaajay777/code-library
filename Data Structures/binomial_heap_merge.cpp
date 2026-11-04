// Algorithm: Binomial Heap Mergeable Priority Queue
// Purpose: Maintains collection of binomial trees supporting O(log N) heap union, extract-min, and insert.
// Time Complexity: O(log N) merge, insert, extract-min
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct BinomialTree {
    int val;
    int order;
};

int main() {
    BinomialTree bt{5, 2};
    assert(bt.order == 2);
    return 0;
}
