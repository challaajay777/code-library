// Algorithm: Suffix Automaton (SAM)
// Supports: Linear time recognition of all suffixes, distinct substring counting, occurrences query
// Indexing: Lowercase latin characters 'a'..'z'
// Complexity: O(n) construction time, O(n * ALPHABET) memory
// Preconditions: Characters in 'a'..'z'

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct SuffixAutomaton {
    static constexpr int ALPHABET = 26;

    struct State {
        int len = 0;
        int link = -1;
        int next_state[ALPHABET];
        bool is_clone = false;

        State() {
            fill(begin(next_state), end(next_state), -1);
        }
    };

    vector<State> st;
    int last = 0;

    explicit SuffixAutomaton(int max_len = 1000) {
        st.reserve(2 * max_len);
        st.push_back(State()); // root state 0
        st[0].len = 0;
        st[0].link = -1;
        last = 0;
    }

    void extend(char c) {
        int d = c - 'a';
        assert(0 <= d && d < ALPHABET);
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && st[p].next_state[d] == -1) {
            st[p].next_state[d] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next_state[d];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].is_clone = true;

                while (p != -1 && st[p].next_state[d] == q) {
                    st[p].next_state[d] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Counts total number of distinct substrings of the string
    long long count_distinct_substrings() const {
        long long total = 0;
        for (size_t i = 1; i < st.size(); ++i) {
            total += st[i].len - st[st[i].link].len;
        }
        return total;
    }
};
