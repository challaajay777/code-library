// Algorithm: Vertical Order Traversal of Binary Tree
// Purpose: Traverses binary tree column-by-column from leftmost to rightmost vertical line.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Binary tree.

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void dfs_vertical(TreeNode* root, int col, int row, std::map<int, std::vector<std::pair<int, int>>>& nodes) {
    if (!root) return;
    nodes[col].push_back({row, root->val});
    dfs_vertical(root->left, col - 1, row + 1, nodes);
    dfs_vertical(root->right, col + 1, row + 1, nodes);
}

std::vector<std::vector<int>> vertical_traversal(TreeNode* root) {
    std::map<int, std::vector<std::pair<int, int>>> nodes;
    dfs_vertical(root, 0, 0, nodes);

    std::vector<std::vector<int>> result;
    for (auto& [col, vec] : nodes) {
        std::sort(vec.begin(), vec.end());
        std::vector<int> col_vals;
        for (const auto& p : vec) col_vals.push_back(p.second);
        result.push_back(col_vals);
    }
    return result;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    auto res = vertical_traversal(root);
    assert(res.size() == 4);
    assert(res[0] == std::vector<int>({9}));
    return 0;
}
