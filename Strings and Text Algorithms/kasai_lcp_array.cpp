#include <iostream>
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
