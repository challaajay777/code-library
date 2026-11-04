// Algorithm: Red-Black Tree Insertion
// Purpose: Self-balancing binary search tree maintaining black-height and no-consecutive-red invariant.
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Comparable keys.

#include <iostream>
#include <set>
#include <cassert>

int main() {
    std::set<int> rb_set;
    rb_set.insert(10);
    rb_set.insert(5);
    rb_set.insert(20);
    assert(*rb_set.begin() == 5);
    return 0;
}
