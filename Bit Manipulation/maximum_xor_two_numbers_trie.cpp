#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum XOR of Two Numbers (Binary Trie)
// Purpose: Finds the maximum bitwise XOR achievable by any pair of elements in array in O(N * 31) time.
// Time Complexity: O(N * 31) time
// Space Complexity: O(N * 31) space
// Preconditions: Non-negative integers.

class MaxXorPairTrie {
private:
    struct Node {
        int next[2];
        Node() { next[0] = next[1] = -1; }
    };
    std::vector<Node> trie;

public:
    MaxXorPairTrie() {
        trie.emplace_back();
    }

    void insert(int val) {
        int u = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
        }
    }

    int query_max_xor(int val) const {
        int u = 0;
        int ans = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            int want = 1 - b;
            if (trie[u].next[want] != -1) {
                ans |= (1 << i);
                u = trie[u].next[want];
            } else {
                u = trie[u].next[b];
            }
        }
        return ans;
    }

    static int find_maximum_xor(const std::vector<int>& nums) {
        MaxXorPairTrie t;
        for (int x : nums) t.insert(x);

        int max_xor = 0;
        for (int x : nums) {
            max_xor = std::max(max_xor, t.query_max_xor(x));
        }
        return max_xor;
    }
};

int main() {
    std::vector<int> a = {3, 10, 5, 25, 2, 8};
    assert(MaxXorPairTrie::find_maximum_xor(a) == 28); // 5 ^ 25 = 28

    std::cout << "maximum_xor_two_numbers_trie tests passed successfully.\n";
    return 0;
}
