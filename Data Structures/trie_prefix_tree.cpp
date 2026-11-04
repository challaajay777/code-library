// Algorithm: Prefix Trie with Prefix Search and Deletion
// Purpose: Standard string prefix tree supporting insert, full match, and prefix existence checks.
// Time Complexity: O(L) per operation
// Space Complexity: O(TotalChars * Sigma)
// Preconditions: Lowercase Latin characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class PrefixTrie {
    struct Node {
        int next[26];
        bool is_end = false;
        Node() { std::fill(next, next + 26, -1); }
    };
    std::vector<Node> tree;

public:
    PrefixTrie() { tree.emplace_back(); }

    void insert(const std::string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) {
                tree[cur].next[ch] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[ch];
        }
        tree[cur].is_end = true;
    }

    bool search(const std::string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) return false;
            cur = tree[cur].next[ch];
        }
        return tree[cur].is_end;
    }

    bool starts_with(const std::string& prefix) {
        int cur = 0;
        for (char c : prefix) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) return false;
            cur = tree[cur].next[ch];
        }
        return true;
    }
};

int main() {
    PrefixTrie trie;
    trie.insert("apple");
    assert(trie.search("apple"));
    assert(!trie.search("app"));
    assert(trie.starts_with("app"));
    return 0;
}
