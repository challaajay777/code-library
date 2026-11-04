// Algorithm: Multiple String LCS via Suffix Automaton
// Purpose: Computes the longest common substring among k strings using SAM constructed on the first string.
// Time Complexity: O(N1 * Sigma + sum(Ni))
// Space Complexity: O(N1 * Sigma)
// Preconditions: At least one non-empty string, lowercase Latin alphabet.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct SAMMultiLCS {
    struct State {
        int len, link;
        int next[26];
        int max_len, min_len;
        State() : len(0), link(-1), max_len(0), min_len(0) {
            std::fill(next, next + 26, -1);
        }
    };
    std::vector<State> st;
    int sz, last;

    SAMMultiLCS(int maxlen = 1000) {
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

    void init_bounds() {
        for (int i = 0; i < sz; ++i) st[i].min_len = st[i].len;
    }

    void process_string(const std::string& s) {
        for (int i = 0; i < sz; ++i) st[i].max_len = 0;
        int cur = 0, cur_len = 0;
        for (char ch : s) {
            int c = ch - 'a';
            while (cur != 0 && st[cur].next[c] == -1) {
                cur = st[cur].link;
                cur_len = st[cur].len;
            }
            if (st[cur].next[c] != -1) {
                cur = st[cur].next[c];
                cur_len++;
            }
            st[cur].max_len = std::max(st[cur].max_len, cur_len);
        }

        std::vector<int> order(sz);
        for (int i = 0; i < sz; ++i) order[i] = i;
        std::sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });

        for (int u : order) {
            if (st[u].link != -1) {
                st[st[u].link].max_len = std::max(st[st[u].link].max_len, std::min(st[st[u].link].len, st[u].max_len));
            }
            st[u].min_len = std::min(st[u].min_len, st[u].max_len);
        }
    }

    int get_lcs_length() {
        int ans = 0;
        for (int i = 0; i < sz; ++i) {
            ans = std::max(ans, st[i].min_len);
        }
        return ans;
    }
};

int main() {
    std::vector<std::string> strings = {"abcde", "bcdef", "zabcdf"};
    SAMMultiLCS sam(strings[0].size());
    for (char c : strings[0]) sam.extend(c);
    sam.init_bounds();

    for (size_t i = 1; i < strings.size(); ++i) {
        sam.process_string(strings[i]);
    }

    assert(sam.get_lcs_length() == 3); // "bcd"
    return 0;
}
