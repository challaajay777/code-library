// Algorithm: Randomized Tree Subtree Polynomial Hashing
// Purpose: Computes hash for each subtree invariant to vertex ordering to test tree isomorphism.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Rooted tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

unsigned long long shift_hash(unsigned long long x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

unsigned long long tree_hash(int u, int p, const std::vector<std::vector<int>>& adj) {
    unsigned long long h = 1;
    for (int v : adj[u]) {
        if (v != p) {
            h += shift_hash(tree_hash(v, u, adj));
        }
    }
    return h;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> t1(n), t2(n);
    t1[0] = {1, 2}; t1[1] = {0}; t1[2] = {0};
    t2[0] = {2, 1}; t2[1] = {0}; t2[2] = {0};

    assert(tree_hash(0, -1, t1) == tree_hash(0, -1, t2));
    return 0;
}
