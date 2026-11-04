// Algorithm: Matrix Chain Multiplication with Optimal Parenthesization
// Purpose: Finds minimum scalar multiplications to multiply a chain of matrices and outputs parenthesized form.
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: Dimensions array p of size n+1 for n matrices, where matrix i has dimensions p[i-1] x p[i].

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <climits>

struct MCMResult {
    long long min_cost;
    std::string order;
};

void build_order(int i, int j, const std::vector<std::vector<int>>& split, std::string& res) {
    if (i == j) {
        res += "A" + std::to_string(i);
        return;
    }
    res += "(";
    build_order(i, split[i][j], split, res);
    res += " x ";
    build_order(split[i][j] + 1, j, split, res);
    res += ")";
}

MCMResult matrix_chain_order(const std::vector<int>& p) {
    int n = p.size() - 1;
    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1, 0));
    std::vector<std::vector<int>> split(n + 1, std::vector<int>(n + 1, 0));

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            for (int k = i; k < j; ++k) {
                long long cost = dp[i][k] + dp[k + 1][j] + 1LL * p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    std::string order;
    build_order(1, n, split, order);
    return {dp[1][n], order};
}

int main() {
    std::vector<int> p = {10, 20, 30, 40, 30};
    auto res = matrix_chain_order(p);
    assert(res.min_cost == 30000);
    assert(!res.order.empty());
    return 0;
}
