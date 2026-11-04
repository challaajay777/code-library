// Algorithm: Construct Binary Tree from Postorder and Inorder Traversal
// Purpose: Reconstructs unique binary tree from postorder and inorder sequences in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Arrays of unique elements.

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

TreeNode* build_post_in(int post_end, int in_start, int in_end,
                       const std::vector<int>& post,
                       const std::unordered_map<int, int>& in_pos) {
    if (in_start > in_end) return nullptr;
    int val = post[post_end];
    TreeNode* root = new TreeNode(val);
    int in_idx = in_pos.at(val);
    int right_size = in_end - in_idx;

    root->right = build_post_in(post_end - 1, in_idx + 1, in_end, post, in_pos);
    root->left = build_post_in(post_end - 1 - right_size, in_start, in_idx - 1, post, in_pos);
    return root;
}

int main() {
    std::vector<int> in = {9, 3, 15, 20, 7};
    std::vector<int> post = {9, 15, 7, 20, 3};
    std::unordered_map<int, int> in_pos;
    for (size_t i = 0; i < in.size(); ++i) in_pos[in[i]] = i;

    TreeNode* root = build_post_in(post.size() - 1, 0, in.size() - 1, post, in_pos);
    assert(root->val == 3);
    assert(root->left->val == 9);
    assert(root->right->val == 20);
    return 0;
}
