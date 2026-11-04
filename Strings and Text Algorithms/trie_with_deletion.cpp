#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Trie with Dynamic Deletion
// Purpose: Prefix tree supporting dynamic word insertion, search, and memory-safe deletion.
// Time Complexity: O(|word|) per operation
// Space Complexity: O(N * Sigma) space
// Preconditions: Lowercase English letters.

class DeletableTrie {
private:
    struct Node {
        int next[26];
        int count;
        int ends_here;
        Node() : count(0), ends_here(0) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };
    std::vector<Node> trie;

public:
    DeletableTrie() {
        trie.emplace_back();
    }

    void insert(const std::string& word) {
        int u = 0;
        trie[u].count++;
        for (char c : word) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
            trie[u].count++;
        }
        trie[u].ends_here++;
    }

    bool search(const std::string& word) const {
        int u = 0;
        for (char c : word) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) return false;
            u = trie[u].next[b];
        }
        return trie[u].ends_here > 0;
    }

    void erase(const std::string& word) {
        if (!search(word)) return;
        int u = 0;
        trie[u].count--;
        for (char c : word) {
            u = trie[u].next[c - 'a'];
            trie[u].count--;
        }
        trie[u].ends_here--;
    }
};

int main() {
    DeletableTrie t;
    t.insert("apple");
    assert(t.search("apple") == true);

    t.erase("apple");
    assert(t.search("apple") == false);

    std::cout << "trie_with_deletion tests passed successfully.\n";
    return 0;
}
