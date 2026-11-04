// Algorithm: Distribute Coins in Binary Tree
// Purpose: Calculates minimum moves to distribute coins so that every node has exactly 1 coin.
// Time Complexity: O(N)
// Space Complexity: O(H) recursion
// Preconditions: Binary tree where total coins equals number of nodes.

#include <iostream>
#include <cmath>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int coin_moves = 0;

int dfs_coins(TreeNode* root) {
    if (!root) return 0;
    int left_balance = dfs_coins(root->left);
    int right_balance = dfs_coins(root->right);
    coin_moves += std::abs(left_balance) + std::abs(right_balance);
    return root->val + left_balance + right_balance - 1;
}

int distribute_coins(TreeNode* root) {
    coin_moves = 0;
    dfs_coins(root);
    return coin_moves;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(0);
    root->right = new TreeNode(0);
    assert(distribute_coins(root) == 2);
    return 0;
}
