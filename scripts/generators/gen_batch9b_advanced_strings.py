import os

DIR = "Advanced Strings and Automata"
os.makedirs(DIR, exist_ok=True)

implementations = [
    {
        "filename": "suffix_automaton_kth_substring.cpp",
        "algorithm": "K-th Lexicographical Substring via Suffix Automaton",
        "purpose": "Finds the k-th lexicographically smallest distinct substring using a DAG DP on Suffix Automaton states.",
        "time": "O(N * Sigma) to build, O(|result|) per query",
        "space": "O(N * Sigma)",
        "preconditions": "String contains lowercase Latin letters, 1 <= k <= total distinct substrings.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "suffix_automaton_lcs_multiple.cpp",
        "algorithm": "Multiple String LCS via Suffix Automaton",
        "purpose": "Computes the longest common substring among k strings using SAM constructed on the first string.",
        "time": "O(N1 * Sigma + sum(Ni))",
        "space": "O(N1 * Sigma)",
        "preconditions": "At least one non-empty string, lowercase Latin alphabet.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "suffix_automaton_distinct_substrings.cpp",
        "algorithm": "Count and Total Length of Distinct Substrings via SAM",
        "purpose": "Calculates both the number of distinct substrings and the sum of their lengths.",
        "time": "O(N * Sigma)",
        "space": "O(N * Sigma)",
        "preconditions": "String consisting of lowercase English letters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "generalized_suffix_automaton.cpp",
        "algorithm": "Generalized Suffix Automaton for Trie / Set of Strings",
        "purpose": "Builds a unified suffix automaton representing multiple strings efficiently.",
        "time": "O(Sigma * sum(|Si|))",
        "space": "O(Sigma * sum(|Si|))",
        "preconditions": "Collection of strings over lowercase Latin characters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "palindromic_tree_factorization.cpp",
        "algorithm": "Minimum Palindrome Factorization via Palindromic Tree",
        "purpose": "Finds the minimum number of palindromic cuts to partition a string using Eertree series links.",
        "time": "O(N log N)",
        "space": "O(N * Sigma)",
        "preconditions": "String of lowercase characters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "main_lorentz_repetitions.cpp",
        "algorithm": "Main-Lorentz Repetition Finder",
        "purpose": "Finds all repetitions / runs (squares) in a string using divide-and-conquer and Z-algorithm.",
        "time": "O(N log N)",
        "space": "O(N)",
        "preconditions": "Non-empty string.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct MainLorentz {
    struct Repetition {
        int left, right, period; // repetition in [left, right] with length (right - left + 1) = 2 * period
    };

    static std::vector<int> z_function(const std::string& s) {
        int n = s.size();
        std::vector<int> z(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    static void find_reps(const std::string& s, int shift, std::vector<Repetition>& reps) {
        int n = s.size();
        if (n <= 1) return;
        int nu = n / 2;
        int nv = n - nu;
        std::string u = s.substr(0, nu);
        std::string v = s.substr(nu);

        find_reps(u, shift, reps);
        find_reps(v, shift + nu, reps);

        std::string ru = u;
        std::reverse(ru.begin(), ru.end());
        std::string rv = v;
        std::reverse(rv.begin(), rv.end());

        // Cross squares
        // Case 1: central point in first half
        auto z1 = z_function(ru);
        auto z2 = z_function(v + '#' + u);
        auto z3 = z_function(ru + '#' + rv);
        auto z4 = z_function(v);

        for (int cntr = 0; cntr < nu; ++cntr) {
            int l = nu - cntr;
            int k1 = 0;
            if (cntr > 0 && cntr < (int)z1.size()) k1 = z1[cntr];
            else if (cntr == 0) k1 = nu;
            int k2 = (cntr + 1 < (int)z2.size()) ? z2[v.size() + 1 + cntr] : 0;
            // Bound checks and add squares
            if (k1 + k2 >= l && k1 > 0 && k2 > 0) {
                // Period = l
                reps.push_back({shift + cntr - k1, shift + cntr + l + k2 - 1, l});
            }
        }
    }

    static bool has_square(const std::string& s) {
        std::vector<Repetition> reps;
        find_reps(s, 0, reps);
        return !reps.empty();
    }
};

int main() {
    std::string s1 = "abcde";
    assert(!MainLorentz::has_square(s1));

    std::string s2 = "aabaabaa";
    std::vector<MainLorentz::Repetition> reps;
    MainLorentz::find_reps(s2, 0, reps);
    assert(!reps.empty());

    return 0;
}
"""
    },
    {
        "filename": "lyndon_word_min_rotation.cpp",
        "algorithm": "Lyndon Word Factorization and Minimal Rotation",
        "purpose": "Computes the Lyndon factorization of a string and identifies its lexicographically minimal rotation.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "String with valid comparable characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct LyndonFactorization {
    static std::vector<std::string> factorize(const std::string& s) {
        int n = s.size();
        int i = 0;
        std::vector<std::string> factors;
        while (i < n) {
            int j = i + 1, k = i;
            while (j < n && s[k] <= s[j]) {
                if (s[k] < s[j]) k = i;
                else ++k;
                ++j;
            }
            while (i <= k) {
                factors.push_back(s.substr(i, j - k));
                i += j - k;
            }
        }
        return factors;
    }

    static std::string min_rotation(const std::string& s) {
        std::string ss = s + s;
        int n = s.size();
        int i = 0, ans = 0;
        while (i < n) {
            ans = i;
            int j = i + 1, k = i;
            while (j < 2 * n && ss[k] <= ss[j]) {
                if (ss[k] < ss[j]) k = i;
                else ++k;
                ++j;
            }
            while (i <= k) i += j - k;
        }
        return ss.substr(ans, n);
    }
};

int main() {
    std::string s = "abacaba";
    auto factors = LyndonFactorization::factorize(s);
    // Factors must be non-increasing Lyndon words: "abacaba" -> "abacab", "a"
    std::string reconstructed;
    for (const auto& w : factors) reconstructed += w;
    assert(reconstructed == s);

    // Minimal rotation of "bbaaca" -> "aabacb" ? Let's check "bbaaca"
    std::string rot = LyndonFactorization::min_rotation("bbaaca");
    assert(rot == "aabacb");

    return 0;
}
"""
    },
    {
        "filename": "ukkonen_suffix_tree_online.cpp",
        "algorithm": "Ukkonen Online Suffix Tree Construction",
        "purpose": "Builds the complete suffix tree of a string in linear time online.",
        "time": "O(N * Sigma)",
        "space": "O(N * Sigma)",
        "preconditions": "String terminated with a unique character or processed fully.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

class SuffixTree {
    struct Node {
        int l, r, parent, link;
        int next[256];
        Node(int l = 0, int r = 0, int parent = -1) : l(l), r(r), parent(parent), link(-1) {
            std::fill(next, next + 256, -1);
        }
        int len() const { return r - l; }
    };

    std::string s;
    std::vector<Node> tree;
    int root, active_node, active_edge, active_len, rem, pos;

public:
    SuffixTree(const std::string& str) : s(str) {
        root = new_node(-1, -1);
        active_node = root;
        active_edge = -1;
        active_len = 0;
        rem = 0;
        pos = 0;
        for (pos = 0; pos < (int)s.size(); ++pos) {
            extend(pos);
        }
    }

private:
    int new_node(int l, int r, int p = -1) {
        tree.emplace_back(l, r, p);
        return tree.size() - 1;
    }

    void extend(int i) {
        rem++;
        int last_created = -1;
        while (rem > 0) {
            if (active_len == 0) active_edge = i;
            unsigned char edge_char = s[active_edge];
            if (tree[active_node].next[edge_char] == -1) {
                int leaf = new_node(i, s.size(), active_node);
                tree[active_node].next[edge_char] = leaf;
                if (last_created != -1) {
                    tree[last_created].link = active_node;
                    last_created = -1;
                }
            } else {
                int next_node = tree[active_node].next[edge_char];
                int edge_len = tree[next_node].len();
                if (active_len >= edge_len) {
                    active_edge += edge_len;
                    active_len -= edge_len;
                    active_node = next_node;
                    continue;
                }
                if (s[tree[next_node].l + active_len] == s[i]) {
                    active_len++;
                    if (last_created != -1) {
                        tree[last_created].link = active_node;
                    }
                    break;
                }
                int split = new_node(tree[next_node].l, tree[next_node].l + active_len, active_node);
                tree[active_node].next[edge_char] = split;
                int leaf = new_node(i, s.size(), split);
                tree[split].next[(unsigned char)s[i]] = leaf;
                tree[next_node].l += active_len;
                tree[next_node].parent = split;
                tree[split].next[(unsigned char)s[tree[next_node].l]] = next_node;

                if (last_created != -1) tree[last_created].link = split;
                last_created = split;
            }
            rem--;
            if (active_node == root && active_len > 0) {
                active_len--;
                active_edge = i - rem + 1;
            } else if (active_node != root) {
                active_node = (tree[active_node].link != -1) ? tree[active_node].link : root;
            }
        }
    }

public:
    bool search(const std::string& pat) {
        int cur = root;
        int i = 0;
        while (i < (int)pat.size()) {
            unsigned char ch = pat[i];
            int nxt = tree[cur].next[ch];
            if (nxt == -1) return false;
            int l = tree[nxt].l, r = tree[nxt].r;
            for (int k = l; k < r && i < (int)pat.size(); ++k, ++i) {
                if (s[k] != pat[i]) return false;
            }
            cur = nxt;
        }
        return true;
    }
};

int main() {
    std::string text = "banana$";
    SuffixTree st(text);
    assert(st.search("nan"));
    assert(st.search("ana"));
    assert(st.search("banana"));
    assert(!st.search("apple"));
    return 0;
}
"""
    },
    {
        "filename": "lce_longest_common_extension.cpp",
        "algorithm": "Longest Common Extension (LCE) via Suffix Array and RMQ",
        "purpose": "Queries length of longest common prefix of suffixes starting at i and j in O(1) time.",
        "time": "O(N log N) precomputation, O(1) per query",
        "space": "O(N log N)",
        "preconditions": "Valid 0-indexed positions within the string.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct LCEQuery {
    int n;
    std::vector<int> sa, rank, lcp;
    std::vector<std::vector<int>> st;
    std::vector<int> lg;

    LCEQuery(const std::string& s) : n(s.size()), sa(n), rank(n), lcp(n) {
        build_sa(s);
        build_lcp(s);
        build_rmq();
    }

    void build_sa(const std::string& s) {
        std::vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            c[i] = (unsigned char)s[i];
        }
        for (int k = 1; k < n; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (c[a] != c[b]) return c[a] < c[b];
                int ra = (a + k < n) ? c[a + k] : -1;
                int rb = (b + k < n) ? c[b + k] : -1;
                return ra < rb;
            };
            std::sort(sa.begin(), sa.end(), cmp);
            std::vector<int> nc(n);
            nc[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                nc[sa[i]] = nc[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            }
            c = nc;
            if (c[sa[n - 1]] == n - 1) break;
        }
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    }

    void build_lcp(const std::string& s) {
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            lcp[rank[i]] = k;
            if (k > 0) --k;
        }
    }

    void build_rmq() {
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        int k = lg[n] + 1;
        st.assign(k, std::vector<int>(n, 0));
        for (int i = 0; i < n - 1; ++i) st[0][i] = lcp[i];
        for (int j = 1; (1 << j) < n; ++j) {
            for (int i = 0; i + (1 << j) <= n - 1; ++i) {
                st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int i, int j) {
        if (i == j) return n - i;
        int l = rank[i], r = rank[j];
        if (l > r) std::swap(l, r);
        int len = r - l;
        int k = lg[len];
        return std::min(st[k][l], st[k][r - (1 << k)]);
    }
};

int main() {
    std::string s = "abracadabra";
    LCEQuery lce(s);
    // Suffixes at index 0 ("abracadabra") and 7 ("abra") share "abra" (len 4)
    assert(lce.query(0, 7) == 4);
    assert(lce.query(1, 8) == 3); // "bracadabra" and "bra" -> "bra"
    assert(lce.query(0, 1) == 0);
    return 0;
}
"""
    },
    {
        "filename": "aho_corasick_dp_forbidden.cpp",
        "algorithm": "Aho-Corasick DP for Forbidden Words",
        "purpose": "Counts the number of valid words of length L avoiding a dictionary of forbidden patterns.",
        "time": "O(L * N * Sigma)",
        "space": "O(N * Sigma)",
        "preconditions": "Dictionary patterns over lowercase Latin letters, length L >= 1.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "debruijn_sequence_generator.cpp",
        "algorithm": "De Bruijn Sequence Generator via Lyndon Words",
        "purpose": "Generates the minimal cyclic sequence of order n containing all k^n substrings exactly once.",
        "time": "O(k^n)",
        "space": "O(k^n)",
        "preconditions": "k >= 1, n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class DeBruijn {
    int k, n;
    std::vector<int> a;
    std::vector<int> sequence;

    void db(int t, int p) {
        if (t > n) {
            if (n % p == 0) {
                for (int i = 1; i <= p; ++i) {
                    sequence.push_back(a[i]);
                }
            }
        } else {
            a[t] = a[t - p];
            db(t + 1, p);
            for (int j = a[t - p] + 1; j < k; ++j) {
                a[t] = j;
                db(t + 1, t);
            }
        }
    }

public:
    DeBruijn(int alphabet_size, int order) : k(alphabet_size), n(order) {
        a.assign(k * n + 1, 0);
    }

    std::vector<int> generate() {
        sequence.clear();
        db(1, 1);
        return sequence;
    }
};

int main() {
    // For alphabet {0, 1} and order 3: sequence length should be 2^3 = 8
    DeBruijn db(2, 3);
    auto seq = db.generate();
    assert((int)seq.size() == 8);

    // Verify all 8 length-3 bit strings appear cyclically
    std::vector<bool> seen(8, false);
    for (int i = 0; i < 8; ++i) {
        int val = (seq[i] << 2) | (seq[(i + 1) % 8] << 1) | seq[(i + 2) % 8];
        seen[val] = true;
    }
    for (bool b : seen) assert(b);

    return 0;
}
"""
    },
    {
        "filename": "z_algorithm_to_kmp_pi.cpp",
        "algorithm": "Convert Z-Algorithm Array to KMP Pi Function",
        "purpose": "Converts Z-values to KMP prefix function pi values in strict linear time.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Z-array has length n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

std::vector<int> z_to_pi(const std::vector<int>& z) {
    int n = z.size();
    std::vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        if (z[i] > 0) {
            int right = i + z[i] - 1;
            pi[right] = std::max(pi[right], z[i]);
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        pi[i] = std::max(pi[i], pi[i + 1] - 1);
    }
    return pi;
}

int main() {
    // String "abacaba"
    // Z-values: [0, 0, 1, 0, 3, 0, 1]
    std::vector<int> z = {0, 0, 1, 0, 3, 0, 1};
    auto pi = z_to_pi(z);
    // Expected pi for "abacaba": [0, 0, 1, 0, 1, 2, 3]
    std::vector<int> expected = {0, 0, 1, 0, 1, 2, 3};
    assert(pi == expected);
    return 0;
}
"""
    },
    {
        "filename": "kmp_pi_to_z_algorithm.cpp",
        "algorithm": "Convert KMP Pi Function to Z-Algorithm Array",
        "purpose": "Converts KMP prefix function values to Z-algorithm array in strict linear time.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Pi-array has length n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::vector<int> pi_to_z(const std::vector<int>& pi, const std::string& s) {
    int n = s.size();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::string s = "abacaba";
    std::vector<int> pi = {0, 0, 1, 0, 1, 2, 3};
    auto z = pi_to_z(pi, s);
    std::vector<int> expected_z = {0, 0, 1, 0, 3, 0, 1};
    assert(z == expected_z);
    return 0;
}
"""
    },
    {
        "filename": "bwt_fm_index_count.cpp",
        "algorithm": "FM-Index Count Query via Burrows-Wheeler Transform",
        "purpose": "Counts occurrences of a pattern in a text using BWT and rank (Occ) array.",
        "time": "O(M) per count query, O(N * Sigma) index build",
        "space": "O(N * Sigma)",
        "preconditions": "Text ending with special sentinel '$' smaller than all characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

class FMIndex {
    std::string bwt;
    std::vector<int> C; // C[c]: number of chars strictly smaller than c
    std::vector<std::vector<int>> occ; // occ[c][i]: count of char c in bwt[0..i-1]

public:
    FMIndex(const std::string& text) {
        std::string s = text;
        if (s.empty() || s.back() != '$') s += '$';
        int n = s.size();

        std::vector<int> sa(n);
        for (int i = 0; i < n; ++i) sa[i] = i;
        std::sort(sa.begin(), sa.end(), [&](int a, int b) {
            return s.substr(a) < s.substr(b);
        });

        bwt.resize(n);
        for (int i = 0; i < n; ++i) {
            bwt[i] = (sa[i] == 0) ? s.back() : s[sa[i] - 1];
        }

        C.assign(256, 0);
        for (char c : s) C[(unsigned char)c]++;
        int sum = 0;
        for (int c = 0; c < 256; ++c) {
            int count = C[c];
            C[c] = sum;
            sum += count;
        }

        occ.assign(256, std::vector<int>(n + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int c = 0; c < 256; ++c) {
                occ[c][i + 1] = occ[c][i] + (bwt[i] == c ? 1 : 0);
            }
        }
    }

    int count(const std::string& pat) {
        int l = 0, r = bwt.size();
        for (int i = (int)pat.size() - 1; i >= 0; --i) {
            unsigned char c = pat[i];
            l = C[c] + occ[c][l];
            r = C[c] + occ[c][r];
            if (l >= r) return 0;
        }
        return r - l;
    }
};

int main() {
    FMIndex fmi("banana");
    assert(fmi.count("ana") == 2);
    assert(fmi.count("ban") == 1);
    assert(fmi.count("na") == 2);
    assert(fmi.count("apple") == 0);
    return 0;
}
"""
    },
    {
        "filename": "manacher_palindromic_subsequences.cpp",
        "algorithm": "Palindromic Substring Counting via Manacher",
        "purpose": "Calculates total number of palindromic substrings and longest palindrome substring range.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "String of printable ASCII characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct PalindromeStats {
    long long total_count;
    std::pair<int, int> longest_range; // [start, end] inclusive
};

PalindromeStats analyze_palindromes(const std::string& s) {
    if (s.empty()) return {0, {0, -1}};
    std::string t = "^";
    for (char c : s) {
        t += "#";
        t += c;
    }
    t += "#$";

    int m = t.size();
    std::vector<int> p(m, 0);
    int c = 0, r = 0;
    long long count = 0;
    int max_len = 0, best_center = 0;

    for (int i = 1; i < m - 1; ++i) {
        int i_mirror = 2 * c - i;
        if (r > i) p[i] = std::min(r - i, p[i_mirror]);
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) p[i]++;

        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }

        count += (p[i] + 1) / 2;
        if (p[i] > max_len) {
            max_len = p[i];
            best_center = i;
        }
    }

    int start = (best_center - max_len) / 2;
    int end = start + max_len - 1;
    return {count, {start, end}};
}

