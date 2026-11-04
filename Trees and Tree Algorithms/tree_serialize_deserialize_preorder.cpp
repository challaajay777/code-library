// Algorithm: Preorder Binary Tree Serialization and Deserialization
// Purpose: Encodes binary tree into string and reconstructs identical tree structure.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Binary tree.

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void serialize_dfs(TreeNode* root, std::ostringstream& out) {
    if (!root) {
        out << "# ";
        return;
    }
    out << root->val << " ";
    serialize_dfs(root->left, out);
    serialize_dfs(root->right, out);
}

TreeNode* deserialize_dfs(std::istringstream& in) {
    std::string val;
    if (!(in >> val) || val == "#") return nullptr;
    TreeNode* node = new TreeNode(std::stoi(val));
    node->left = deserialize_dfs(in);
    node->right = deserialize_dfs(in);
    return node;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    std::ostringstream out;
    serialize_dfs(root, out);

    std::istringstream in(out.str());
    TreeNode* recovered = deserialize_dfs(in);
    assert(recovered->val == 1);
    assert(recovered->left->val == 2);
    assert(recovered->right->val == 3);
    return 0;
}
