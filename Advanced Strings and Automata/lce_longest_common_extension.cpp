// Algorithm: Longest Common Extension (LCE) via Suffix Array and RMQ
// Purpose: Queries length of longest common prefix of suffixes starting at i and j in O(1) time.
// Time Complexity: O(N log N) precomputation, O(1) per query
// Space Complexity: O(N log N)
// Preconditions: Valid 0-indexed positions within the string.

#include <iostream>
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
