// Algorithm: Generalized Suffix Automaton for Trie / Set of Strings
// Purpose: Builds a unified suffix automaton representing multiple strings efficiently.
// Time Complexity: O(Sigma * sum(|Si|))
// Space Complexity: O(Sigma * sum(|Si|))
// Preconditions: Collection of strings over lowercase Latin characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct GeneralizedSAM {
    struct State {
        int len, link;
        int next[26];
        State() : len(0), link(-1) {
            std::fill(next, next + 26, -1);
        }
    };
    std::vector<State> st;
    int sz;

    GeneralizedSAM(int maxlen = 1000) {
        st.resize(2 * maxlen);
        st[0].len = 0;
        st[0].link = -1;
        sz = 1;
    }

    int insert(char c, int last) {
        int ch = c - 'a';
        if (st[last].next[ch] != -1) {
            int q = st[last].next[ch];
            if (st[last].len + 1 == st[q].len) {
                return q;
            }
            int clone = sz++;
            st[clone].len = st[last].len + 1;
            for (int i = 0; i < 26; ++i) st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            while (last != -1 && st[last].next[ch] == q) {
                st[last].next[ch] = clone;
                last = st[last].link;
            }
            st[q].link = clone;
            return clone;
        }

        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
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
        return cur;
    }

    void add_string(const std::string& s) {
        int cur = 0;
        for (char c : s) {
            cur = insert(c, cur);
        }
    }

    bool contains(const std::string& pat) {
        int cur = 0;
        for (char c : pat) {
            int ch = c - 'a';
            if (st[cur].next[ch] == -1) return false;
            cur = st[cur].next[ch];
        }
        return true;
    }
};

int main() {
    GeneralizedSAM gsam(100);
    gsam.add_string("apple");
    gsam.add_string("applet");
    gsam.add_string("apply");

    assert(gsam.contains("apple"));
    assert(gsam.contains("let"));
    assert(gsam.contains("ply"));
    assert(gsam.contains("pp"));
    assert(!gsam.contains("banana"));

    return 0;
}
