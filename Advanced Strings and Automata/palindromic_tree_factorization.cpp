// Algorithm: Minimum Palindrome Factorization via Palindromic Tree
// Purpose: Finds the minimum number of palindromic cuts to partition a string using Eertree series links.
// Time Complexity: O(N log N)
// Space Complexity: O(N * Sigma)
// Preconditions: String of lowercase characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct EertreeFactorization {
    static const int INF = 1e9;
    struct Node {
        int len, link;
        int next[26];
        int diff, slink;
        Node(int l = 0, int p = 0) : len(l), link(p), diff(0), slink(0) {
            std::fill(next, next + 26, 0);
        }
    };

    std::vector<Node> tree;
    std::string s;
    int last, sz;
    std::vector<int> dp, g;

    EertreeFactorization(const std::string& str) : s(str) {
        int n = str.size();
        tree.resize(n + 3);
        dp.assign(n + 1, INF);
        g.assign(n + 3, INF);
        dp[0] = 0;

        tree[1] = Node(-1, 1);
        tree[2] = Node(0, 1);
        sz = 2;
        last = 2;
    }

    int get_link(int v, int i) {
        while (i - 1 - tree[v].len < 0 || s[i - 1 - tree[v].len] != s[i]) {
            v = tree[v].link;
        }
        return v;
    }

    int solve() {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            int cur = get_link(last, i);
            int ch = s[i] - 'a';
            if (!tree[cur].next[ch]) {
                int now = ++sz;
                tree[now] = Node(tree[cur].len + 2, 0);
                tree[now].link = tree[get_link(tree[cur].link, i)].next[ch];
                if (!tree[now].link) tree[now].link = 2;
                tree[cur].next[ch] = now;

                tree[now].diff = tree[now].len - tree[tree[now].link].len;
                if (tree[now].diff == tree[tree[now].link].diff) {
                    tree[now].slink = tree[tree[now].link].slink;
                } else {
                    tree[now].slink = tree[now].link;
                }
            }
            last = tree[cur].next[ch];

            for (int v = last; tree[v].len > 0; v = tree[v].slink) {
                g[v] = dp[i - (tree[tree[v].slink].len + tree[v].diff)];
                if (tree[v].diff == tree[tree[v].link].diff) {
                    g[v] = std::min(g[v], g[tree[v].link]);
                }
                dp[i + 1] = std::min(dp[i + 1], g[v] + 1);
            }
        }
        return dp[n];
    }
};

int main() {
    // "abacaba" -> palindrome itself -> 1
    EertreeFactorization ef1("abacaba");
    assert(ef1.solve() == 1);

    // "abac" -> "aba" + "c" -> 2
    EertreeFactorization ef2("abac");
    assert(ef2.solve() == 2);

    // "abcdef" -> 6 single letter palindromes
    EertreeFactorization ef3("abcdef");
    assert(ef3.solve() == 6);

    return 0;
}
