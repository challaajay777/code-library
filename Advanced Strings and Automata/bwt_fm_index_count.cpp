// Algorithm: FM-Index Count Query via Burrows-Wheeler Transform
// Purpose: Counts occurrences of a pattern in a text using BWT and rank (Occ) array.
// Time Complexity: O(M) per count query, O(N * Sigma) index build
// Space Complexity: O(N * Sigma)
// Preconditions: Text ending with special sentinel '$' smaller than all characters.

#include <iostream>
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
