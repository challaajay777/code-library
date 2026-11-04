#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Stirling Numbers of the Second Kind
// Purpose: Computes S(n, k), the number of ways to partition a set of n elements into k non-empty subsets, in O(n * k).
// Time Complexity: O(N * K) time
// Space Complexity: O(N * K) space
// Preconditions: 0 <= k <= n.

class StirlingSecondKind {
public:
    static std::vector<std::vector<long long>> compute_table(int n, int k, long long mod = 1e9 + 7) {
        std::vector<std::vector<long long>> S(n + 1, std::vector<long long>(k + 1, 0));
        S[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= std::min(i, k); ++j) {
                // S(i, j) = S(i-1, j-1) + j * S(i-1, j)
                S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod;
            }
        }
        return S;
    }
};

int main() {
    auto S = StirlingSecondKind::compute_table(4, 4);
    // S(4, 1) = 1
    // S(4, 2) = 7
    // S(4, 3) = 6
    // S(4, 4) = 1
    assert(S[4][1] == 1);
    assert(S[4][2] == 7);
    assert(S[4][3] == 6);
    assert(S[4][4] == 1);

    std::cout << "stirling_numbers_second_kind tests passed successfully.\n";
    return 0;
}
