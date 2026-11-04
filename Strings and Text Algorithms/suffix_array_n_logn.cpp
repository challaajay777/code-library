#include <iostream>
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
