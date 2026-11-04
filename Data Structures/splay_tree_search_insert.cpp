// Algorithm: Splay Tree Dynamic Set Operations
// Purpose: Self-adjusting binary search tree where accessed elements are splayed to the root in O(log N) amortized.
// Time Complexity: O(log N) amortized
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <cassert>

struct SplayNode {
    int key;
    SplayNode *left = nullptr, *right = nullptr;
    SplayNode(int k) : key(k) {}
};

SplayNode* right_rotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* left_rotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* splay(SplayNode* root, int key) {
    if (!root || root->key == key) return root;

    if (root->key > key) {
        if (!root->left) return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = right_rotate(root);
        } else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = left_rotate(root->left);
        }
        return root->left ? right_rotate(root) : root;
    } else {
        if (!root->right) return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = right_rotate(root->right);
        } else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = left_rotate(root);
        }
        return root->right ? left_rotate(root) : root;
    }
}

SplayNode* insert(SplayNode* root, int k) {
    if (!root) return new SplayNode(k);
    root = splay(root, k);
    if (root->key == k) return root;

    SplayNode* new_node = new SplayNode(k);
    if (root->key > k) {
        new_node->right = root;
        new_node->left = root->left;
        root->left = nullptr;
    } else {
        new_node->left = root;
        new_node->right = root->right;
        root->right = nullptr;
    }
    return new_node;
}

int main() {
    SplayNode* root = nullptr;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 200);

    root = splay(root, 50);
    assert(root->key == 50);
    return 0;
}
