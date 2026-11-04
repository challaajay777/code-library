// Algorithm: AVL Tree Self-Balancing BST
// Purpose: Maintains strict height-balanced BST with max height difference 1 using single/double rotations.
// Time Complexity: O(log N) insert/delete/search
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <algorithm>
#include <cassert>

struct AVLNode {
    int key, height = 1;
    AVLNode *left = nullptr, *right = nullptr;
    AVLNode(int k) : key(k) {}
};

int h(AVLNode* n) { return n ? n->height : 0; }
int get_balance(AVLNode* n) { return n ? h(n->left) - h(n->right) : 0; }

AVLNode* rot_right(AVLNode* y) {
    AVLNode* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = std::max(h(y->left), h(y->right)) + 1;
    x->height = std::max(h(x->left), h(x->right)) + 1;
    return x;
}

AVLNode* rot_left(AVLNode* x) {
    AVLNode* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = std::max(h(x->left), h(x->right)) + 1;
    y->height = std::max(h(y->left), h(y->right)) + 1;
    return y;
}

AVLNode* insert_avl(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);
    if (key < node->key) node->left = insert_avl(node->left, key);
    else if (key > node->key) node->right = insert_avl(node->right, key);
    else return node;

    node->height = 1 + std::max(h(node->left), h(node->right));
    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key) return rot_right(node);
    if (balance < -1 && key > node->right->key) return rot_left(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rot_left(node->left);
        return rot_right(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rot_right(node->right);
        return rot_left(node);
    }
    return node;
}

int main() {
    AVLNode* root = nullptr;
    for (int x : {10, 20, 30, 40, 50, 25}) {
        root = insert_avl(root, x);
    }
    assert(root->key == 30);
    return 0;
}
