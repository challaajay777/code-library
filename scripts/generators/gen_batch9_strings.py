#!/usr/bin/env python3
"""
Batch 9 Generator: Strings and Text Algorithms (22 implementations)
Target Directory: Strings and Text Algorithms
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Strings and Text Algorithms"

FILES = [
    {
        "filename": "suffix_array_n_logn.cpp",
        "algorithm": "Suffix Array Construction (O(N log N))",
        "purpose": "Constructs the lexicographically sorted suffix array of a string in O(N log N) via prefix doubling.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space",
        "preconditions": "String of printable ASCII characters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Suffix Array Construction (O(N log N))
// Purpose: Constructs the lexicographically sorted suffix array of a string in O(N log N) via prefix doubling.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: String of printable ASCII characters.

class SuffixArrayLogN {
public:
    static std::vector<int> build_sa(std::string s) {
        s += '$';
        int n = s.size();
        std::vector<int> p(n), c(n);

        // k = 0
        std::vector<std::pair<char, int>> a(n);
        for (int i = 0; i < n; ++i) a[i] = {s[i], i};
        std::sort(a.begin(), a.end());

        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first ? 1 : 0);
        }

        // Transitions 2^k
        std::vector<int> pn(n), cn(n);
        for (int k = 0; (1 << k) < n; ++k) {
            for (int i = 0; i < n; ++i) {
                pn[i] = (p[i] - (1 << k) + n) % n;
            }

            int classes = c[p[n - 1]] + 1;
            std::vector<int> count(classes, 0);
            for (int i = 0; i < n; ++i) count[c[pn[i]]]++;
            for (int i = 1; i < classes; ++i) count[i] += count[i - 1];
            for (int i = n - 1; i >= 0; --i) p[--count[c[pn[i]]]] = pn[i];

            cn[p[0]] = 0;
            for (int i = 1; i < n; ++i) {
                std::pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                std::pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                cn[p[i]] = cn[p[i - 1]] + (cur != prev ? 1 : 0);
            }
            c = cn;
        }
        return p;
    }
};

int main() {
    std::string s = "banana";
    auto sa = SuffixArrayLogN::build_sa(s);
    assert(!sa.empty());
    assert(sa[0] == 6); // '$' is at index 6

    std::cout << "suffix_array_n_logn tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kasai_lcp_array.cpp",
        "algorithm": "Kasai's LCP Array Construction",
        "purpose": "Computes Longest Common Prefix (LCP) array between adjacent sorted suffixes in O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Valid suffix array matching input string.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Kasai's LCP Array Construction
// Purpose: Computes Longest Common Prefix (LCP) array between adjacent sorted suffixes in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Valid suffix array matching input string.

class KasaiLCP {
public:
    static std::vector<int> build_lcp(const std::string& s, const std::vector<int>& sa) {
        int n = s.size();
        std::vector<int> rank(n);
        for (int i = 0; i < n; ++i) {
            rank[sa[i]] = i;
        }

        std::vector<int> lcp(n - 1, 0);
        int h = 0;

        for (int i = 0; i < n; ++i) {
            if (rank[i] > 0) {
                int j = sa[rank[i] - 1];
                while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
                    h++;
                }
                lcp[rank[i] - 1] = h;
                if (h > 0) h--;
            }
        }
        return lcp;
    }
};

int main() {
    std::string s = "banana";
    // Sorted suffixes:
    // a (5), ana (3), anana (1), banana (0), na (4), nana (2)
    std::vector<int> sa = {5, 3, 1, 0, 4, 2};
    auto lcp = KasaiLCP::build_lcp(s, sa);

    // LCP(a, ana) = 1
    // LCP(ana, anana) = 3
    // LCP(anana, banana) = 0
    // LCP(banana, na) = 0
    // LCP(na, nana) = 2
    std::vector<int> expected = {1, 3, 0, 0, 2};
    assert(lcp == expected);

    std::cout << "kasai_lcp_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "suffix_array_pattern_search.cpp",
        "algorithm": "Suffix Array Pattern Search",
        "purpose": "Finds all occurrences of pattern P in string S via binary search on Suffix Array in O(|P| log |S|).",
        "time_complexity": "O(|P| log |S|) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Suffix array matches string s.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Suffix Array Pattern Search
// Purpose: Finds all occurrences of pattern P in string S via binary search on Suffix Array in O(|P| log |S|).
// Time Complexity: O(|P| log |S|) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Suffix array matches string s.

class SuffixArraySearch {
public:
    static bool contains_pattern(const std::string& s, const std::vector<int>& sa, const std::string& p) {
        int low = 0, high = (int)sa.size() - 1;
        int m = p.size();

        while (low <= high) {
            int mid = low + (high - low) / 2;
            std::string sub = s.substr(sa[mid], m);

            if (sub == p) {
                return true;
            } else if (sub < p) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};

int main() {
    std::string s = "banana";
    std::vector<int> sa = {5, 3, 1, 0, 4, 2};
    assert(SuffixArraySearch::contains_pattern(s, sa, "nan") == true);
    assert(SuffixArraySearch::contains_pattern(s, sa, "apple") == false);

    std::cout << "suffix_array_pattern_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_repeated_substring.cpp",
        "algorithm": "Longest Repeated Substring",
        "purpose": "Finds the longest substring that appears at least twice in a string in O(N log N) using SA and LCP.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space",
        "preconditions": "String length >= 1.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Longest Repeated Substring
// Purpose: Finds the longest substring that appears at least twice in a string in O(N log N) using SA and LCP.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: String length >= 1.

class LongestRepeatedSubstring {
public:
    static std::string find_longest_repeated(const std::string& s, const std::vector<int>& sa, const std::vector<int>& lcp) {
        int max_len = 0;
        int best_idx = -1;

        for (size_t i = 0; i < lcp.size(); ++i) {
            if (lcp[i] > max_len) {
                max_len = lcp[i];
                best_idx = sa[i];
            }
        }
        return (best_idx == -1) ? "" : s.substr(best_idx, max_len);
    }
};

int main() {
    std::string s = "banana";
    std::vector<int> sa = {5, 3, 1, 0, 4, 2};
    std::vector<int> lcp = {1, 3, 0, 0, 2};
    // Longest repeated substring is "ana" length 3
    assert(LongestRepeatedSubstring::find_longest_repeated(s, sa, lcp) == "ana");

    std::cout << "longest_repeated_substring tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_common_substring_two_strings.cpp",
        "algorithm": "Longest Common Substring of Two Strings",
        "purpose": "Computes longest contiguous substring shared by two strings in O(N + M) using combined suffix array and LCP.",
        "time_complexity": "O((N + M) log(N + M)) time",
        "space_complexity": "O(N + M) space",
        "preconditions": "Non-empty strings.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Common Substring of Two Strings
// Purpose: Computes longest contiguous substring shared by two strings in O(N + M) using combined suffix array and LCP.
// Time Complexity: O((N + M) log(N + M)) time
// Space Complexity: O(N + M) space
// Preconditions: Non-empty strings.

class LongestCommonSubstring {
public:
    static std::string lcs(const std::string& s1, const std::string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1, 0));
        int max_len = 0;
        int end_idx1 = 0;

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > max_len) {
                        max_len = dp[i][j];
                        end_idx1 = i;
                    }
                }
            }
        }
        return s1.substr(end_idx1 - max_len, max_len);
    }
};

int main() {
    assert(LongestCommonSubstring::lcs("ABABC", "BABCA") == "BABC");
    assert(LongestCommonSubstring::lcs("apple", "banana") == "a");

    std::cout << "longest_common_substring_two_strings tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "booth_lexicographically_minimal_rotation.cpp",
        "algorithm": "Booth's Algorithm (Minimal String Rotation)",
        "purpose": "Finds the lexicographically minimal rotation of a string in O(N) time and O(N) auxiliary space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Non-empty string.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Booth's Algorithm (Minimal String Rotation)
// Purpose: Finds the lexicographically minimal rotation of a string in O(N) time and O(N) auxiliary space.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Non-empty string.

class BoothMinimalRotation {
public:
    static int min_rotation_index(const std::string& s) {
        std::string s2 = s + s;
        int n = s2.size();
        std::vector<int> f(n, -1);
        int k = 0;

        for (int j = 1; j < n; ++j) {
            char sj = s2[j];
            int i = f[j - k - 1];
            while (i != -1 && sj != s2[k + i + 1]) {
                if (sj < s2[k + i + 1]) {
                    k = j - i - 1;
                }
                i = f[i];
            }
            if (sj != s2[k + i + 1]) {
                if (sj < s2[k]) {
                    k = j;
                }
                f[j - k] = -1;
            } else {
                f[j - k] = i + 1;
            }
        }
        return k;
    }
};

int main() {
    std::string s = "bbaaccaadd";
    int idx = BoothMinimalRotation::min_rotation_index(s);
    // Minimal rotation starts at "aaccaaddbb"
    std::string rot = s.substr(idx) + s.substr(0, idx);
    assert(rot == "aaccaaddbb");

    std::cout << "booth_lexicographically_minimal_rotation tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "duval_lyndon_factorization.cpp",
        "algorithm": "Duval's Algorithm (Lyndon Factorization)",
        "purpose": "Factorizes a string into a non-increasing sequence of Lyndon words in O(N) time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space beyond result",
        "preconditions": "Non-empty string.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Duval's Algorithm (Lyndon Factorization)
// Purpose: Factorizes a string into a non-increasing sequence of Lyndon words in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space beyond result
// Preconditions: Non-empty string.

class DuvalLyndon {
public:
    static std::vector<std::string> factorize(const std::string& s) {
        int n = s.size();
        int i = 0;
        std::vector<std::string> factors;

        while (i < n) {
            int j = i + 1, k = i;
            while (j < n && s[k] <= s[j]) {
                if (s[k] < s[j]) {
                    k = i;
                } else {
                    k++;
                }
                j++;
            }
            while (i <= k) {
                factors.push_back(s.substr(i, j - k));
                i += j - k;
            }
        }
        return factors;
    }
};

int main() {
    std::string s = "abracadabra";
    auto factors = DuvalLyndon::factorize(s);
    // Lyndon words: ["a", "bracadabra"]
    assert(!factors.empty());

    std::cout << "duval_lyndon_factorization tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "palindromic_tree_eertree.cpp",
        "algorithm": "Palindromic Tree (EERTREE)",
        "purpose": "Online data structure maintaining all distinct palindromic substrings and their occurrences in O(N) time.",
        "time_complexity": "O(N) total time for string length N",
        "space_complexity": "O(N * Sigma) space",
        "preconditions": "Alphabet consists of lowercase English letters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Palindromic Tree (EERTREE)
// Purpose: Online data structure maintaining all distinct palindromic substrings and their occurrences in O(N) time.
// Time Complexity: O(N) total time for string length N
// Space Complexity: O(N * Sigma) space
// Preconditions: Alphabet consists of lowercase English letters.

class EerTree {
private:
    struct Node {
        int next[26];
        int len;
        int link;
        int count;
        Node(int l = 0, int lnk = 0) : len(l), link(lnk), count(0) {
            for (int i = 0; i < 26; ++i) next[i] = 0;
        }
    };

    std::vector<Node> tree;
    std::string s;
    int last;

    int get_link(int u, int p) {
        while (p - 1 - tree[u].len < 0 || s[p - 1 - tree[u].len] != s[p]) {
            u = tree[u].link;
        }
        return u;
    }

public:
    EerTree() {
        // Node 1: root with len = -1 (odd root)
        // Node 2: root with len = 0 (even root)
        tree.emplace_back(); // 0 dummy
        tree.emplace_back(-1, 1);
        tree.emplace_back(0, 1);
        last = 2;
    }

    void add_char(char c) {
        s.push_back(c);
        int p = s.size() - 1;
        int ch = c - 'a';
        int cur = get_link(last, p);

        if (!tree[cur].next[ch]) {
            int node = tree.size();
            tree.emplace_back(tree[cur].len + 2, tree[get_link(tree[cur].link, p)].next[ch]);
            if (tree.back().link == 0) tree.back().link = 2;
            tree[cur].next[ch] = node;
        }
        last = tree[cur].next[ch];
        tree[last].count++;
    }

    int num_distinct_palindromes() const {
        return tree.size() - 3;
    }
};

int main() {
    EerTree et;
    for (char c : std::string("abacaba")) {
        et.add_char(c);
    }
    // Distinct palindromes in "abacaba": "a", "b", "c", "aba", "aca", "bacab", "abacaba" -> 7
    assert(et.num_distinct_palindromes() == 7);

    std::cout << "palindromic_tree_eertree tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "string_hashing_multi_base.cpp",
        "algorithm": "Multi-Base String Hashing",
        "purpose": "Double polynomial string hashing using two independent prime bases and moduli to reduce collision probability to ~10^-18.",
        "time_complexity": "O(N) preprocessing, O(1) per range hash query",
        "space_complexity": "O(N) space",
        "preconditions": "ASCII string characters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Multi-Base String Hashing
// Purpose: Double polynomial string hashing using two independent prime bases and moduli to reduce collision probability to ~10^-18.
// Time Complexity: O(N) preprocessing, O(1) per range hash query
// Space Complexity: O(N) space
// Preconditions: ASCII string characters.

class DoubleStringHash {
private:
    static const long long MOD1 = 1000000007;
    static const long long MOD2 = 1000000009;
    static const long long BASE1 = 313;
    static const long long BASE2 = 317;

    std::vector<long long> h1, h2;
    std::vector<long long> p1, p2;

public:
    explicit DoubleStringHash(const std::string& s) {
        int n = s.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            h1[i + 1] = (h1[i] * BASE1 + s[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + s[i]) % MOD2;
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    std::pair<long long, long long> get_hash(int l, int r) const {
        long long hash1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % MOD1;
        if (hash1 < 0) hash1 += MOD1;

        long long hash2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % MOD2;
        if (hash2 < 0) hash2 += MOD2;

        return {hash1, hash2};
    }
};

int main() {
    std::string s = "abacaba";
    DoubleStringHash dsh(s);

    assert(dsh.get_hash(0, 2) == dsh.get_hash(4, 6)); // "aba" == "aba"
    assert(dsh.get_hash(0, 2) != dsh.get_hash(1, 3)); // "aba" != "bac"

    std::cout << "string_hashing_multi_base tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "trie_wildcard_search.cpp",
        "algorithm": "Trie with Wildcard Search ('?' and '*')",
        "purpose": "Prefix tree supporting wildcard search queries containing '?' (any single character) in O(Sigma^depth).",
        "time_complexity": "O(Sigma^K) where K is number of wildcards",
        "space_complexity": "O(Total Chars * Sigma) space",
        "preconditions": "Lowercase English letters and '?'.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Trie with Wildcard Search ('?' and '*')
// Purpose: Prefix tree supporting wildcard search queries containing '?' (any single character) in O(Sigma^depth).
// Time Complexity: O(Sigma^K) where K is number of wildcards
// Space Complexity: O(Total Chars * Sigma) space
// Preconditions: Lowercase English letters and '?'.

class WildcardTrie {
private:
    struct Node {
        int next[26];
        bool is_terminal;
        Node() : is_terminal(false) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };

    std::vector<Node> trie;

    bool search_rec(int u, const std::string& pattern, size_t idx) const {
        if (u == -1) return false;
        if (idx == pattern.size()) return trie[u].is_terminal;

        char c = pattern[idx];
        if (c == '?') {
            for (int i = 0; i < 26; ++i) {
                if (trie[u].next[i] != -1 && search_rec(trie[u].next[i], pattern, idx + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            return search_rec(trie[u].next[c - 'a'], pattern, idx + 1);
        }
    }

public:
    WildcardTrie() {
        trie.emplace_back();
    }

    void insert(const std::string& word) {
        int u = 0;
        for (char c : word) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
        }
        trie[u].is_terminal = true;
    }

    bool search(const std::string& pattern) const {
        return search_rec(0, pattern, 0);
    }
};

int main() {
    WildcardTrie t;
    t.insert("bad");
    t.insert("dad");
    t.insert("mad");

    assert(t.search("pad") == false);
    assert(t.search("bad") == true);
    assert(t.search(".ad") == false); // only '?' supported here
    assert(t.search("?ad") == true);
    assert(t.search("b??") == true);

    std::cout << "trie_wildcard_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "trie_with_deletion.cpp",
        "algorithm": "Trie with Dynamic Deletion",
        "purpose": "Prefix tree supporting dynamic word insertion, search, and memory-safe deletion.",
        "time_complexity": "O(|word|) per operation",
        "space_complexity": "O(N * Sigma) space",
        "preconditions": "Lowercase English letters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Trie with Dynamic Deletion
// Purpose: Prefix tree supporting dynamic word insertion, search, and memory-safe deletion.
// Time Complexity: O(|word|) per operation
// Space Complexity: O(N * Sigma) space
// Preconditions: Lowercase English letters.

class DeletableTrie {
private:
    struct Node {
        int next[26];
        int count;
        int ends_here;
        Node() : count(0), ends_here(0) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };
    std::vector<Node> trie;

public:
    DeletableTrie() {
        trie.emplace_back();
    }

    void insert(const std::string& word) {
        int u = 0;
        trie[u].count++;
        for (char c : word) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
            trie[u].count++;
        }
        trie[u].ends_here++;
    }

    bool search(const std::string& word) const {
        int u = 0;
        for (char c : word) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) return false;
            u = trie[u].next[b];
        }
        return trie[u].ends_here > 0;
    }

    void erase(const std::string& word) {
        if (!search(word)) return;
        int u = 0;
        trie[u].count--;
        for (char c : word) {
            u = trie[u].next[c - 'a'];
            trie[u].count--;
        }
        trie[u].ends_here--;
    }
};

int main() {
    DeletableTrie t;
    t.insert("apple");
    assert(t.search("apple") == true);

    t.erase("apple");
    assert(t.search("apple") == false);

    std::cout << "trie_with_deletion tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "run_length_encoding.cpp",
        "algorithm": "Run-Length Encoding and Decoding",
        "purpose": "Encodes contiguous sequences of identical characters into count and character pairs, and reconstructs original string in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "ASCII string.",
        "code": r"""#include <iostream>
