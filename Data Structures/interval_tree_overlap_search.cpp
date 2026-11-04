// Algorithm: Interval Tree Overlapping Interval Search
// Purpose: Augmented binary search tree searching for any interval overlapping with query [low, high].
// Time Complexity: O(log N) search/insert
// Space Complexity: O(N)
// Preconditions: Valid intervals with low <= high.

#include <iostream>
#include <cassert>
#include <algorithm>

struct Interval {
    int low, high;
};

struct ITNode {
    Interval i;
    int max_high;
    ITNode *left = nullptr, *right = nullptr;
    ITNode(Interval iv) : i(iv), max_high(iv.high) {}
};

ITNode* insert_interval(ITNode* root, Interval iv) {
    if (!root) return new ITNode(iv);
    if (iv.low < root->i.low) root->left = insert_interval(root->left, iv);
    else root->right = insert_interval(root->right, iv);
    root->max_high = std::max(root->max_high, iv.high);
    return root;
}

bool overlaps(Interval a, Interval b) {
    return a.low <= b.high && b.low <= a.high;
}

Interval* search_overlap(ITNode* root, Interval q) {
    if (!root) return nullptr;
    if (overlaps(root->i, q)) return &(root->i);
    if (root->left && root->left->max_high >= q.low) {
        return search_overlap(root->left, q);
    }
    return search_overlap(root->right, q);
}

int main() {
    ITNode* root = nullptr;
    root = insert_interval(root, {15, 20});
    root = insert_interval(root, {10, 30});
    root = insert_interval(root, {17, 19});
    root = insert_interval(root, {5, 20});

    Interval* res = search_overlap(root, {6, 7});
    assert(res != nullptr);
    assert(overlaps(*res, {6, 7}));
    return 0;
}
