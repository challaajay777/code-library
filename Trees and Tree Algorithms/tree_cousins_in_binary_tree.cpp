// Algorithm: Cousins in Binary Tree Verification
// Purpose: Determines if two nodes are cousins (same depth, different parents).
// Time Complexity: O(N)
// Space Complexity: O(H)
// Preconditions: Binary tree with unique values.

#include <iostream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void dfs_cousins(TreeNode* root, int p, int d, int target, int& out_p, int& out_d) {
    if (!root) return;
    if (root->val == target) {
        out_p = p;
        out_d = d;
        return;
    }
    dfs_cousins(root->left, root->val, d + 1, target, out_p, out_d);
    dfs_cousins(root->right, root->val, d + 1, target, out_p, out_d);
}

bool is_cousins(TreeNode* root, int x, int y) {
    int px = -1, dx = -1, py = -1, dy = -1;
    dfs_cousins(root, -1, 0, x, px, dx);
    dfs_cousins(root, -1, 0, y, py, dy);
    return (dx == dy && px != py);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(5);

    assert(is_cousins(root, 4, 5));
    assert(!is_cousins(root, 2, 3));
    return 0;
}
