// Algorithm: Path Sum III (Downwards Paths Sum to Target)
// Purpose: Finds number of paths that sum to target value not necessarily starting at root.
// Time Complexity: O(N)
// Space Complexity: O(H)
// Preconditions: Binary tree with integer values.

#include <iostream>
#include <unordered_map>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int dfs_path_sum(TreeNode* root, long long cur_sum, long long target, std::unordered_map<long long, int>& pref) {
    if (!root) return 0;
    cur_sum += root->val;
    int count = pref.count(cur_sum - target) ? pref[cur_sum - target] : 0;

    pref[cur_sum]++;
    count += dfs_path_sum(root->left, cur_sum, target, pref);
    count += dfs_path_sum(root->right, cur_sum, target, pref);
    pref[cur_sum]--;
    return count;
}

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);

    std::unordered_map<long long, int> pref;
    pref[0] = 1;
    assert(dfs_path_sum(root, 0, 8, pref) == 2); // 5+3 and 10+5+2-9? 5+3=8, 10+(-3)+...
    return 0;
}
