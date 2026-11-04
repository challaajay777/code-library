// Algorithm: Sum Root to Leaf Numbers in Binary Tree
// Purpose: Calculates the total sum of all numbers formed by root-to-leaf paths.
// Time Complexity: O(N)
// Space Complexity: O(H)
// Preconditions: Binary tree with single-digit node values.

#include <iostream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int sum_numbers_dfs(TreeNode* root, int cur) {
    if (!root) return 0;
    cur = cur * 10 + root->val;
    if (!root->left && !root->right) return cur;
    return sum_numbers_dfs(root->left, cur) + sum_numbers_dfs(root->right, cur);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    // 12 + 13 = 25
    assert(sum_numbers_dfs(root, 0) == 25);
    return 0;
}
