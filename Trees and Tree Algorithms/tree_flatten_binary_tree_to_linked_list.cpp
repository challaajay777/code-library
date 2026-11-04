// Algorithm: Flatten Binary Tree to Linked List In-Place
// Purpose: Flattens binary tree into preorder in-place linked list using right pointers.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Binary tree.

#include <iostream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void flatten(TreeNode* root) {
    TreeNode* cur = root;
    while (cur) {
        if (cur->left) {
            TreeNode* pre = cur->left;
            while (pre->right) pre = pre->right;
            pre->right = cur->right;
            cur->right = cur->left;
            cur->left = nullptr;
        }
        cur = cur->right;
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);

    flatten(root);
    assert(root->left == nullptr);
    assert(root->right->val == 2);
    assert(root->right->right->val == 5);
    return 0;
}
