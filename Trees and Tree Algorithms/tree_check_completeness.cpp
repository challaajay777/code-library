// Algorithm: Check Completeness of Binary Tree
// Purpose: Determines whether a binary tree is a complete binary tree using level BFS.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Binary tree.

#include <iostream>
#include <queue>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool is_complete_tree(TreeNode* root) {
    if (!root) return true;
    std::queue<TreeNode*> q;
    q.push(root);
    bool seen_null = false;

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        if (!cur) {
            seen_null = true;
        } else {
            if (seen_null) return false;
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    return true;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    assert(is_complete_tree(root));

    root->left->left = nullptr;
    root->left->right = new TreeNode(4); // incomplete
    assert(!is_complete_tree(root));
    return 0;
}
