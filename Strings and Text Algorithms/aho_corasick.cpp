// Algorithm: Aho-Corasick Automaton
// Supports: Multi-pattern dictionary string matching, suffix links, occurrences count
// Indexing: Lowercase latin characters 'a'..'z'
// Complexity: O(total_pattern_length) construction, O(|text| + matches) search, O(states * ALPHABET) memory
// Preconditions: Patterns and text contain characters 'a'..'z'

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct AhoCorasick {
    static constexpr int ALPHABET = 26;

    struct Node {
        int next_node[ALPHABET];
        int fail = 0;
        vector<int> pattern_indices; // IDs of patterns that end here

        Node() {
            fill(begin(next_node), end(next_node), -1);
        }
    };

    vector<Node> nodes;
    int pattern_count = 0;

    AhoCorasick() {
        nodes.push_back(Node());
    }

    int insert(const string& p) {
        int u = 0;
        for (char c : p) {
            int d = c - 'a';
            assert(0 <= d && d < ALPHABET);
            if (nodes[u].next_node[d] == -1) {
                nodes[u].next_node[d] = (int)nodes.size();
                nodes.push_back(Node());
            }
            u = nodes[u].next_node[d];
        }
        int id = pattern_count++;
        nodes[u].pattern_indices.push_back(id);
        return id;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHABET; ++c) {
            if (nodes[0].next_node[c] != -1) {
                q.push(nodes[0].next_node[c]);
            } else {
                nodes[0].next_node[c] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Suffix link / fail link points to longest proper suffix match
            for (int p_id : nodes[nodes[u].fail].pattern_indices) {
                nodes[u].pattern_indices.push_back(p_id);
            }

            for (int c = 0; c < ALPHABET; ++c) {
                if (nodes[u].next_node[c] != -1) {
                    int v = nodes[u].next_node[c];
                    nodes[v].fail = nodes[nodes[u].fail].next_node[c];
                    q.push(v);
                } else {
                    nodes[u].next_node[c] = nodes[nodes[u].fail].next_node[c];
                }
            }
        }
    }

    // Returns counts of occurrences in text for each pattern ID [0, pattern_count - 1]
    vector<int> count_occurrences(const string& text) const {
        vector<int> matches(pattern_count, 0);
        int u = 0;
        for (char c : text) {
            int d = c - 'a';
            u = nodes[u].next_node[d];
            for (int p_id : nodes[u].pattern_indices) {
                matches[p_id]++;
            }
        }
        return matches;
    }
};
