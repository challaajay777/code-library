// Algorithm: Recover BST Two Swapped Nodes (Morris Traversal)
// Purpose: Restores BST invariant where exactly two node values were swapped in O(1) memory.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: BST with exactly two elements swapped.

#include <iostream>
#include <cassert>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void recover_bst(TreeNode* root) {
    TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
    TreeNode* cur = root;

    while (cur) {
        if (!cur->left) {
            if (prev && prev->val > cur->val) {
                if (!first) first = prev;
                second = cur;
            }
            prev = cur;
            cur = cur->right;
        } else {
            TreeNode* p = cur->left;
            while (p->right && p->right != cur) p = p->right;
            if (!p->right) {
                p->right = cur;
                cur = cur->left;
            } else {
                p->right = nullptr;
                if (prev && prev->val > cur->val) {
                    if (!first) first = prev;
                    second = cur;
                }
                prev = cur;
                cur = cur->right;
            }
        }
    }

    if (first && second) {
        std::swap(first->val, second->val);
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->right = new TreeNode(2);

    recover_bst(root);
    assert(root->val == 3);
    assert(root->left->val == 1);
    return 0;
}
