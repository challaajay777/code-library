// Algorithm: Dynamic Segment Tree with Sparse Allocation
// Purpose: Allocates nodes on-demand to support range updates and queries over huge coordinates up to 10^9.
// Time Complexity: O(log C) per query/update
// Space Complexity: O(Q log C)
// Preconditions: Coordinate bounds in [1..10^9].

#include <iostream>
#include <cassert>

struct DynSegNode {
    long long sum = 0, lazy = 0;
    DynSegNode *left = nullptr, *right = nullptr;
};

void apply_dyn(DynSegNode* node, long long l, long long r, long long val) {
    node->sum += val * (r - l + 1);
    node->lazy += val;
}

void push_down_dyn(DynSegNode* node, long long l, long long r) {
    if (!node->left) node->left = new DynSegNode();
    if (!node->right) node->right = new DynSegNode();
    if (node->lazy) {
        long long mid = l + (r - l) / 2;
        apply_dyn(node->left, l, mid, node->lazy);
        apply_dyn(node->right, mid + 1, r, node->lazy);
        node->lazy = 0;
    }
}

void update_dyn(DynSegNode* node, long long l, long long r, long long ql, long long qr, long long val) {
    if (ql <= l && r <= qr) {
        apply_dyn(node, l, r, val);
        return;
    }
    push_down_dyn(node, l, r);
    long long mid = l + (r - l) / 2;
    if (ql <= mid) update_dyn(node->left, l, mid, ql, qr, val);
    if (qr > mid) update_dyn(node->right, mid + 1, r, ql, qr, val);
    node->sum = node->left->sum + node->right->sum;
}

long long query_dyn(DynSegNode* node, long long l, long long r, long long ql, long long qr) {
    if (!node || ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return node->sum;
    push_down_dyn(node, l, r);
    long long mid = l + (r - l) / 2;
    return query_dyn(node->left, l, mid, ql, qr) + query_dyn(node->right, mid + 1, r, ql, qr);
}

int main() {
    DynSegNode* root = new DynSegNode();
    update_dyn(root, 1, 1000000000, 10, 20, 5);
    assert(query_dyn(root, 1, 1000000000, 15, 25) == 30); // 6 elements in [15, 20] with value 5
    return 0;
}
