// Algorithm: Z-Algorithm
// Supports: Z-array computation (LCP between s and suffix s[i..n-1]), exact pattern matching
// Indexing: 0-based string indices [0, n - 1]
// Complexity: O(n) linear time, O(n) memory
// Preconditions: Non-empty string

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct ZAlgorithm {
    // Computes Z-array for string s
    static vector<int> compute_z(const string& s) {
        int n = (int)s.size();
        vector<int> z(n, 0);
        z[0] = n;
        int l = 0, r = 0;

        for (int i = 1; i < n; ++i) {
            if (i <= r) {
                z[i] = min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    // Searches pattern in text using Z-algorithm
    static vector<int> search(const string& text, const string& pattern) {
        if (pattern.empty()) return {};
        string combined = pattern + '$' + text;
        auto z = compute_z(combined);
        int p_len = (int)pattern.size();
        vector<int> matches;

        for (size_t i = p_len + 1; i < combined.size(); ++i) {
            if (z[i] >= p_len) {
                matches.push_back((int)(i - p_len - 1));
            }
        }
        return matches;
    }
};
