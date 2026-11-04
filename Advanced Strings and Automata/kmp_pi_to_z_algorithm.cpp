// Algorithm: Convert KMP Pi Function to Z-Algorithm Array
// Purpose: Converts KMP prefix function values to Z-algorithm array in strict linear time.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Pi-array has length n >= 1.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::vector<int> pi_to_z(const std::vector<int>& pi, const std::string& s) {
    int n = s.size();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::string s = "abacaba";
    std::vector<int> pi = {0, 0, 1, 0, 1, 2, 3};
    auto z = pi_to_z(pi, s);
    std::vector<int> expected_z = {0, 0, 1, 0, 3, 0, 1};
    assert(z == expected_z);
    return 0;
}
