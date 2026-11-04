// Algorithm: Palindromic Substring Counting via Manacher
// Purpose: Calculates total number of palindromic substrings and longest palindrome substring range.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: String of printable ASCII characters.

#include <iostream>
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
