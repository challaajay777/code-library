// Algorithm: Skew Heap Self-Adjusting Mergeable Heap
// Purpose: Self-adjusting mergeable heap that unconditionally swaps subtrees during O(log N) amortized merge.
// Time Complexity: O(log N) amortized
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <cassert>

struct SkewNode {
    int val;
    SkewNode *left = nullptr, *right = nullptr;
    SkewNode(int v) : val(v) {}
};

SkewNode* merge_skew(SkewNode* h1, SkewNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;
    if (h1->val > h2->val) std::swap(h1, h2);

    SkewNode* temp = merge_skew(h1->right, h2);
    h1->right = h1->left;
    h1->left = temp;
    return h1;
}

int main() {
    SkewNode* h = merge_skew(new SkewNode(10), new SkewNode(5));
    assert(h->val == 5);
    return 0;
}