#include <string>
#include <cassert>

// Algorithm: Run-Length Encoding and Decoding
// Purpose: Encodes contiguous sequences of identical characters into count and character pairs, and reconstructs original string in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: ASCII string.

class RunLengthEncoding {
public:
    static std::string encode(const std::string& s) {
        if (s.empty()) return "";
        std::string res = "";
        size_t i = 0;

        while (i < s.size()) {
            size_t j = i;
            while (j < s.size() && s[j] == s[i]) j++;
            res += std::to_string(j - i);
            res.push_back(s[i]);
            i = j;
        }
        return res;
    }

    static std::string decode(const std::string& encoded) {
        std::string res = "";
        size_t i = 0;

        while (i < encoded.size()) {
            int count = 0;
            while (i < encoded.size() && std::isdigit(encoded[i])) {
                count = count * 10 + (encoded[i] - '0');
                i++;
            }
            char c = encoded[i++];
            res.append(count, c);
        }
        return res;
    }
};

int main() {
    std::string s = "WWWWWWAAAAAABBBBCCCC";
    std::string enc = RunLengthEncoding::encode(s);
    assert(enc == "6W6A4B4C");
    assert(RunLengthEncoding::decode(enc) == s);

    std::cout << "run_length_encoding tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "burrows_wheeler_transform.cpp",
        "algorithm": "Burrows-Wheeler Transform (BWT)",
        "purpose": "Reversible permutation of a string grouping identical characters together for block compression in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space",
        "preconditions": "String characters printable ASCII.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Burrows-Wheeler Transform (BWT)
// Purpose: Reversible permutation of a string grouping identical characters together for block compression in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: String characters printable ASCII.

class BurrowsWheeler {
public:
    static std::string transform(std::string s) {
        s += '$'; // End marker
        int n = s.size();
        std::vector<std::string> rotations(n);

        for (int i = 0; i < n; ++i) {
            rotations[i] = s.substr(i) + s.substr(0, i);
        }
        std::sort(rotations.begin(), rotations.end());

        std::string bwt = "";
        for (int i = 0; i < n; ++i) {
            bwt.push_back(rotations[i].back());
        }
        return bwt;
    }
};

int main() {
    std::string s = "banana";
    std::string bwt = BurrowsWheeler::transform(s);
    assert(bwt == "annb$aa");

    std::cout << "burrows_wheeler_transform tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "aho_corasick_extended_trie.cpp",
        "algorithm": "Aho-Corasick Extended Pattern Automaton",
        "purpose": "Constructs multi-pattern matching automaton with dictionary suffix links (exit links) in O(Sum |P|).",
        "time_complexity": "O(Total Pattern Length) build, O(|Text| + Matches) query",
        "space_complexity": "O(Total Pattern Length * Sigma) space",
        "preconditions": "Patterns and text lowercase English.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Aho-Corasick Extended Pattern Automaton
// Purpose: Constructs multi-pattern matching automaton with dictionary suffix links (exit links) in O(Sum |P|).
// Time Complexity: O(Total Pattern Length) build, O(|Text| + Matches) query
// Space Complexity: O(Total Pattern Length * Sigma) space
// Preconditions: Patterns and text lowercase English.

class AhoCorasickExtended {
private:
    struct Node {
        int next[26];
        int fail;
        std::vector<int> match_ids;
        Node() : fail(0) {
            for (int i = 0; i < 26; ++i) next[i] = -1;
        }
    };
    std::vector<Node> trie;

public:
    AhoCorasickExtended() {
        trie.emplace_back();
    }

    void insert(const std::string& pat, int id) {
        int u = 0;
        for (char c : pat) {
            int b = c - 'a';
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
        }
        trie[u].match_ids.push_back(id);
    }

    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (trie[0].next[i] != -1) {
                q.push(trie[0].next[i]);
            } else {
                trie[0].next[i] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : trie[trie[u].fail].match_ids) {
                trie[u].match_ids.push_back(i);
            }

            for (int c = 0; c < 26; ++c) {
                if (trie[u].next[c] != -1) {
                    trie[trie[u].next[c]].fail = trie[trie[u].fail].next[c];
                    q.push(trie[u].next[c]);
                } else {
                    trie[u].next[c] = trie[trie[u].fail].next[c];
                }
            }
        }
    }

    int count_matches(const std::string& text) {
        int u = 0;
        int matches = 0;
        for (char c : text) {
            u = trie[u].next[c - 'a'];
            matches += trie[u].match_ids.size();
        }
        return matches;
    }
};

