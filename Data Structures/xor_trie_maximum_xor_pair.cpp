// Algorithm: Binary XOR Trie Maximum XOR Pair
// Purpose: Finds the maximum XOR value among all pairs in an integer array in O(32 * N) time.
// Time Complexity: O(32 * N)
// Space Complexity: O(32 * N)
// Preconditions: Non-negative 32-bit integers.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct XORTrie {
    struct Node {
        int next[2] = {-1, -1};
    };
    std::vector<Node> tree;

    XORTrie() { tree.emplace_back(); }

    void insert(int val) {
        int cur = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (tree[cur].next[b] == -1) {
                tree[cur].next[b] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[b];
        }
    }

    int max_xor(int val) {
        int cur = 0, res = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            int opp = b ^ 1;
            if (tree[cur].next[opp] != -1) {
                res |= (1 << i);
                cur = tree[cur].next[opp];
            } else {
                cur = tree[cur].next[b];
            }
        }
        return res;
    }
};

int find_maximum_xor(const std::vector<int>& nums) {
    XORTrie trie;
    for (int x : nums) trie.insert(x);
    int mx = 0;
    for (int x : nums) mx = std::max(mx, trie.max_xor(x));
    return mx;
}

int main() {
    std::vector<int> nums = {3, 10, 5, 25, 2, 8};
    assert(find_maximum_xor(nums) == 28); // 5 ^ 25 = 28
    return 0;
}
