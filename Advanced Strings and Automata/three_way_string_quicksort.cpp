// Algorithm: Three-Way String Quicksort (Bentley-Sedgewick)
// Purpose: Efficient multikey ternary quicksort specialized for string collections.
// Time Complexity: O(N * L)
// Space Complexity: O(L + log N)
// Preconditions: String array with random-access iterators.

#include <iostream>
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
