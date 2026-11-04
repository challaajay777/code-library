// Algorithm: Leftist Heap (Mergeable Priority Queue)
// Purpose: Priority queue supporting O(log N) heap merge based on null path length (s-value) property.
// Time Complexity: O(log N) merge, insert, and delete-min
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <algorithm>
#include <cassert>

struct LeftistNode {
    int val, npl = 0;
    LeftistNode *left = nullptr, *right = nullptr;
    LeftistNode(int v) : val(v) {}
};

LeftistNode* merge_leftist(LeftistNode* h1, LeftistNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;
    if (h1->val > h2->val) std::swap(h1, h2);

    h1->right = merge_leftist(h1->right, h2);
    if (!h1->left || h1->left->npl < h1->right->npl) {
        std::swap(h1->left, h1->right);
    }
    h1->npl = h1->right ? h1->right->npl + 1 : 0;
    return h1;
}

int main() {
    LeftistNode* h1 = new LeftistNode(10);
    h1 = merge_leftist(h1, new LeftistNode(20));

    LeftistNode* h2 = new LeftistNode(5);
    h2 = merge_leftist(h2, new LeftistNode(15));

    LeftistNode* h = merge_leftist(h1, h2);
    assert(h->val == 5);
    return 0;
}
