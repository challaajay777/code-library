// Algorithm: Manacher's Algorithm
// Supports: Finding all sub-palindromes in linear time, longest palindromic substring, O(1) palindrome query
// Indexing: 0-based original string indices [0, n - 1]
// Complexity: O(n) time, O(n) memory
// Preconditions: Standard string

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Manacher {
    string t;
    vector<int> p; // p[i] = radius of palindrome centered at i in expanded string t
    int original_n;

    explicit Manacher(const string& s) {
        original_n = (int)s.size();
        t = "^";
        for (char c : s) {
            t += '#';
            t += c;
        }
        t += "#$";

        int m = (int)t.size();
        p.assign(m, 0);
        int c = 0, r = 0;

        for (int i = 1; i < m - 1; ++i) {
            int i_mirror = 2 * c - i;
            if (r > i) {
                p[i] = min(r - i, p[i_mirror]);
            }
            while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
                p[i]++;
            }
            if (i + p[i] > r) {
                c = i;
                r = i + p[i];
            }
        }
    }

    // Returns true if substring s[l..r] is a palindrome in O(1)
    bool is_palindrome(int l, int r) const {
        assert(0 <= l && l <= r && r < original_n);
        int center = l + r + 2;
        int len = r - l + 1;
        return p[center] >= len;
    }

    // Returns {start_pos, length} of the longest palindromic substring
    pair<int, int> longest_palindrome() const {
        int max_len = 0, center_idx = 0;
        for (size_t i = 1; i < p.size() - 1; ++i) {
            if (p[i] > max_len) {
                max_len = p[i];
                center_idx = (int)i;
            }
        }
        int start = (center_idx - max_len) / 2;
        return {start, max_len};
    }
};
