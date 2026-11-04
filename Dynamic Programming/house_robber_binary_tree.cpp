// Algorithm: House Robber on Binary Tree DP
// Purpose: Finds max amount robbed on binary tree where no two directly connected nodes can be robbed.
// Time Complexity: O(N)
// Space Complexity: O(H) recursion stack
// Preconditions: Binary tree node structure with values.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

struct RobResult {
    int rob_cur;
    int not_rob_cur;
};

RobResult dfs_tree(TreeNode* root) {
    if (!root) return {0, 0};
    RobResult l = dfs_tree(root->left);
    RobResult r = dfs_tree(root->right);

    int rob = root->val + l.not_rob_cur + r.not_rob_cur;
    int not_rob = std::max(l.rob_cur, l.not_rob_cur) + std::max(r.rob_cur, r.not_rob_cur);
    return {rob, not_rob};
}

int rob_tree(TreeNode* root) {
    auto res = dfs_tree(root);
    return std::max(res.rob_cur, res.not_rob_cur);
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);

    // Rob 3 (root) + 3 (left->right) + 1 (right->right) = 7
    assert(rob_tree(root) == 7);
    return 0;
}