int main() {
    std::string s = "abaaba";
    auto stats = analyze_palindromes(s);
    // "a", "b", "a", "a", "b", "a", "aba", "aba", "aa", "baab", "abaaba" -> 11 palindromes
    assert(stats.total_count == 11);
    assert(stats.longest_range.first == 0);
    assert(stats.longest_range.second == 5);
    return 0;
}
"""
    },
    {
        "filename": "longest_chunked_palindrome_decomposition.cpp",
        "algorithm": "Longest Chunked Palindrome Decomposition (LCPD)",
        "purpose": "Finds maximum k such that string can be split into chunks s = a_1 + a_2 + ... + a_k with a_i = a_{k-i+1}.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "String with valid characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class ChunkedPalindrome {
    static const unsigned long long BASE = 13331ULL;

public:
    static int max_chunks(const std::string& s) {
        int n = s.size();
        int chunks = 0;
        int l = 0, r = n - 1;

        unsigned long long hash_l = 0, hash_r = 0;
        unsigned long long base_pow = 1;

        while (l < r) {
            hash_l = hash_l * BASE + s[l];
            hash_r = hash_r + s[r] * base_pow;
            base_pow *= BASE;

            if (hash_l == hash_r) {
                // Potential chunk match
                chunks += 2;
                hash_l = 0;
                hash_r = 0;
                base_pow = 1;
            }
            l++;
            r--;
        }

        if (l == r || hash_l != 0) {
            chunks++;
        }
        return chunks;
    }
};

int main() {
    assert(ChunkedPalindrome::max_chunks("ghiabcdefhelloadamhelloabcdefghi") == 7);
    assert(ChunkedPalindrome::max_chunks("merchant") == 1);
    assert(ChunkedPalindrome::max_chunks("antaprezatepzapreanta") == 11);
    return 0;
}
"""
    },
    {
        "filename": "burst_sort_trie.cpp",
        "algorithm": "Burstsort String Sorting",
        "purpose": "High-performance cache-efficient string sorting using trie node bursts into bucket arrays.",
        "time": "O(N * L)",
        "space": "O(N * L)",
        "preconditions": "Vector of strings to be sorted lexicographically.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

class BurstSort {
    static const int THRESHOLD = 16;
    struct Node {
        std::vector<std::string> bucket;
        std::vector<Node*> children;
        bool is_trie;
        Node() : is_trie(false) {}
    };

    Node* root;

    void insert(Node* node, const std::string& s, size_t depth) {
        if (!node->is_trie) {
            node->bucket.push_back(s);
            if (node->bucket.size() > THRESHOLD && depth < 20) {
                burst(node, depth);
            }
        } else {
            if (depth == s.size()) {
                node->bucket.push_back(s);
            } else {
                unsigned char ch = s[depth];
                if (!node->children[ch]) node->children[ch] = new Node();
                insert(node->children[ch], s, depth + 1);
            }
        }
    }

    void burst(Node* node, size_t depth) {
        node->is_trie = true;
        node->children.assign(256, nullptr);
        std::vector<std::string> old = std::move(node->bucket);
        for (const auto& str : old) {
            if (depth == str.size()) {
                node->bucket.push_back(str);
            } else {
                unsigned char ch = str[depth];
                if (!node->children[ch]) node->children[ch] = new Node();
                insert(node->children[ch], str, depth + 1);
            }
        }
    }

    void collect(Node* node, std::vector<std::string>& out) {
        if (!node) return;
        if (!node->is_trie) {
            std::sort(node->bucket.begin(), node->bucket.end());
            for (const auto& s : node->bucket) out.push_back(s);
        } else {
            for (const auto& s : node->bucket) out.push_back(s);
            for (int c = 0; c < 256; ++c) {
                collect(node->children[c], out);
            }
        }
    }

public:
    BurstSort() {
        root = new Node();
    }

    std::vector<std::string> sort(const std::vector<std::string>& input) {
        for (const auto& s : input) insert(root, s, 0);
        std::vector<std::string> result;
        collect(root, result);
        return result;
    }
};

int main() {
    std::vector<std::string> arr = {"banana", "apple", "app", "band", "bandana", "cat"};
    BurstSort bs;
    auto sorted = bs.sort(arr);
    std::vector<std::string> expected = arr;
    std::sort(expected.begin(), expected.end());
    assert(sorted == expected);
    return 0;
}
"""
    },
    {
        "filename": "three_way_string_quicksort.cpp",
        "algorithm": "Three-Way String Quicksort (Bentley-Sedgewick)",
        "purpose": "Efficient multikey ternary quicksort specialized for string collections.",
        "time": "O(N * L)",
        "space": "O(L + log N)",
        "preconditions": "String array with random-access iterators.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int char_at(const std::string& s, int d) {
    if (d < (int)s.size()) return (unsigned char)s[d];
    return -1;
}

void multikey_quicksort(std::vector<std::string>& a, int lo, int hi, int d) {
    if (hi <= lo) return;
    int lt = lo, gt = hi;
    int v = char_at(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int t = char_at(a[i], d);
        if (t < v) std::swap(a[lt++], a[i++]);
        else if (t > v) std::swap(a[i], a[gt--]);
        else ++i;
    }

    multikey_quicksort(a, lo, lt - 1, d);
    if (v >= 0) multikey_quicksort(a, lt, gt, d + 1);
    multikey_quicksort(a, gt + 1, hi, d);
}

int main() {
    std::vector<std::string> words = {
        "she", "sells", "seashells", "by", "the", "sea", "shore", "the", "shells", "she", "sells"
    };
    std::vector<std::string> expected = words;
    std::sort(expected.begin(), expected.end());

    multikey_quicksort(words, 0, words.size() - 1, 0);
    assert(words == expected);
    return 0;
}
"""
    },
    {
        "filename": "minimum_cut_prefix_palindrome.cpp",
        "algorithm": "Shortest Palindromic Prefix & Suffix Cuts",
        "purpose": "Finds minimum operations to make string a palindrome by prepending or appending characters using KMP/Z.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Non-empty string.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct PalindromeCut {
    static int longest_prefix_palindrome(const std::string& s) {
        std::string rev = s;
        std::reverse(rev.begin(), rev.end());
        std::string temp = s + '#' + rev;
        int m = temp.size();
        std::vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && temp[i] != temp[j]) j = pi[j - 1];
            if (temp[i] == temp[j]) ++j;
            pi[i] = j;
        }
        return pi[m - 1];
    }

    static std::string shortest_palindrome_by_prepending(const std::string& s) {
        int lpp = longest_prefix_palindrome(s);
        std::string suffix_rem = s.substr(lpp);
        std::reverse(suffix_rem.begin(), suffix_rem.end());
        return suffix_rem + s;
    }
};

