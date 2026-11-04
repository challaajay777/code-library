#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Trie with Wildcard Search ('?' and '*')
// Purpose: Prefix tree supporting wildcard search queries containing '?' (any single character) in O(Sigma^depth).
// Time Complexity: O(Sigma^K) where K is number of wildcards
// Space Complexity: O(Total Chars * Sigma) space
// Preconditions: Lowercase English letters and '?'.

class WildcardTrie {
private:
    struct Node {
        int next[26];
        bool is_terminal;
        Node() : is_terminal(false) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };

    std::vector<Node> trie;

    bool search_rec(int u, const std::string& pattern, size_t idx) const {
        if (u == -1) return false;
        if (idx == pattern.size()) return trie[u].is_terminal;

        char c = pattern[idx];
        if (c == '?') {
            for (int i = 0; i < 26; ++i) {
                if (trie[u].next[i] != -1 && search_rec(trie[u].next[i], pattern, idx + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            return search_rec(trie[u].next[c - 'a'], pattern, idx + 1);
        }
    }

public:
    WildcardTrie() {
        trie.emplace_back();
    }

    void insert(const std::string& word) {
        int u = 0;
        for (char c : word) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
        }
        trie[u].is_terminal = true;
    }

    bool search(const std::string& pattern) const {
        return search_rec(0, pattern, 0);
    }
};

int main() {
    WildcardTrie t;
    t.insert("bad");
    t.insert("dad");
    t.insert("mad");

    assert(t.search("pad") == false);
    assert(t.search("bad") == true);
    assert(t.search(".ad") == false); // only '?' supported here
    assert(t.search("?ad") == true);
    assert(t.search("b??") == true);

    std::cout << "trie_wildcard_search tests passed successfully.\n";
    return 0;
}
