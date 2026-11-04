#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Stirling Numbers of the First Kind (Unsigned)
// Purpose: Computes |s(n, k)|, the number of permutations of n elements with exactly k disjoint cycles, in O(n * k).
// Time Complexity: O(N * K) time
// Space Complexity: O(N * K) auxiliary space
// Preconditions: 0 <= k <= n.

class StirlingFirstKind {
public:
    static std::vector<std::vector<long long>> compute_table(int n, int k, long long mod = 1e9 + 7) {
        std::vector<std::vector<long long>> s(n + 1, std::vector<long long>(k + 1, 0));
        s[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= std::min(i, k); ++j) {
                // s(i, j) = s(i-1, j-1) + (i-1) * s(i-1, j)
                s[i][j] = (s[i - 1][j - 1] + (i - 1) * s[i - 1][j]) % mod;
            }
        }
        return s;
    }
};

int main() {
    auto s = StirlingFirstKind::compute_table(4, 4);
    // Permutations of 4:
    // k=1: (4-1)! = 6
    // k=2: 11
    // k=3: 6
    // k=4: 1
    assert(s[4][1] == 6);
    assert(s[4][2] == 11);
    assert(s[4][3] == 6);
    assert(s[4][4] == 1);

    std::cout << "stirling_numbers_first_kind tests passed successfully.\n";
    return 0;
}
