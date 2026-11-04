// Algorithm: Morris Inorder Traversal (O(1) Extra Space)
// Purpose: Traverses binary tree in inorder without recursion or stack using threaded binary trees.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Binary tree.

#include <iostream>
#include <vector>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

std::vector<int> morris_inorder(TreeNode* root) {
    std::vector<int> res;
    TreeNode* cur = root;

    while (cur) {
        if (!cur->left) {
            res.push_back(cur->val);
            cur = cur->right;
        } else {
            TreeNode* pre = cur->left;
            while (pre->right && pre->right != cur) pre = pre->right;

            if (!pre->right) {
                pre->right = cur;
                cur = cur->left;
            } else {
                pre->right = nullptr;
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
    }
    return res;
}

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    auto in = morris_inorder(root);
    assert(in == std::vector<int>({1, 2, 3}));
    return 0;
}
