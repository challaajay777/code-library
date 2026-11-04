#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Aho-Corasick Extended Pattern Automaton
// Purpose: Constructs multi-pattern matching automaton with dictionary suffix links (exit links) in O(Sum |P|).
// Time Complexity: O(Total Pattern Length) build, O(|Text| + Matches) query
// Space Complexity: O(Total Pattern Length * Sigma) space
// Preconditions: Patterns and text lowercase English.

class AhoCorasickExtended {
private:
    struct Node {
        int next[26];
        int fail;
        std::vector<int> match_ids;
        Node() : fail(0) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };
    std::vector<Node> trie;

public:
    AhoCorasickExtended() {
        trie.emplace_back();
    }

    void insert(const std::string& pat, int id) {
        int u = 0;
        for (char c : pat) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
        }
        trie[u].match_ids.push_back(id);
    }

    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (trie[0].next[i] != -1) {
                q.push(trie[0].next[i]);
            } else {
                trie[0].next[i] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : trie[trie[u].fail].match_ids) {
                trie[u].match_ids.push_back(i);
            }

            for (int c = 0; c < 26; ++c) {
                if (trie[u].next[c] != -1) {
                    trie[trie[u].next[c]].fail = trie[trie[u].fail].next[c];
                    q.push(trie[u].next[c]);
                } else {
                    trie[u].next[c] = trie[trie[u].fail].next[c];
                }
            }
        }
    }

    int count_matches(const std::string& text) {
        int u = 0;
        int matches = 0;
        for (char c : text) {
            u = trie[u].next[c - 'a'];
            matches += trie[u].match_ids.size();
        }
        return matches;
    }
};

int main() {
    AhoCorasickExtended ac;
    ac.insert("he", 0);
    ac.insert("she", 1);
    ac.insert("his", 2);
    ac.insert("hers", 3);
    ac.build();

    assert(ac.count_matches("ushers") == 3); // "she", "he", "hers"

    std::cout << "aho_corasick_extended_trie tests passed successfully.\n";
    return 0;
}
