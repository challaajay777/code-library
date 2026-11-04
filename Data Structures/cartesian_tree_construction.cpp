// Algorithm: Cartesian Tree Construction in O(N)
// Purpose: Builds min-Cartesian tree using monotonic stack in linear time where inorder matches array order.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Array of distinct elements.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

struct CartesianNode {
    int val, id;
    int left = -1, right = -1, parent = -1;
};

int build_cartesian_tree(const std::vector<int>& a, std::vector<CartesianNode>& tree) {
    int n = a.size();
    tree.resize(n);
    for (int i = 0; i < n; ++i) {
        tree[i].val = a[i];
        tree[i].id = i;
    }

    std::stack<int> st;
    int root = 0;

    for (int i = 0; i < n; ++i) {
        int last = -1;
        while (!st.empty() && tree[st.top()].val > tree[i].val) {
            last = st.top();
            st.pop();
        }
        if (!st.empty()) {
            tree[st.top()].right = i;
            tree[i].parent = st.top();
        } else {
            root = i;
        }
        if (last != -1) {
            tree[i].left = last;
            tree[last].parent = i;
        }
        st.push(i);
    }
    return root;
}

int main() {
    std::vector<int> a = {9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5};
    std::vector<CartesianNode> tree;
    int root = build_cartesian_tree(a, tree);
    // Minimum element is 1 at index 3, so root should be 3
    assert(root == 3);
    return 0;
}
