// Algorithm: Levenshtein Edit Distance with Operation Alignment Trace
// Purpose: Finds minimum insertion, deletion, and replacement operations between two strings and reconstructs the trace.
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// Preconditions: Strings of comparable characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct EditTrace {
    int distance;
    std::vector<std::string> operations;
};

EditTrace edit_distance_trace(const std::string& s, const std::string& t) {
    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }

    std::vector<std::string> ops;
    int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && s[i - 1] == t[j - 1] && dp[i][j] == dp[i - 1][j - 1]) {
            ops.push_back(std::string("MATCH ") + s[i - 1]);
            --i; --j;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            ops.push_back(std::string("REPLACE ") + s[i - 1] + " WITH " + t[j - 1]);
            --i; --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            ops.push_back(std::string("DELETE ") + s[i - 1]);
            --i;
        } else {
            ops.push_back(std::string("INSERT ") + t[j - 1]);
            --j;
        }
    }
    std::reverse(ops.begin(), ops.end());
    return {dp[n][m], ops};
}

int main() {
    auto res = edit_distance_trace("kitten", "sitting");
    assert(res.distance == 3);
    assert(!res.operations.empty());
    return 0;
}
