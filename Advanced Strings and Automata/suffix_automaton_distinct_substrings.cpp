// Algorithm: Count and Total Length of Distinct Substrings via SAM
// Purpose: Calculates both the number of distinct substrings and the sum of their lengths.
// Time Complexity: O(N * Sigma)
// Space Complexity: O(N * Sigma)
// Preconditions: String consisting of lowercase English letters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct DistinctSubstringsSAM {
    struct State {
        int len, link;
        int next[26];
        State() : len(0), link(-1) {
            std::fill(next, next + 26, -1);
        }
    };
    std::vector<State> st;
    int sz, last;

    DistinctSubstringsSAM(int maxlen = 1000) {
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

    long long count_distinct() {
        long long ans = 0;
        for (int i = 1; i < sz; ++i) {
            ans += st[i].len - st[st[i].link].len;
        }
        return ans;
    }

    long long sum_of_lengths() {
        long long ans = 0;
        for (int i = 1; i < sz; ++i) {
            long long l_max = st[i].len;
            long long l_min = st[st[i].link].len + 1;
            ans += (l_max + l_min) * (l_max - l_min + 1) / 2;
        }
        return ans;
    }
};

int main() {
    std::string s = "aba";
    DistinctSubstringsSAM sam(s.size());
    for (char c : s) sam.extend(c);

    // Substrings: "a", "b", "ab", "ba", "aba" -> 5 distinct
    assert(sam.count_distinct() == 5);
    // Lengths: 1 + 1 + 2 + 2 + 3 = 9
    assert(sam.sum_of_lengths() == 9);

    return 0;
}
