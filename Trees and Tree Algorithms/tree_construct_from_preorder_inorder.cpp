// Algorithm: Construct Binary Tree from Preorder and Inorder Traversal
// Purpose: Rebuilds unique binary tree from its preorder and inorder sequences in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Arrays of unique values.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* build_pre_in(int pre_start, int in_start, int in_end,
                      const std::vector<int>& pre,
                      const std::unordered_map<int, int>& in_pos) {
    if (in_start > in_end) return nullptr;
    int val = pre[pre_start];
    TreeNode* root = new TreeNode(val);
    int in_idx = in_pos.at(val);
    int left_size = in_idx - in_start;

    root->left = build_pre_in(pre_start + 1, in_start, in_idx - 1, pre, in_pos);
    root->right = build_pre_in(pre_start + 1 + left_size, in_idx + 1, in_end, pre, in_pos);
    return root;
}

int main() {
    std::vector<int> pre = {3, 9, 20, 15, 7};
    std::vector<int> in = {9, 3, 15, 20, 7};
    std::unordered_map<int, int> in_pos;
    for (size_t i = 0; i < in.size(); ++i) in_pos[in[i]] = i;

    TreeNode* root = build_pre_in(0, 0, in.size() - 1, pre, in_pos);
    assert(root->val == 3);
    assert(root->left->val == 9);
    assert(root->right->val == 20);
    return 0;
}
