// Algorithm: Policy-Based Data Structure Ordered Set (PBDS)
// Purpose: Demonstrates GCC policy-based tree for rank queries (order_of_key) and k-th element (find_by_order).
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Compiled with GNU C++.

#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <cassert>

using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ordered_set<int> os;
    os.insert(1);
    os.insert(2);
    os.insert(4);
    os.insert(8);
    os.insert(16);

    // find_by_order: 0-indexed k-th element
    assert(*os.find_by_order(0) == 1);
    assert(*os.find_by_order(2) == 4);

    // order_of_key: number of strictly smaller elements
    assert(os.order_of_key(4) == 2);
    assert(os.order_of_key(10) == 4);
    return 0;
}
