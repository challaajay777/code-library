// Algorithm: Recursive LCA in Binary Tree
// Purpose: Finds lowest common ancestor of two nodes in binary tree without parent pointers.
// Time Complexity: O(N)
// Space Complexity: O(H)
// Preconditions: Binary tree containing both target nodes.

#include <iostream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* lowest_common_ancestor_bt(TreeNode* root, int p, int q) {
    if (!root || root->val == p || root->val == q) return root;
    TreeNode* left = lowest_common_ancestor_bt(root->left, p, q);
    TreeNode* right = lowest_common_ancestor_bt(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);

    TreeNode* lca = lowest_common_ancestor_bt(root, 5, 1);
    assert(lca == root);
    TreeNode* lca2 = lowest_common_ancestor_bt(root, 5, 2);
    assert(lca2 == root->left);
    return 0;
}
