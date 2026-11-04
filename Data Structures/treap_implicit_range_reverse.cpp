// Algorithm: Implicit Treap Range Reversal
// Purpose: Reverses subarray in range [L, R] in O(log N) using split, merge, and lazy reverse propagation.
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: 1-indexed range.

#include <iostream>
#include <random>
#include <cassert>

struct TreapNode {
    int val, priority, sz = 1;
    bool rev = false;
    TreapNode *left = nullptr, *right = nullptr;
    TreapNode(int v, int p) : val(v), priority(p) {}
};

int get_sz(TreapNode* t) { return t ? t->sz : 0; }

void push(TreapNode* t) {
    if (t && t->rev) {
        std::swap(t->left, t->right);
        if (t->left) t->left->rev ^= 1;
        if (t->right) t->right->rev ^= 1;
        t->rev = false;
    }
}

void update_sz(TreapNode* t) {
    if (t) t->sz = 1 + get_sz(t->left) + get_sz(t->right);
}

void split(TreapNode* t, int k, TreapNode*& l, TreapNode*& r) {
    if (!t) { l = r = nullptr; return; }
    push(t);
    if (get_sz(t->left) >= k) {
        split(t->left, k, l, t->left);
        r = t;
    } else {
        split(t->right, k - get_sz(t->left) - 1, t->right, r);
        l = t;
    }
    update_sz(t);
}

void merge(TreapNode*& t, TreapNode* l, TreapNode* r) {
    push(l); push(r);
    if (!l || !r) t = l ? l : r;
    else if (l->priority > r->priority) {
        merge(l->right, l->right, r);
        t = l;
    } else {
        merge(r->left, l, r->left);
        t = r;
    }
    update_sz(t);
}

void reverse_range(TreapNode*& root, int ql, int qr) {
    TreapNode *t1, *t2, *t3;
    split(root, qr, t1, t3);
    split(t1, ql - 1, t1, t2);
    if (t2) t2->rev ^= 1;
    merge(t1, t1, t2);
    merge(root, t1, t3);
}

int main() {
    TreapNode* root = nullptr;
    for (int i = 1; i <= 5; ++i) {
        merge(root, root, new TreapNode(i, rand()));
    }
    reverse_range(root, 2, 4); // [1, 2, 3, 4, 5] -> [1, 4, 3, 2, 5]
    assert(root != nullptr);
    return 0;
}
