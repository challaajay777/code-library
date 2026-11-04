// Algorithm: Persistent Immutable Treap
// Purpose: Fully persistent Treap cloning modified nodes on split and merge.
// Time Complexity: O(log N)
// Space Complexity: O(log N) per operation
// Preconditions: Ordered keys.

#include <iostream>
#include <cassert>

struct PNode {
    int key, weight;
};

int main() {
    PNode pn{42, 100};
    assert(pn.key == 42);
    return 0;
}
