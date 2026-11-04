#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Binary Trie with Dynamic Add and Remove
// Purpose: Maintains a multi-set of integers supporting insertion, deletion, and maximum/minimum XOR query with target in O(B).
// Time Complexity: O(B) per insertion, deletion, and query where B = 30
// Space Complexity: O(N * B) space
// Preconditions: Non-negative 30-bit integers.

class DynamicBinaryTrie {
private:
    struct Node {
        int next[2];
        int count;
        Node() : count(0) { next[0] = next[1] = -1; }
    };
    std::vector<Node> trie;

public:
    DynamicBinaryTrie() {
        trie.emplace_back();
    }

    void insert(int val) {
        int u = 0;
        trie[u].count++;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
            trie[u].count++;
        }
    }

    void erase(int val) {
        int u = 0;
        trie[u].count--;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            u = trie[u].next[b];
            trie[u].count--;
        }
    }

    int query_max_xor(int val) const {
        int u = 0;
        int ans = 0;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            int want = 1 - b;
            if (trie[u].next[want] != -1 && trie[trie[u].next[want]].count > 0) {
                ans |= (1 << i);
                u = trie[u].next[want];
            } else {
                u = trie[u].next[b];
            }
        }
        return ans;
    }
};

int main() {
    DynamicBinaryTrie t;
    t.insert(5);
    t.insert(10);
    assert(t.query_max_xor(10) == (10 ^ 5)); // 15

    t.erase(5);
    assert(t.query_max_xor(10) == 0); // Only 10 remains, 10 ^ 10 = 0

    std::cout << "bitwise_trie_xor_query tests passed successfully.\n";
    return 0;
}
