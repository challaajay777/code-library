// Algorithm: K-th Lexicographical Substring via Suffix Automaton
// Purpose: Finds the k-th lexicographically smallest distinct substring using a DAG DP on Suffix Automaton states.
// Time Complexity: O(N * Sigma) to build, O(|result|) per query
// Space Complexity: O(N * Sigma)
// Preconditions: String contains lowercase Latin letters, 1 <= k <= total distinct substrings.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct SAMKth {
    struct State {
        int len, link;
        int next[26];
        long long paths; // number of distinct paths starting from this state
        State() : len(0), link(-1), paths(0) {
            std::fill(next, next + 26, -1);
        }
    };
    std::vector<State> st;
    int sz, last;

    SAMKth(int maxlen = 1000) {
        st.resize(2 * maxlen);
        st[0].len = 0;
        st[0].link = -1;
        sz = 1;
        last = 0;
    }

    void extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        int ch = c - 'a';
        while (p != -1 && st[p].next[ch] == -1) {
            st[p].next[ch] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[ch];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                for (int i = 0; i < 26; ++i) st[clone].next[i] = st[q].next[i];
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[ch] == q) {
                    st[p].next[ch] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    void prepare() {
        std::vector<int> order(sz);
        for (int i = 0; i < sz; ++i) order[i] = i;
        std::sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (int u : order) {
            st[u].paths = 1; // non-empty paths ending here or continuing
            for (int c = 0; c < 26; ++c) {
                if (st[u].next[c] != -1) {
                    st[u].paths += st[st[u].next[c]].paths;
                }
            }
        }
    }

    std::string kth_substring(long long k) {
        if (k > st[0].paths - 1) return "";
        std::string res;
        int cur = 0;
        while (k > 0) {
            for (int c = 0; c < 26; ++c) {
                int nxt = st[cur].next[c];
                if (nxt != -1) {
                    if (k <= st[nxt].paths) {
                        res.push_back((char)('a' + c));
                        k -= 1; // the transition character itself can form a substring
                        cur = nxt;
                        break;
                    } else {
                        k -= st[nxt].paths;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    std::string s = "aab";
    SAMKth sam(s.size());
    for (char c : s) sam.extend(c);
    sam.prepare();

    // Distinct substrings of "aab" are: "a", "aa", "aab", "ab", "b"
    assert(sam.kth_substring(1) == "a");
    assert(sam.kth_substring(2) == "aa");
    assert(sam.kth_substring(3) == "aab");
    assert(sam.kth_substring(4) == "ab");
    assert(sam.kth_substring(5) == "b");

    return 0;
}
