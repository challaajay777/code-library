// Algorithm: Aho-Corasick DP for Forbidden Words
// Purpose: Counts the number of valid words of length L avoiding a dictionary of forbidden patterns.
// Time Complexity: O(L * N * Sigma)
// Space Complexity: O(N * Sigma)
// Preconditions: Dictionary patterns over lowercase Latin letters, length L >= 1.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

struct AhoCorasickDP {
    static const int MOD = 1e9 + 7;
    struct Node {
        int next[26];
        int link;
        bool is_bad;
        Node() : link(0), is_bad(false) {
            for (int i = 0; i < 26; ++i) next[i] = 0;
        }
    };

    std::vector<Node> tree;

    AhoCorasickDP() {
        tree.emplace_back(); // root at 0
    }

    void insert(const std::string& pat) {
        int u = 0;
        for (char c : pat) {
            int ch = c - 'a';
            if (!tree[u].next[ch]) {
                tree[u].next[ch] = tree.size();
                tree.emplace_back();
            }
            u = tree[u].next[ch];
        }
        tree[u].is_bad = true;
    }

    void build() {
        std::queue<int> q;
        for (int c = 0; c < 26; ++c) {
            if (tree[0].next[c]) {
                q.push(tree[0].next[c]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            tree[u].is_bad |= tree[tree[u].link].is_bad;
            for (int c = 0; c < 26; ++c) {
                if (tree[u].next[c]) {
                    tree[tree[u].next[c]].link = tree[tree[u].link].next[c];
                    q.push(tree[u].next[c]);
                } else {
                    tree[u].next[c] = tree[tree[u].link].next[c];
                }
            }
        }
    }

    int count_valid_strings(int L, int alphabet_size = 26) {
        int n = tree.size();
        std::vector<int> dp(n, 0);
        dp[0] = 1;
        for (int step = 0; step < L; ++step) {
            std::vector<int> next_dp(n, 0);
            for (int u = 0; u < n; ++u) {
                if (dp[u] == 0) continue;
                for (int c = 0; c < alphabet_size; ++c) {
                    int v = tree[u].next[c];
                    if (!tree[v].is_bad) {
                        next_dp[v] = (next_dp[v] + dp[u]) % MOD;
                    }
                }
            }
            dp = next_dp;
        }
        long long total = 0;
        for (int u = 0; u < n; ++u) {
            total = (total + dp[u]) % MOD;
        }
        return total;
    }
};

int main() {
    AhoCorasickDP ac;
    ac.insert("ab");
    ac.build();

    // Alphabet of size 2 ('a', 'b'), length 3
    // Total binary strings of length 3: 8 ("aaa", "aab", "aba", "abb", "baa", "bab", "bba", "bbb")
    // Strings containing "ab": "aab", "aba", "abb", "bab" (4 strings)
    // Valid: 4 strings ("aaa", "baa", "bba", "bbb")
    int ans = ac.count_valid_strings(3, 2);
    assert(ans == 4);

    return 0;
}
