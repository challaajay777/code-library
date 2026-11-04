#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Suffix Automaton (Basic State Construction)
// Purpose: Constructs the minimal deterministic automaton recognizing all suffixes of string S in O(N) time and space.
// Time Complexity: O(N) time
// Space Complexity: O(N * Sigma) space
// Preconditions: String of lowercase English letters.

class BasicSuffixAutomaton {
private:
    struct State {
        int len, link;
        int next[26];
        State(int l = 0, int lnk = -1) : len(l), link(lnk) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };

    std::vector<State> st;
    int last;

public:
    BasicSuffixAutomaton() {
        st.emplace_back(0, -1);
        last = 0;
    }

    void extend(char c) {
        int cur = st.size();
        st.emplace_back(st[last].len + 1, -1);
        int ch = c - 'a';
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
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[ch] == q) {
                    st[p].next[ch] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    bool contains_substring(const std::string& pat) const {
        int u = 0;
        for (char c : pat) {
            int ch = c - 'a';
            if (st[u].next[ch] == -1) return false;
            u = st[u].next[ch];
        }
        return true;
    }
};

int main() {
    BasicSuffixAutomaton sam;
    for (char c : std::string("banana")) {
        sam.extend(c);
    }
    assert(sam.contains_substring("nan") == true);
    assert(sam.contains_substring("ana") == true);
    assert(sam.contains_substring("apple") == false);

    std::cout << "suffix_automaton_basic tests passed successfully.\n";
    return 0;
}
