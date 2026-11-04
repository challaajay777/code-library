// Algorithm: Trie Auto-Complete with Frequency Ranking
// Purpose: Returns top-k most frequent words matching a prefix using Trie with stored best candidates.
// Time Complexity: O(PrefixLen + K)
// Space Complexity: O(N * WordLen)
// Preconditions: Lowercase ASCII strings.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

class AutoCompleteTrie {
    struct WordFreq {
        std::string word;
        int freq;
        bool operator<(const WordFreq& o) const {
            if (freq != o.freq) return freq > o.freq;
            return word < o.word;
        }
    };

    struct Node {
        int next[26];
        std::vector<WordFreq> top_words;
        Node() { std::fill(next, next + 26, -1); }
    };
    std::vector<Node> tree;

public:
    AutoCompleteTrie() { tree.emplace_back(); }

    void insert(const std::string& s, int freq) {
        int cur = 0;
        WordFreq wf{s, freq};
        for (char c : s) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) {
                tree[cur].next[ch] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[ch];
            tree[cur].top_words.push_back(wf);
            std::sort(tree[cur].top_words.begin(), tree[cur].top_words.end());
            if (tree[cur].top_words.size() > 3) tree[cur].top_words.pop_back();
        }
    }

    std::vector<std::string> query_top(const std::string& prefix) {
        int cur = 0;
        for (char c : prefix) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) return {};
            cur = tree[cur].next[ch];
        }
        std::vector<std::string> res;
        for (const auto& wf : tree[cur].top_words) res.push_back(wf.word);
        return res;
    }
};

int main() {
    AutoCompleteTrie act;
    act.insert("apple", 10);
    act.insert("app", 20);
    act.insert("application", 5);

    auto top = act.query_top("app");
    assert(top.size() == 3);
    assert(top[0] == "app"); // freq 20
    assert(top[1] == "apple"); // freq 10
    return 0;
}
