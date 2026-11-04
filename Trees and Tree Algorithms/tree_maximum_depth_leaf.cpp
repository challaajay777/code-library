// Algorithm: Deepest Leaves Sum and Deepest Path
// Purpose: Finds the maximum depth among all leaves and computes sum of deepest leaves in O(N).
// Time Complexity: O(N)
// Space Complexity: O(H)
// Preconditions: Binary tree.

#include <iostream>
#include <cassert>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int max_depth = 0, sum_deepest = 0;

void dfs_deepest(TreeNode* root, int depth) {
    if (!root) return;
    if (depth > max_depth) {
        max_depth = depth;
        sum_deepest = root->val;
    } else if (depth == max_depth) {
        sum_deepest += root->val;
    }
    dfs_deepest(root->left, depth + 1);
    dfs_deepest(root->right, depth + 1);
}

int deepest_leaves_sum(TreeNode* root) {
    max_depth = 0;
    sum_deepest = 0;
    dfs_deepest(root, 0);
    return sum_deepest;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    assert(deepest_leaves_sum(root) == 9); // 4 + 5 = 9
    return 0;
}
