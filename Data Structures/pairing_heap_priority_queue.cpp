// Algorithm: Pairing Heap Priority Queue
// Purpose: Heap data structure with O(1) amortized insert and merge, and O(log N) extract-min.
// Time Complexity: O(1) insert/merge, O(log N) extract-min
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <vector>
#include <cassert>

struct PairNode {
    int val;
    PairNode* child = nullptr;
    PairNode* sibling = nullptr;
    PairNode(int v) : val(v) {}
};

PairNode* merge(PairNode* h1, PairNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;
    if (h1->val > h2->val) std::swap(h1, h2);
    h2->sibling = h1->child;
    h1->child = h2;
    return h1;
}

PairNode* two_pass_merge(PairNode* node) {
    if (!node || !node->sibling) return node;
    PairNode* a = node;
    PairNode* b = node->sibling;
    PairNode* next_pairs = node->sibling->sibling;
    a->sibling = b->sibling = nullptr;
    return merge(merge(a, b), two_pass_merge(next_pairs));
}

int main() {
    PairNode* root = nullptr;
    root = merge(root, new PairNode(10));
    root = merge(root, new PairNode(5));
    root = merge(root, new PairNode(20));

    assert(root->val == 5);
    root = two_pass_merge(root->child);
    assert(root->val == 10);
    return 0;
}
