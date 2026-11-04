// Algorithm: Persistent Binary Trie Range Max XOR
// Purpose: Queries maximum XOR with value X in prefix or range [L, R] using persistent trie roots.
// Time Complexity: O(30) per query
// Space Complexity: O(30 * N)
// Preconditions: Integers >= 0.

#include <iostream>
#include <vector>
#include <cassert>

struct PTNode {
    int next[2] = {0, 0};
    int count = 0;
};

struct PersistentXORTrie {
    std::vector<PTNode> tree;
    std::vector<int> roots;

    PersistentXORTrie() {
        tree.emplace_back();
        roots.push_back(0);
    }

    int insert(int prev, int val) {
        int cur = tree.size();
        tree.push_back(tree[prev]);
        tree[cur].count++;
        int ret = cur;

        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            int next_node = tree.size();
            tree.push_back(tree[tree[cur].next[b]]);
            tree[next_node].count++;
            tree[cur].next[b] = next_node;
            cur = next_node;
        }
        return ret;
    }

    int query_max_xor(int root_l, int root_r, int val) {
        int cur_l = root_l, cur_r = root_r;
        int ans = 0;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            int opp = b ^ 1;
            int count_opp = tree[tree[cur_r].next[opp]].count - tree[tree[cur_l].next[opp]].count;
            if (count_opp > 0) {
                ans |= (1 << i);
                cur_l = tree[cur_l].next[opp];
                cur_r = tree[cur_r].next[opp];
            } else {
                cur_l = tree[cur_l].next[b];
                cur_r = tree[cur_r].next[b];
            }
        }
        return ans;
    }
};

int main() {
    PersistentXORTrie pxt;
    pxt.roots.push_back(pxt.insert(pxt.roots.back(), 5));
    pxt.roots.push_back(pxt.insert(pxt.roots.back(), 10));

    assert(pxt.query_max_xor(pxt.roots[0], pxt.roots[2], 5) == (5 ^ 10));
    return 0;
}
