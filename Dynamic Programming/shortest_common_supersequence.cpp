// Algorithm: Shortest Common Supersequence with Reconstruction
// Purpose: Finds the shortest sequence that has both input sequences as subsequences.
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// Preconditions: Strings of valid characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::string shortest_common_supersequence(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + 1;
        }
    }

    std::string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res.push_back(a[i - 1]);
            --i; --j;
        } else if (dp[i - 1][j] < dp[i][j - 1]) {
            res.push_back(a[i - 1]);
            --i;
        } else {
            res.push_back(b[j - 1]);
            --j;
        }
    }
    while (i > 0) res.push_back(a[--i]);
    while (j > 0) res.push_back(b[--j]);

    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    std::string a = "abac", b = "cab";
    std::string scs = shortest_common_supersequence(a, b);
    assert(scs == "cabac");
    return 0;
}