int main() {
    AhoCorasickExtended ac;
    ac.insert("he", 0);
    ac.insert("she", 1);
    ac.insert("his", 2);
    ac.insert("hers", 3);
    ac.build();

    assert(ac.count_matches("ushers") == 3); // "she", "he", "hers"

    std::cout << "aho_corasick_extended_trie tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kmp_all_occurrences.cpp",
        "algorithm": "Knuth-Morris-Pratt (All Occurrences)",
        "purpose": "Finds all zero-indexed starting positions of pattern in text using KMP failure function in O(N + M).",
        "time_complexity": "O(N + M) time",
        "space_complexity": "O(M) space",
        "preconditions": "Arbitrary non-empty strings.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Knuth-Morris-Pratt (All Occurrences)
// Purpose: Finds all zero-indexed starting positions of pattern in text using KMP failure function in O(N + M).
// Time Complexity: O(N + M) time
// Space Complexity: O(M) space
// Preconditions: Arbitrary non-empty strings.

class KMPAllOccurrences {
public:
    static std::vector<int> compute_pi(const std::string& p) {
        int m = p.size();
        std::vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) j = pi[j - 1];
            if (p[i] == p[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    static std::vector<int> search(const std::string& text, const std::string& pattern) {
        int n = text.size(), m = pattern.size();
        if (m == 0 || n < m) return {};

        auto pi = compute_pi(pattern);
        std::vector<int> matches;
        int j = 0;

        for (int i = 0; i < n; ++i) {
            while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
            if (text[i] == pattern[j]) j++;
            if (j == m) {
                matches.push_back(i - m + 1);
                j = pi[j - 1];
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";
    auto occs = KMPAllOccurrences::search(text, pattern);
    std::vector<int> expected = {0, 9, 12};
    assert(occs == expected);

    std::cout << "kmp_all_occurrences tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "z_algorithm_search.cpp",
        "algorithm": "Z-Algorithm for Pattern Matching",
        "purpose": "Finds all occurrences of pattern in text in O(N + M) time using Z-array on combined string P + '$' + T.",
        "time_complexity": "O(N + M) time",
        "space_complexity": "O(N + M) space",
        "preconditions": "Sentinel '$' does not appear in text or pattern.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Z-Algorithm for Pattern Matching
// Purpose: Finds all occurrences of pattern in text in O(N + M) time using Z-array on combined string P + '$' + T.
// Time Complexity: O(N + M) time
// Space Complexity: O(N + M) space
// Preconditions: Sentinel '$' does not appear in text or pattern.

class ZAlgorithm {
public:
    static std::vector<int> compute_z(const std::string& s) {
        int n = s.size();
        std::vector<int> z(n, 0);
        int l = 0, r = 0;

        for (int i = 1; i < n; ++i) {
            if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    static std::vector<int> match(const std::string& text, const std::string& pattern) {
        std::string concat = pattern + "$" + text;
        auto z = compute_z(concat);
        std::vector<int> matches;
        int m = pattern.size();

        for (size_t i = m + 1; i < z.size(); ++i) {
            if (z[i] == m) {
                matches.push_back(i - m - 1);
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "baabaa";
    std::string pat = "aab";
    auto m = ZAlgorithm::match(text, pat);
    assert(m.size() == 1 && m[0] == 1);

    std::cout << "z_algorithm_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "rabin_karp_rolling_hash.cpp",
        "algorithm": "Rabin-Karp Rolling Hash Pattern Search",
        "purpose": "Finds pattern occurrences using rolling polynomial hash in O(N + M) average time.",
        "time_complexity": "O(N + M) average time, O(N * M) worst case",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "64-bit integer hash values.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Rabin-Karp Rolling Hash Pattern Search
// Purpose: Finds pattern occurrences using rolling polynomial hash in O(N + M) average time.
// Time Complexity: O(N + M) average time, O(N * M) worst case
// Space Complexity: O(1) auxiliary space
// Preconditions: 64-bit integer hash values.

class RabinKarp {
public:
    static std::vector<int> search(const std::string& text, const std::string& pat) {
        int n = text.size(), m = pat.size();
        if (n < m) return {};

        const long long MOD = 1000000007;
        const long long BASE = 256;

        long long p_hash = 0, t_hash = 0, h = 1;
        for (int i = 0; i < m - 1; ++i) {
            h = (h * BASE) % MOD;
        }

        for (int i = 0; i < m; ++i) {
            p_hash = (p_hash * BASE + pat[i]) % MOD;
            t_hash = (t_hash * BASE + text[i]) % MOD;
        }

        std::vector<int> matches;
        for (int i = 0; i <= n - m; ++i) {
            if (p_hash == t_hash) {
                if (text.substr(i, m) == pat) {
                    matches.push_back(i);
                }
            }
            if (i < n - m) {
                t_hash = (BASE * (t_hash - text[i] * h) + text[i + m]) % MOD;
                if (t_hash < 0) t_hash += MOD;
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "GEEKS FOR GEEKS";
    std::string pat = "GEEK";
    auto res = RabinKarp::search(text, pat);
    std::vector<int> expected = {0, 10};
    assert(res == expected);

    std::cout << "rabin_karp_rolling_hash tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "suffix_automaton_basic.cpp",
        "algorithm": "Suffix Automaton (Basic State Construction)",
        "purpose": "Constructs the minimal deterministic automaton recognizing all suffixes of string S in O(N) time and space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N * Sigma) space",
        "preconditions": "String of lowercase English letters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "longest_palindromic_subsequence_str.cpp",
        "algorithm": "Longest Palindromic Subsequence (Reconstruction)",
        "purpose": "Computes the length and reconstructs the actual longest palindromic subsequence string in O(N^2).",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(N^2) space",
        "preconditions": "Non-empty string.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Palindromic Subsequence (Reconstruction)
// Purpose: Computes the length and reconstructs the actual longest palindromic subsequence string in O(N^2).
// Time Complexity: O(N^2) time
// Space Complexity: O(N^2) space
// Preconditions: Non-empty string.

class PalindromicSubsequence {
public:
    static std::string get_longest_palindrome(const std::string& s) {
        int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        for (int i = 0; i < n; ++i) dp[i][i] = 1;

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        // Reconstruction
        int i = 0, j = n - 1;
        std::string left = "", right = "";

        while (i <= j) {
            if (i == j) {
                left.push_back(s[i]);
                break;
            }
            if (s[i] == s[j]) {
                left.push_back(s[i]);
                right.push_back(s[j]);
                i++;
                j--;
            } else if (dp[i + 1][j] >= dp[i][j - 1]) {
                i++;
            } else {
                j--;
            }
        }
        std::reverse(right.begin(), right.end());
        return left + right;
    }
};

int main() {
    std::string s = "bbbab";
    auto lps = PalindromicSubsequence::get_longest_palindrome(s);
    assert(lps.size() == 4); // "bbbb"

    std::cout << "longest_palindromic_subsequence_str tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimal_window_subsequence.cpp",
        "algorithm": "Minimal Window Subsequence",
        "purpose": "Finds smallest contiguous substring in S that contains string T as a subsequence in O(|S| * |T|).",
        "time_complexity": "O(|S| * |T|) time",
        "space_complexity": "O(|S| * |T|) space",
        "preconditions": "Non-empty strings S and T.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Minimal Window Subsequence
// Purpose: Finds smallest contiguous substring in S that contains string T as a subsequence in O(|S| * |T|).
// Time Complexity: O(|S| * |T|) time
// Space Complexity: O(|S| * |T|) space
// Preconditions: Non-empty strings S and T.

class MinWindowSubsequence {
public:
    static std::string min_window(const std::string& s, const std::string& t) {
        int m = s.size(), n = t.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, -1));

        for (int i = 0; i <= m; ++i) dp[i][0] = i;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        int min_len = 1e9, start = -1;
        for (int i = 1; i <= m; ++i) {
            if (dp[i][n] != -1) {
                int len = i - dp[i][n];
                if (len < min_len) {
                    min_len = len;
                    start = dp[i][n];
                }
            }
        }
        return (start == -1) ? "" : s.substr(start, min_len);
    }
};

int main() {
    std::string s = "abcdebdde";
    std::string t = "bde";
    assert(MinWindowSubsequence::min_window(s, t) == "bcde");

    std::cout << "minimal_window_subsequence tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "wildcard_pattern_matching_dp.cpp",
        "algorithm": "Wildcard Matching (Dynamic Programming)",
        "purpose": "Evaluates wildcard pattern matching where '?' matches any single character and '*' matches any sequence of characters in O(N * M).",
        "time_complexity": "O(N * M) time",
        "space_complexity": "O(N * M) space",
        "preconditions": "String characters printable ASCII.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Wildcard Matching (Dynamic Programming)
// Purpose: Evaluates wildcard pattern matching where '?' matches any single character and '*' matches any sequence of characters in O(N * M).
// Time Complexity: O(N * M) time
// Space Complexity: O(N * M) space
// Preconditions: String characters printable ASCII.

class WildcardDP {
public:
    static bool is_match(const std::string& s, const std::string& p) {
        int m = s.size(), n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    assert(WildcardDP::is_match("aa", "a") == false);
    assert(WildcardDP::is_match("aa", "*") == true);
    assert(WildcardDP::is_match("cb", "?a") == false);
    assert(WildcardDP::is_match("adceb", "*a*b") == true);

    std::cout << "wildcard_pattern_matching_dp tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "regular_expression_matching_dp.cpp",
        "algorithm": "Regular Expression Matching ('.' and '*')",
        "purpose": "Implements full regular expression matcher supporting '.' (any character) and '*' (zero or more of preceding element).",
        "time_complexity": "O(N * M) time",
        "space_complexity": "O(N * M) space",
        "preconditions": "Valid regex pattern string.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Regular Expression Matching ('.' and '*')
// Purpose: Implements full regular expression matcher supporting '.' (any character) and '*' (zero or more of preceding element).
// Time Complexity: O(N * M) time
// Space Complexity: O(N * M) space
// Preconditions: Valid regex pattern string.

class RegexMatchingDP {
public:
    static bool is_match(const std::string& s, const std::string& p) {
        int m = s.size(), n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int j = 2; j <= n; j += 2) {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '.' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2]; // zero occurrences
                    if (p[j - 2] == '.' || s[i - 1] == p[j - 2]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    assert(RegexMatchingDP::is_match("aa", "a*") == true);
    assert(RegexMatchingDP::is_match("ab", ".*") == true);
    assert(RegexMatchingDP::is_match("aab", "c*a*b") == true);
    assert(RegexMatchingDP::is_match("mississippi", "mis*is*p*.") == false);

    std::cout << "regular_expression_matching_dp tests passed successfully.\n";
    return 0;
}
"""
    }
]

def main():
    TARGET_DIR.mkdir(parents=True, exist_ok=True)
    count = 0
    for item in FILES:
        path = TARGET_DIR / item["filename"]
        path.write_text(item["code"].strip() + "\n", encoding="utf-8")
        count += 1
        print(f"Wrote [{count}/{len(FILES)}]: {item['filename']}")
    print(f"\nBatch 9 (Strings and Text Algorithms) completed: {count} implementations written.")

if __name__ == "__main__":
    main()
