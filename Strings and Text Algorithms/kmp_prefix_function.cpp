// Algorithm: Knuth-Morris-Pratt (KMP) Prefix Function
// Supports: Prefix function computation (pi array), pattern search, smallest period length
// Indexing: 0-based string indices [0, n - 1]
// Complexity: O(n) prefix table construction, O(n + m) pattern search, O(n) memory
// Preconditions: Strings can contain any characters

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct KMP {
    // Computes pi[i]: length of longest proper prefix of s[0..i] that is also a suffix of s[0..i]
    static vector<int> prefix_function(const string& s) {
        int n = (int)s.size();
        vector<int> pi(n, 0);
        for (int i = 1; i < n; ++i) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) {
                j = pi[j - 1];
            }
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    // Finds all 0-based starting occurrences of pattern in text
    static vector<int> search(const string& text, const string& pattern) {
        if (pattern.empty()) return {};
        string combined = pattern + '#' + text;
        auto pi = prefix_function(combined);
        int p_len = (int)pattern.size();
        vector<int> matches;

        for (size_t i = p_len + 1; i < combined.size(); ++i) {
            if (pi[i] == p_len) {
                matches.push_back((int)(i - 2 * p_len));
            }
        }
        return matches;
    }

    // Returns length of the smallest repeating period of string s
    static int smallest_period(const string& s) {
        int n = (int)s.size();
        if (n == 0) return 0;
        auto pi = prefix_function(s);
        int k = n - pi[n - 1];
        if (n % k == 0) return k;
        return n;
    }
};
