// Algorithm: Binary XOR Trie K-th Smallest XOR Query
// Purpose: Finds the k-th smallest element XORed with a given query value in O(30).
// Time Complexity: O(30) per query
// Space Complexity: O(30 * N)
// Preconditions: Integers >= 0, 1 <= k <= tree size.

#include <iostream>
#include <vector>
#include <cassert>

struct KthXORTrie {
    struct Node {
        int next[2] = {-1, -1};
        int count = 0;
    };
    std::vector<Node> tree;

    KthXORTrie() { tree.emplace_back(); }

    void insert(int val) {
        int cur = 0;
        tree[cur].count++;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (tree[cur].next[b] == -1) {
                tree[cur].next[b] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[b];
            tree[cur].count++;
        }
    }

    int query_kth_xor(int x, int k) {
        int cur = 0, res = 0;
        for (int i = 29; i >= 0; --i) {
            int b = (x >> i) & 1;
            int left_cnt = (tree[cur].next[b] != -1) ? tree[tree[cur].next[b]].count : 0;
            if (k <= left_cnt) {
                cur = tree[cur].next[b];
            } else {
                k -= left_cnt;
                cur = tree[cur].next[b ^ 1];
                res |= (1 << i);
            }
        }
        return res;
    }
};

int main() {
    KthXORTrie kt;
    kt.insert(5);
    kt.insert(10);
    // x = 0: 1st smallest XOR is 5 ^ 0 = 5, 2nd is 10 ^ 0 = 10
    assert(kt.query_kth_xor(0, 1) == 5);
    assert(kt.query_kth_xor(0, 2) == 10);
    return 0;
}
