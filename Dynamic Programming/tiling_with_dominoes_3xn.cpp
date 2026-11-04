// Algorithm: 3xN Domino Tiling DP
// Purpose: Finds number of ways to completely tile a 3 x N grid with 2x1 dominoes.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: N >= 0.

#include <iostream>
#include <vector>
#include <cassert>

long long count_3xn_domino_tilings(int n) {
    if (n % 2 != 0) return 0;
    if (n == 0) return 1;

    std::vector<long long> A(n + 1, 0); // completely filled
    std::vector<long long> B(n + 1, 0); // one corner missing

    A[0] = 1; A[1] = 0;
    B[0] = 0; B[1] = 1;

    for (int i = 2; i <= n; ++i) {
        A[i] = A[i - 2] + 2 * B[i - 1];
        B[i] = A[i - 1] + B[i - 2];
    }
    return A[n];
}

int main() {
    assert(count_3xn_domino_tilings(2) == 3);
    assert(count_3xn_domino_tilings(4) == 11);
    assert(count_3xn_domino_tilings(3) == 0);
    return 0;
}
