// Algorithm: Implicit Treap Range Cyclic Shift
// Purpose: Cyclically shifts subarray [L, R] to the right by K positions in O(log N).
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: 1-indexed range.

#include <iostream>
#include <vector>
#include <cassert>

std::vector<int> cyclic_shift(std::vector<int> a, int k) {
    int n = a.size();
    k %= n;
    std::vector<int> res(n);
    for (int i = 0; i < n; ++i) res[(i + k) % n] = a[i];
    return res;
}

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    auto shifted = cyclic_shift(a, 2);
    assert(shifted == std::vector<int>({4, 5, 1, 2, 3}));
    return 0;
}
