// Algorithm: Convert Z-Algorithm Array to KMP Pi Function
// Purpose: Converts Z-values to KMP prefix function pi values in strict linear time.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Z-array has length n >= 1.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

std::vector<int> z_to_pi(const std::vector<int>& z) {
    int n = z.size();
    std::vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        if (z[i] > 0) {
            int right = i + z[i] - 1;
            pi[right] = std::max(pi[right], z[i]);
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        pi[i] = std::max(pi[i], pi[i + 1] - 1);
    }
    return pi;
}

int main() {
    // String "abacaba"
    // Z-values: [0, 0, 1, 0, 3, 0, 1]
    std::vector<int> z = {0, 0, 1, 0, 3, 0, 1};
    auto pi = z_to_pi(z);
    // Expected pi for "abacaba": [0, 0, 1, 0, 1, 2, 3]
    std::vector<int> expected = {0, 0, 1, 0, 1, 2, 3};
    assert(pi == expected);
    return 0;
}
