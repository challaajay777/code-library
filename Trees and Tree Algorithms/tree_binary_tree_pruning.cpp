// Algorithm: Binary Tree Subtree Pruning
// Purpose: Prunes every subtree in a binary tree that does not contain a target value 1.
// Time Complexity: O(N)
// Space Complexity: O(H) recursion
// Preconditions: Binary tree with 0 and 1 values.

#include <iostream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* prune_tree(TreeNode* root) {
    if (!root) return nullptr;
    root->left = prune_tree(root->left);
    root->right = prune_tree(root->right);
    if (root->val == 0 && !root->left && !root->right) {
        delete root;
        return nullptr;
    }
    return root;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(0);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(1);

    root = prune_tree(root);
    assert(root != nullptr);
    assert(root->right->left == nullptr);
    assert(root->right->right != nullptr);
    return 0;
}
