// Algorithm: Trie (Prefix Tree)
// Supports: Word insertion, exact search, prefix search, prefix count
// Indexing: Lowercase latin characters 'a'..'z'
// Complexity: O(|S|) per insertion/search, O(total_chars * ALPHABET) memory
// Preconditions: Strings contain characters 'a'..'z'

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Trie {
    static constexpr int ALPHABET_SIZE = 26;

    struct Node {
        int next_node[ALPHABET_SIZE];
        int words_ending_here = 0;
        int prefix_count = 0;

        Node() {
            fill(begin(next_node), end(next_node), -1);
        }
    };

    vector<Node> nodes;

    Trie() {
        nodes.push_back(Node());
    }

    void insert(const string& s) {
        int u = 0;
        nodes[u].prefix_count++;
        for (char c : s) {
            int d = c - 'a';
            assert(0 <= d && d < ALPHABET_SIZE);
            if (nodes[u].next_node[d] == -1) {
                nodes[u].next_node[d] = (int)nodes.size();
                nodes.push_back(Node());
            }
            u = nodes[u].next_node[d];
            nodes[u].prefix_count++;
        }
        nodes[u].words_ending_here++;
    }

    // Returns exact occurrences of string s in the trie
    int count_word(const string& s) const {
        int u = 0;
        for (char c : s) {
            int d = c - 'a';
            if (d < 0 || d >= ALPHABET_SIZE || nodes[u].next_node[d] == -1) {
                return 0;
            }
            u = nodes[u].next_node[d];
        }
        return nodes[u].words_ending_here;
    }

    // Returns number of words in the trie having prefix p
    int count_prefix(const string& p) const {
        int u = 0;
        for (char c : p) {
            int d = c - 'a';
            if (d < 0 || d >= ALPHABET_SIZE || nodes[u].next_node[d] == -1) {
                return 0;
            }
            u = nodes[u].next_node[d];
        }
        return nodes[u].prefix_count;
    }
};
