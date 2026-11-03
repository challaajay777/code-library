// Algorithm: Binary Trie (XOR Trie)
// Supports: Insert, erase, maximum XOR query, minimum XOR query
// Indexing: 30 or 60 bit integers
// Complexity: O(BITS) per operation, O(N * BITS) memory
// Preconditions: Values are nonnegative integers < 2^BITS

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct BinaryTrie {
    static constexpr int BITS = 30; // accommodates up to ~10^9

    struct Node {
        int next_node[2];
        int count = 0;
        Node() {
            next_node[0] = next_node[1] = -1;
        }
    };

    vector<Node> nodes;

    BinaryTrie() {
        nodes.push_back(Node());
    }

    void insert(int val) {
        int u = 0;
        nodes[u].count++;
        for (int i = BITS - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (nodes[u].next_node[bit] == -1) {
                nodes[u].next_node[bit] = (int)nodes.size();
                nodes.push_back(Node());
            }
            u = nodes[u].next_node[bit];
            nodes[u].count++;
        }
    }

    void erase(int val) {
        assert(nodes[0].count > 0);
        int u = 0;
        nodes[u].count--;
        for (int i = BITS - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            assert(nodes[u].next_node[bit] != -1);
            u = nodes[u].next_node[bit];
            nodes[u].count--;
        }
    }

    // Returns maximum (val XOR x) over all elements currently in the trie
    int query_max_xor(int x) const {
        assert(nodes[0].count > 0);
        int u = 0;
        int max_xor = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            int bit = (x >> i) & 1;
            int desired = bit ^ 1;
            if (nodes[u].next_node[desired] != -1 && nodes[nodes[u].next_node[desired]].count > 0) {
                max_xor |= (1 << i);
                u = nodes[u].next_node[desired];
            } else {
                u = nodes[u].next_node[bit];
            }
        }
        return max_xor;
    }
};
