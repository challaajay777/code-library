// Algorithm: Boolean Parenthesization DP
// Purpose: Counts the number of ways to parenthesize a boolean expression with '&', '|', '^' to evaluate to true.
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: Alternating string of operands ('T', 'F') and operators ('&', '|', '^').

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

long long count_boolean_ways(const std::string& symbols, const std::string& operators) {
    static const int MOD = 1000000007;
    int n = symbols.size();
    std::vector<std::vector<long long>> T(n, std::vector<long long>(n, 0));
    std::vector<std::vector<long long>> F(n, std::vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) {
        T[i][i] = (symbols[i] == 'T') ? 1 : 0;
        F[i][i] = (symbols[i] == 'F') ? 1 : 0;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                long long total_ik = (T[i][k] + F[i][k]) % MOD;
                long long total_kj = (T[k + 1][j] + F[k + 1][j]) % MOD;
                long long total = (total_ik * total_kj) % MOD;

                char op = operators[k];
                if (op == '&') {
                    long long t = (T[i][k] * T[k + 1][j]) % MOD;
                    T[i][j] = (T[i][j] + t) % MOD;
                    F[i][j] = (F[i][j] + total - t + MOD) % MOD;
                } else if (op == '|') {
                    long long f = (F[i][k] * F[k + 1][j]) % MOD;
                    F[i][j] = (F[i][j] + f) % MOD;
                    T[i][j] = (T[i][j] + total - f + MOD) % MOD;
                } else if (op == '^') {
                    long long t = (T[i][k] * F[k + 1][j] + F[i][k] * T[k + 1][j]) % MOD;
                    T[i][j] = (T[i][j] + t) % MOD;
                    F[i][j] = (F[i][j] + total - t + MOD) % MOD;
                }
            }
        }
    }
    return T[0][n - 1];
}

int main() {
    std::string sym = "TTFT";
    std::string ops = "|&^";
    assert(count_boolean_ways(sym, ops) == 4);
    return 0;
}
