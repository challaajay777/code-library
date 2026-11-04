// Algorithm: Count Good Nodes in Binary Tree
// Purpose: Counts nodes where no ancestor has a value strictly greater than node value.
// Time Complexity: O(N)
// Space Complexity: O(H)
// Preconditions: Binary tree.

#include <iostream>
#include <algorithm>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int count_good(TreeNode* root, int max_so_far) {
    if (!root) return 0;
    int good = (root->val >= max_so_far) ? 1 : 0;
    int next_max = std::max(max_so_far, root->val);
    return good + count_good(root->left, next_max) + count_good(root->right, next_max);
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->left = new TreeNode(3);
    root->right->right = new TreeNode(5);

    assert(count_good(root, root->val) == 4);
    return 0;
}