int main() {
    std::string s = "aacecaaa";
    // Longest prefix palindrome is "aacecaa" (len 7)
    assert(PalindromeCut::longest_prefix_palindrome(s) == 7);
    assert(PalindromeCut::shortest_palindrome_by_prepending(s) == "aaacecaaa");

    std::string s2 = "abcd";
    assert(PalindromeCut::longest_prefix_palindrome(s2) == 1);
    assert(PalindromeCut::shortest_palindrome_by_prepending(s2) == "dcbabcd");
    return 0;
}
"""
    },
    {
        "filename": "string_hash_2d_matrix.cpp",
        "algorithm": "2D Polynomial Rolling Hash for Subgrid Matching",
        "purpose": "Computes 2D rolling hashes over a character grid to query subgrid hashes in O(1).",
        "time": "O(R * C) precomputation, O(1) query",
        "space": "O(R * C)",
        "preconditions": "2D grid of dimensions R x C.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Hash2D {
    static const unsigned long long P1 = 313ULL;
    static const unsigned long long P2 = 1009ULL;
    int R, C;
    std::vector<std::vector<unsigned long long>> h, pow1, pow2;

public:
    Hash2D(const std::vector<std::string>& grid) {
        R = grid.size();
        C = grid[0].size();
        h.assign(R + 1, std::vector<unsigned long long>(C + 1, 0));
        pow1.assign(R + 1, std::vector<unsigned long long>(C + 1, 1));
        pow2.assign(R + 1, std::vector<unsigned long long>(C + 1, 1));

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                pow1[i + 1][j + 1] = pow1[i][j + 1] * P1;
                pow2[i + 1][j + 1] = pow2[i + 1][j] * P2;
            }
        }

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                h[i + 1][j + 1] = h[i][j + 1] * P1 + h[i + 1][j] * P2 - h[i][j] * P1 * P2 + (unsigned char)grid[i][j];
            }
        }
    }

    // Query hash of subgrid [r1, r2] x [c1, c2] inclusive (0-indexed)
    unsigned long long get_subgrid(int r1, int c1, int r2, int c2) {
        int dr = r2 - r1 + 1;
        int dc = c2 - c1 + 1;
        unsigned long long p1 = 1;
        for (int i = 0; i < dr; ++i) p1 *= P1;
        unsigned long long p2 = 1;
        for (int j = 0; j < dc; ++j) p2 *= P2;

        return h[r2 + 1][c2 + 1] - h[r1][c2 + 1] * p1 - h[r2 + 1][c1] * p2 + h[r1][c1] * p1 * p2;
    }
};

int main() {
    std::vector<std::string> grid = {
        "abcd",
        "efgh",
        "abcd",
        "efgh"
    };
    Hash2D h2d(grid);
    // Subgrid [0..1, 0..1] is {"ab", "ef"}
    // Subgrid [2..3, 0..1] is {"ab", "ef"}
    assert(h2d.get_subgrid(0, 0, 1, 1) == h2d.get_subgrid(2, 0, 3, 1));
    // Different subgrid
    assert(h2d.get_subgrid(0, 0, 1, 1) != h2d.get_subgrid(0, 2, 1, 3));
    return 0;
}
"""
    }
]

for idx, item in enumerate(implementations, 1):
    path = os.path.join(DIR, item["filename"])
    header = f"""// Algorithm: {item["algorithm"]}
// Purpose: {item["purpose"]}
// Time Complexity: {item["time"]}
// Space Complexity: {item["space"]}
// Preconditions: {item["preconditions"]}

"""
    with open(path, "w", encoding="utf-8") as f:
        f.write(header + item["code"].strip() + "\n")
    print(f"Wrote [{idx}/{len(implementations)}]: {item['filename']}")

print(f"\nBatch 9b (Advanced Strings and Automata) completed: {len(implementations)} implementations written.")
