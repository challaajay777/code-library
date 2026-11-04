import os

DIR = "Dynamic Programming"
os.makedirs(DIR, exist_ok=True)

implementations = [
    {
        "filename": "lcs_full_reconstruction.cpp",
        "algorithm": "Longest Common Subsequence with Full Reconstruction",
        "purpose": "Computes the LCS length of two sequences and reconstructs the lexicographically first LCS string.",
        "time": "O(N * M)",
        "space": "O(N * M)",
        "preconditions": "Sequences of elements with equality comparison.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::string lcs_reconstruct(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }
    std::string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res.push_back(a[i - 1]);
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    std::string a = "ABCBDAB", b = "BDCABA";
    std::string lcs = lcs_reconstruct(a, b);
    assert((int)lcs.size() == 4);
    assert(lcs == "BDAB" || lcs == "BCBA" || lcs == "BCAB");
    return 0;
}
"""
    },
    {
        "filename": "edit_distance_levenshtein.cpp",
        "algorithm": "Levenshtein Edit Distance with Operation Alignment Trace",
        "purpose": "Finds minimum insertion, deletion, and replacement operations between two strings and reconstructs the trace.",
        "time": "O(N * M)",
        "space": "O(N * M)",
        "preconditions": "Strings of comparable characters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "longest_palindromic_subsequence_dp.cpp",
        "algorithm": "Longest Palindromic Subsequence DP with Reconstruction",
        "purpose": "Computes the maximum length palindromic subsequence and reconstructs the palindromic string.",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "String of length >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::string lps_reconstruct(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = (len == 2) ? 2 : dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    std::string left, right;
    int i = 0, j = n - 1;
    while (i <= j) {
        if (i == j) {
            left.push_back(s[i]);
            break;
        }
        if (s[i] == s[j]) {
            left.push_back(s[i]);
            right.push_back(s[j]);
            ++i; --j;
        } else if (dp[i + 1][j] >= dp[i][j - 1]) {
            ++i;
        } else {
            --j;
        }
    }
    std::reverse(right.begin(), right.end());
    return left + right;
}

int main() {
    std::string s = "bbbab";
    std::string lps = lps_reconstruct(s);
    assert((int)lps.size() == 4);
    assert(lps == "bbbb");
    return 0;
}
"""
    },
    {
        "filename": "matrix_chain_multiplication.cpp",
        "algorithm": "Matrix Chain Multiplication with Optimal Parenthesization",
        "purpose": "Finds minimum scalar multiplications to multiply a chain of matrices and outputs parenthesized form.",
        "time": "O(N^3)",
        "space": "O(N^2)",
        "preconditions": "Dimensions array p of size n+1 for n matrices, where matrix i has dimensions p[i-1] x p[i].",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "stone_game_minimax_interval.cpp",
        "algorithm": "Stone Game Interval DP (Minimax Game Theory)",
        "purpose": "Computes maximum score difference between first and second player taking from ends of array.",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "Array of positive integers representing stone piles.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long stone_game_difference(const std::vector<int>& piles) {
    int n = piles.size();
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = piles[i];

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = std::max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> piles = {5, 3, 4, 5};
    assert(stone_game_difference(piles) > 0);
    return 0;
}
"""
    },
    {
        "filename": "boolean_parenthesization.cpp",
        "algorithm": "Boolean Parenthesization DP",
        "purpose": "Counts the number of ways to parenthesize a boolean expression with '&', '|', '^' to evaluate to true.",
        "time": "O(N^3)",
        "space": "O(N^2)",
        "preconditions": "Alternating string of operands ('T', 'F') and operators ('&', '|', '^').",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "coin_change_minimum_coins.cpp",
        "algorithm": "Coin Change Minimum Coins with Combination Reconstruction",
        "purpose": "Finds the minimum number of coins needed to make amount V and reconstructs the used coin denominations.",
        "time": "O(N * V)",
        "space": "O(V)",
        "preconditions": "Positive integer coin values, non-negative target amount V.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct CoinResult {
    int min_coins;
    std::vector<int> coins_used;
};

CoinResult min_coin_change(const std::vector<int>& coins, int target) {
    const int INF = 1e9;
    std::vector<int> dp(target + 1, INF);
    std::vector<int> parent(target + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= target; ++i) {
        for (int c : coins) {
            if (i >= c && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
                parent[i] = c;
            }
        }
    }

    if (dp[target] >= INF) return {-1, {}};
    std::vector<int> used;
    int cur = target;
    while (cur > 0) {
        used.push_back(parent[cur]);
        cur -= parent[cur];
    }
    return {dp[target], used};
}

int main() {
    std::vector<int> coins = {1, 2, 5};
    auto res = min_coin_change(coins, 11);
    assert(res.min_coins == 3); // 5 + 5 + 1
    int sum = 0;
    for (int c : res.coins_used) sum += c;
    assert(sum == 11);
    return 0;
}
"""
    },
    {
        "filename": "coin_change_total_ways.cpp",
        "algorithm": "Coin Change Total Combinations DP",
        "purpose": "Calculates total number of unordered combinations to make target amount with given coins.",
        "time": "O(N * V)",
        "space": "O(V)",
        "preconditions": "Positive integer coin values, non-negative target amount V.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

long long total_coin_combinations(const std::vector<int>& coins, int target) {
    std::vector<long long> dp(target + 1, 0);
    dp[0] = 1;
    for (int c : coins) {
        for (int i = c; i <= target; ++i) {
            dp[i] += dp[i - c];
        }
    }
    return dp[target];
}

int main() {
    std::vector<int> coins = {1, 2, 5};
    // 5 can be made as: {5}, {2,2,1}, {2,1,1,1}, {1,1,1,1,1} -> 4 ways
    assert(total_coin_combinations(coins, 5) == 4);
    return 0;
}
"""
    },
    {
        "filename": "subset_sum_decision_and_reconstruct.cpp",
        "algorithm": "Subset Sum Decision and Subset Reconstruction",
        "purpose": "Determines if a subset exists summing to target and reconstructs the subset elements.",
        "time": "O(N * S)",
        "space": "O(N * S)",
        "preconditions": "Non-negative array elements, target >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct SubsetSumResult {
    bool possible;
    std::vector<int> subset;
};

SubsetSumResult find_subset_sum(const std::vector<int>& nums, int target) {
    int n = nums.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
        int val = nums[i - 1];
        for (int s = 0; s <= target; ++s) {
            dp[i][s] = dp[i - 1][s];
            if (s >= val && dp[i - 1][s - val]) {
                dp[i][s] = true;
            }
        }
    }

    if (!dp[n][target]) return {false, {}};

    std::vector<int> res;
    int s = target;
    for (int i = n; i > 0 && s > 0; --i) {
        int val = nums[i - 1];
        if (s >= val && dp[i - 1][s - val]) {
            res.push_back(val);
            s -= val;
        }
    }
    return {true, res};
}

int main() {
    std::vector<int> nums = {3, 34, 4, 12, 5, 2};
    auto res = find_subset_sum(nums, 9);
    assert(res.possible);
    int sum = 0;
    for (int x : res.subset) sum += x;
    assert(sum == 9);
    return 0;
}
"""
    },
    {
        "filename": "target_sum_ways.cpp",
        "algorithm": "Target Sum Ways via Subset Sum Reduction",
        "purpose": "Calculates number of ways to assign '+' and '-' to elements such that total sum equals target.",
        "time": "O(N * Sum)",
        "space": "O(Sum)",
        "preconditions": "Array of non-negative integers, target value.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <cassert>

long long count_target_sum_ways(const std::vector<int>& nums, int target) {
    long long total_sum = std::accumulate(nums.begin(), nums.end(), 0LL);
    if (std::abs(target) > total_sum) return 0;
    if ((total_sum + target) % 2 != 0) return 0;

    long long s1 = (total_sum + target) / 2;
    std::vector<long long> dp(s1 + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
        for (long long s = s1; s >= num; --s) {
            dp[s] += dp[s - num];
        }
    }
    return dp[s1];
}

int main() {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    assert(count_target_sum_ways(nums, 3) == 5);
    return 0;
}
"""
    },
    {
        "filename": "count_unique_bst_catalan_dp.cpp",
        "algorithm": "Unique BST Count via Catalan DP",
        "purpose": "Computes the number of structurally unique binary search trees that can store keys 1..n.",
        "time": "O(N^2)",
        "space": "O(N)",
        "preconditions": "n >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

long long count_unique_bst(int n) {
    if (n <= 1) return 1;
    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }
    return dp[n];
}

int main() {
    assert(count_unique_bst(0) == 1);
    assert(count_unique_bst(3) == 5);
    assert(count_unique_bst(4) == 14);
    assert(count_unique_bst(5) == 42);
    return 0;
}
"""
    },
    {
        "filename": "longest_path_dag_dp.cpp",
        "algorithm": "Longest Path in DAG via Topological Order DP",
        "purpose": "Finds the maximum weight path in a Directed Acyclic Graph and reconstructs vertex sequence.",
        "time": "O(V + E)",
        "space": "O(V + E)",
        "preconditions": "Graph is a Directed Acyclic Graph (DAG).",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct Edge {
    int to, weight;
};

struct DAGPathResult {
    long long max_distance;
    std::vector<int> path;
};

DAGPathResult longest_path_dag(int n, const std::vector<std::vector<Edge>>& adj) {
    std::vector<int> in_degree(n, 0);
    for (int u = 0; u < n; ++u) {
        for (const auto& e : adj[u]) in_degree[e.to]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    std::vector<long long> dp(n, 0);
    std::vector<int> parent(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& e : adj[u]) {
            if (dp[u] + e.weight > dp[e.to]) {
                dp[e.to] = dp[u] + e.weight;
                parent[e.to] = u;
            }
            if (--in_degree[e.to] == 0) {
                q.push(e.to);
            }
        }
    }

    int best_end = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[i] > dp[best_end]) best_end = i;
    }

    std::vector<int> path;
    int cur = best_end;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    std::reverse(path.begin(), path.end());
    return {dp[best_end], path};
}

int main() {
    int n = 4;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 3});
    adj[0].push_back({2, 2});
    adj[1].push_back({3, 4});
    adj[2].push_back({3, 1});

    auto res = longest_path_dag(n, adj);
    assert(res.max_distance == 7); // 0 -> 1 -> 3
    assert(res.path == std::vector<int>({0, 1, 3}));
    return 0;
}
"""
    },
    {
        "filename": "tree_max_independent_set.cpp",
        "algorithm": "Maximum Independent Set on Trees via Post-Order DP",
        "purpose": "Finds the maximum weight subset of tree vertices with no adjacent edges.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Connected tree of n vertices.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void dfs_mis(int u, int p, const std::vector<std::vector<int>>& adj,
             const std::vector<int>& weights,
             std::vector<long long>& dp_incl,
             std::vector<long long>& dp_excl) {
    dp_incl[u] = weights[u];
    dp_excl[u] = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_mis(v, u, adj, weights, dp_incl, dp_excl);
            dp_incl[u] += dp_excl[v];
            dp_excl[u] += std::max(dp_incl[v], dp_excl[v]);
        }
    }
}

long long max_independent_set(int n, const std::vector<std::vector<int>>& adj, const std::vector<int>& weights) {
    std::vector<long long> dp_incl(n, 0), dp_excl(n, 0);
    dfs_mis(0, -1, adj, weights, dp_incl, dp_excl);
    return std::max(dp_incl[0], dp_excl[0]);
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[0].push_back(3); adj[3].push_back(0);
    std::vector<int> weights = {10, 5, 5, 5};

    // Include 0: weight 10. Exclude 0: include 1, 2, 3 -> weight 15.
    assert(max_independent_set(n, adj, weights) == 15);
    return 0;
}
"""
    },
    {
        "filename": "tree_vertex_cover.cpp",
        "algorithm": "Minimum Vertex Cover on Trees DP",
        "purpose": "Finds the minimum number of vertices such that every edge is incident to at least one chosen vertex.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Connected tree of n vertices.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void dfs_vc(int u, int p, const std::vector<std::vector<int>>& adj,
            std::vector<int>& dp_incl, std::vector<int>& dp_excl) {
    dp_incl[u] = 1;
    dp_excl[u] = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_vc(v, u, adj, dp_incl, dp_excl);
            dp_incl[u] += std::min(dp_incl[v], dp_excl[v]);
            dp_excl[u] += dp_incl[v];
        }
    }
}

int min_vertex_cover(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> dp_incl(n, 0), dp_excl(n, 0);
    dfs_vc(0, -1, adj, dp_incl, dp_excl);
    return std::min(dp_incl[0], dp_excl[0]);
}

int main() {
    // Star tree: center 0 with leaves 1, 2, 3
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[0].push_back(3); adj[3].push_back(0);

    // Minimum vertex cover is simply node 0 (size 1)
    assert(min_vertex_cover(n, adj) == 1);
    return 0;
}
"""
    },
    {
        "filename": "tree_dominating_set.cpp",
        "algorithm": "Minimum Dominating Set on Trees DP",
        "purpose": "Finds the minimum subset of tree vertices such that every vertex is chosen or adjacent to a chosen vertex.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Connected tree of n vertices.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e8;

void dfs_ds(int u, int p, const std::vector<std::vector<int>>& adj,
            std::vector<int>& dp0, std::vector<int>& dp1, std::vector<int>& dp2) {
    // dp0: u is chosen in the dominating set
    // dp1: u is not chosen, but covered by at least one child
    // dp2: u is not chosen, not covered by any child (relies on parent to cover it)
    dp0[u] = 1;
    dp1[u] = 0;
    dp2[u] = 0;

    int sum_min = 0;
    int min_diff = INF;
    bool has_child = false;

    for (int v : adj[u]) {
        if (v != p) {
            has_child = true;
            dfs_ds(v, u, adj, dp0, dp1, dp2);
            dp0[u] += std::min({dp0[v], dp1[v], dp2[v]});
            dp2[u] += dp1[v];

            int best_v = std::min(dp0[v], dp1[v]);
            sum_min += best_v;
            min_diff = std::min(min_diff, dp0[v] - best_v);
        }
    }

    if (!has_child) {
        dp1[u] = INF;
    } else {
        dp1[u] = sum_min + std::max(0, min_diff);
    }
}

int min_dominating_set(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> dp0(n, 0), dp1(n, 0), dp2(n, 0);
    dfs_ds(0, -1, adj, dp0, dp1, dp2);
    return std::min(dp0[0], dp1[0]);
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[0].push_back(3); adj[3].push_back(0);

    // Center dominates all 3 leaves
    assert(min_dominating_set(n, adj) == 1);
    return 0;
}
"""
    },
    {
        "filename": "tree_knapsack_subtree_dp.cpp",
        "algorithm": "Tree Knapsack Subtree-Bounded DP",
        "purpose": "Solves knapsack optimization on a tree where choosing a node requires choosing its parent.",
        "time": "O(N * W)",
        "space": "O(N * W)",
        "preconditions": "Rooted tree, item weights >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreeKnapsack {
    int n, W;
    std::vector<std::vector<int>> adj;
    std::vector<int> weight, value, sz;
    std::vector<std::vector<long long>> dp;

    TreeKnapsack(int n, int W) : n(n), W(W), adj(n), weight(n), value(n), sz(n, 0), dp(n, std::vector<long long>(W + 1, 0)) {}

    void dfs(int u, int p) {
        sz[u] = weight[u];
        if (weight[u] <= W) dp[u][weight[u]] = value[u];

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                std::vector<long long> next_dp = dp[u];
                for (int w1 = 0; w1 <= std::min(W, sz[u]); ++w1) {
                    if (dp[u][w1] == 0 && w1 != weight[u]) continue;
                    for (int w2 = 0; w1 + w2 <= W && w2 <= sz[v]; ++w2) {
                        next_dp[w1 + w2] = std::max(next_dp[w1 + w2], dp[u][w1] + dp[v][w2]);
                    }
                }
                dp[u] = next_dp;
                sz[u] += sz[v];
            }
        }
    }

    long long solve(int root = 0) {
        dfs(root, -1);
        long long ans = 0;
        for (int w = 0; w <= W; ++w) ans = std::max(ans, dp[root][w]);
        return ans;
    }
};

int main() {
    TreeKnapsack tk(3, 4);
    tk.adj[0].push_back(1);
    tk.adj[0].push_back(2);
    tk.weight = {2, 1, 1};
    tk.value = {5, 4, 3};

    // Capacity 4: root weight 2 (value 5) + child 1 weight 1 (value 4) + child 2 weight 1 (val 3) = total weight 4, val 12
    assert(tk.solve(0) == 12);
    return 0;
}
"""
    },
    {
        "filename": "broken_profile_domino_tiling.cpp",
        "algorithm": "Broken Profile (Plug) DP for Domino Tiling",
        "purpose": "Calculates the exact number of ways to tile an N x M grid with 2x1 dominoes.",
        "time": "O(N * M * 2^M)",
        "space": "O(2^M)",
        "preconditions": "1 <= N, M <= 16 with N * M even.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

long long domino_tiling_ways(int n, int m) {
    if (m > n) std::swap(n, m);
    if ((n * m) % 2 != 0) return 0;

    int mask_limit = 1 << m;
    std::vector<long long> dp(mask_limit, 0);
    dp[0] = 1;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            std::vector<long long> next_dp(mask_limit, 0);
            for (int mask = 0; mask < mask_limit; ++mask) {
                if (dp[mask] == 0) continue;
                if (mask & (1 << c)) {
                    // Current cell is already occupied by domino from cell above
                    next_dp[mask ^ (1 << c)] += dp[mask];
                } else {
                    // Try placing vertical domino (covers (r, c) and (r+1, c))
                    if (r + 1 < n) {
                        next_dp[mask | (1 << c)] += dp[mask];
                    }
                    // Try placing horizontal domino (covers (r, c) and (r, c+1))
                    if (c + 1 < m && !(mask & (1 << (c + 1)))) {
                        next_dp[mask | (1 << (c + 1))] += dp[mask];
                    }
                }
            }
            dp = next_dp;
        }
    }
    return dp[0];
}

int main() {
    assert(domino_tiling_ways(2, 2) == 2);
    assert(domino_tiling_ways(2, 3) == 3);
    assert(domino_tiling_ways(4, 4) == 36);
    return 0;
}
"""
    },
    {
        "filename": "traveling_salesperson_bitmask.cpp",
        "algorithm": "Traveling Salesperson Problem via Held-Karp Bitmask DP",
        "purpose": "Solves the exact metric/general TSP minimum tour cost with vertex sequence reconstruction.",
        "time": "O(2^N * N^2)",
        "space": "O(2^N * N)",
        "preconditions": "N <= 20, complete directed or undirected cost matrix.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

struct TSPResult {
    int min_cost;
    std::vector<int> tour;
};

TSPResult solve_tsp(int n, const std::vector<std::vector<int>>& cost) {
    int total_states = 1 << n;
    std::vector<std::vector<int>> dp(total_states, std::vector<int>(n, INF));
    std::vector<std::vector<int>> parent(total_states, std::vector<int>(n, -1));

    dp[1][0] = 0; // Start at vertex 0

    for (int mask = 1; mask < total_states; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v))) {
                    int next_mask = mask | (1 << v);
                    int new_cost = dp[mask][u] + cost[u][v];
                    if (new_cost < dp[next_mask][v]) {
                        dp[next_mask][v] = new_cost;
                        parent[next_mask][v] = u;
                    }
                }
            }
        }
    }

    int best_last = -1;
    int min_total = INF;
    int all_mask = total_states - 1;

    for (int u = 1; u < n; ++u) {
        if (dp[all_mask][u] != INF && dp[all_mask][u] + cost[u][0] < min_total) {
            min_total = dp[all_mask][u] + cost[u][0];
            best_last = u;
        }
    }

    std::vector<int> tour;
    int cur_mask = all_mask;
    int cur_node = best_last;
    while (cur_node != -1) {
        tour.push_back(cur_node);
        int p = parent[cur_mask][cur_node];
        cur_mask ^= (1 << cur_node);
        cur_node = p;
    }
    std::reverse(tour.begin(), tour.end());
    tour.push_back(0); // return to start
    return {min_total, tour};
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    auto res = solve_tsp(n, cost);
    // Optimal tour: 0 -> 1 -> 3 -> 2 -> 0 with cost 10 + 25 + 30 + 15 = 80
    assert(res.min_cost == 80);
    assert((int)res.tour.size() == 5);
    return 0;
}
"""
    },
    {
        "filename": "hamiltonian_path_bitmask.cpp",
        "algorithm": "Hamiltonian Path Check and Extraction via Bitmask DP",
        "purpose": "Checks if a directed graph contains a path visiting every vertex exactly once and extracts it.",
        "time": "O(2^N * N^2)",
        "space": "O(2^N * N)",
        "preconditions": "N <= 20, directed graph adjacency matrix.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct HamResult {
    bool exists;
    std::vector<int> path;
};

HamResult find_hamiltonian_path(int n, const std::vector<std::vector<bool>>& adj) {
    int total = 1 << n;
    std::vector<std::vector<bool>> dp(total, std::vector<bool>(n, false));
    std::vector<std::vector<int>> parent(total, std::vector<int>(n, -1));

    for (int i = 0; i < n; ++i) dp[1 << i][i] = true;

    for (int mask = 1; mask < total; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!dp[mask][u]) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v)) && adj[u][v]) {
                    dp[mask | (1 << v)][v] = true;
                    parent[mask | (1 << v)][v] = u;
                }
            }
        }
    }

    int full_mask = total - 1;
    for (int i = 0; i < n; ++i) {
        if (dp[full_mask][i]) {
            std::vector<int> path;
            int cur_mask = full_mask, cur_node = i;
            while (cur_node != -1) {
                path.push_back(cur_node);
                int p = parent[cur_mask][cur_node];
                cur_mask ^= (1 << cur_node);
                cur_node = p;
            }
            std::reverse(path.begin(), path.end());
            return {true, path};
        }
    }
    return {false, {}};
}

int main() {
    int n = 4;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    adj[0][1] = adj[1][2] = adj[2][3] = true;

    auto res = find_hamiltonian_path(n, adj);
    assert(res.exists);
    assert(res.path == std::vector<int>({0, 1, 2, 3}));
    return 0;
}
"""
    },
    {
        "filename": "minimum_cost_bipartite_matching_bitmask.cpp",
        "algorithm": "Min-Cost Bipartite Matching via Bitmask DP",
        "purpose": "Computes exact minimum cost perfect matching for bipartite graph with N elements per side.",
        "time": "O(2^N * N)",
        "space": "O(2^N)",
        "preconditions": "N <= 20, N x N edge weight matrix.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

int min_cost_bipartite_matching(int n, const std::vector<std::vector<int>>& cost) {
    int total_states = 1 << n;
    std::vector<int> dp(total_states, INF);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == INF) continue;
        int i = __builtin_popcount(mask); // next worker to assign
        if (i >= n) break;
        for (int j = 0; j < n; ++j) {
            if (!(mask & (1 << j))) {
                int next_mask = mask | (1 << j);
                dp[next_mask] = std::min(dp[next_mask], dp[mask] + cost[i][j]);
            }
        }
    }
    return dp[total_states - 1];
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> cost = {
        {9, 2, 7},
        {6, 4, 3},
        {5, 8, 1}
    };
    // Match worker 0 -> job 1 (2), worker 1 -> job 0 (6), worker 2 -> job 2 (1) = 9 total
    assert(min_cost_bipartite_matching(n, cost) == 9);
    return 0;
}
"""
    },
    {
        "filename": "knuth_optimization_dp.cpp",
        "algorithm": "Knuth Optimization for Interval DP",
        "purpose": "Accelerates interval dynamic programming satisfying the quadrangle inequality from O(N^3) to O(N^2).",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "Cost function satisfies quadrangle inequality and monotonicity on intervals.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>
#include <climits>

long long knuth_optimal_merge(const std::vector<int>& weights) {
    int n = weights.size();
    std::vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + weights[i];

    auto sum = [&](int i, int j) {
        return pref[j + 1] - pref[i];
    };

    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));
    std::vector<std::vector<int>> opt(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) opt[i][i] = i;

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            int opt_start = opt[i][j - 1];
            int opt_end = (j > i + 1) ? opt[i + 1][j] : j - 1;

            for (int k = opt_start; k <= opt_end; ++k) {
                long long cur = dp[i][k] + dp[k + 1][j] + sum(i, j);
                if (cur < dp[i][j]) {
                    dp[i][j] = cur;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> weights = {3, 4, 2, 1, 7};
    long long cost = knuth_optimal_merge(weights);
    assert(cost > 0);
    return 0;
}
"""
    },
    {
        "filename": "monotonic_queue_dp_optimization.cpp",
        "algorithm": "Monotonic Queue 1D DP Optimization",
        "purpose": "Optimizes DP transitions over sliding window bounds [i - k, i - 1] in strict O(N) total time.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Array of values, jump length k >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

long long max_score_jump(const std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<long long> dp(n, 0);
    dp[0] = nums[0];

    std::deque<int> dq;
    dq.push_back(0);

    for (int i = 1; i < n; ++i) {
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        dp[i] = dp[dq.front()] + nums[i];

        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    return dp[n - 1];
}

int main() {
    std::vector<int> nums = {1, -1, -2, 4, -7, 3};
    // Jump at most 2 steps: 0 -> 1 -> 3 -> 5: 1 + (-1) + 4 + 3 = 7
    assert(max_score_jump(nums, 2) == 7);
    return 0;
}
"""
    },
    {
        "filename": "slope_trick_convex_dp.cpp",
        "algorithm": "Slope Trick for Piecewise Linear Convex Optimization",
        "purpose": "Optimizes functions maintaining slope change points using dual priority queues.",
        "time": "O(N log N)",
        "space": "O(N)",
        "preconditions": "Convex objective with unit slope changes.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <cmath>

long long make_non_decreasing(const std::vector<int>& a) {
    // Minimum operations to make array non-decreasing with absolute deviation cost
    std::priority_queue<int> pq; // max-heap storing slope changing points
    long long cost = 0;

    for (int x : a) {
        if (!pq.empty() && pq.top() > x) {
            cost += pq.top() - x;
            pq.pop();
            pq.push(x);
        }
        pq.push(x);
    }
    return cost;
}

int main() {
    std::vector<int> a = {5, 4, 3, 2, 1};
    // Make non-decreasing: minimum modifications = 6
    assert(make_non_decreasing(a) == 6);
    return 0;
}
"""
    },
    {
        "filename": "alien_trick_wqs_binary_search.cpp",
        "algorithm": "Aliens Trick (WQS Binary Search on Cost Multiplier)",
        "purpose": "Removes dimension constraint (e.g. choose exactly K elements) via convex Lagrange penalty.",
        "time": "O(N log(Range))",
        "space": "O(N)",
        "preconditions": "Objective function is convex/concave with respect to k.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct WQSCheck {
    long long max_val;
    int count;
};

WQSCheck check(const std::vector<int>& prices, long long penalty) {
    int n = prices.size();
    long long hold = -prices[0] - penalty;
    long long not_hold = 0;
    int hold_count = 1;
    int not_hold_count = 0;

    for (int i = 1; i < n; ++i) {
        if (hold + prices[i] > not_hold) {
            not_hold = hold + prices[i];
            not_hold_count = hold_count;
        }
        if (not_hold - prices[i] - penalty > hold) {
            hold = not_hold - prices[i] - penalty;
            hold_count = not_hold_count + 1;
        }
    }
    return {not_hold, not_hold_count};
}

long long max_profit_k_transactions(const std::vector<int>& prices, int k) {
    int n = prices.size();
    if (n <= 1 || k == 0) return 0;
    if (k >= n / 2) {
        long long sum = 0;
        for (int i = 1; i < n; ++i) if (prices[i] > prices[i - 1]) sum += prices[i] - prices[i - 1];
        return sum;
    }

    long long low = 0, high = 1e9, ans = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        auto res = check(prices, mid);
        if (res.count >= k) {
            ans = res.max_val + mid * k;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    std::vector<int> prices = {3, 2, 6, 5, 0, 3};
    assert(max_profit_k_transactions(prices, 2) == 7); // Buy at 2, sell at 6; buy at 0, sell at 3
    return 0;
}
"""
    },
    {
        "filename": "longest_alternating_subsequence.cpp",
        "algorithm": "Longest Alternating Subsequence DP",
        "purpose": "Finds the length of the longest subsequence where differences between consecutive elements alternate sign.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "Array of integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int longest_alternating_subsequence(const std::vector<int>& a) {
    int n = a.size();
    if (n <= 1) return n;
    int up = 1, down = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) up = down + 1;
        else if (a[i] < a[i - 1]) down = up + 1;
    }
    return std::max(up, down);
}

int main() {
    std::vector<int> a = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    assert(longest_alternating_subsequence(a) == 7);
    return 0;
}
"""
    },
    {
        "filename": "longest_common_increasing_subsequence.cpp",
        "algorithm": "Longest Common Increasing Subsequence (LCIS)",
        "purpose": "Finds the length of the longest subsequence common to both arrays that is strictly increasing.",
        "time": "O(N * M)",
        "space": "O(M)",
        "preconditions": "Two integer arrays.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int lcis(const std::vector<int>& a, const std::vector<int>& b) {
    int n = a.size(), m = b.size();
    std::vector<int> dp(m, 0);

    for (int i = 0; i < n; ++i) {
        int current_max = 0;
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                dp[j] = std::max(dp[j], current_max + 1);
            }
            if (a[i] > b[j]) {
                current_max = std::max(current_max, dp[j]);
            }
        }
    }
    int ans = 0;
    for (int x : dp) ans = std::max(ans, x);
    return ans;
}

int main() {
    std::vector<int> a = {3, 4, 9, 1};
    std::vector<int> b = {5, 3, 8, 9, 4, 1};
    // LCIS: {3, 9} (len 2)
    assert(lcis(a, b) == 2);
    return 0;
}
"""
    },
    {
        "filename": "maximum_weight_independent_set_path.cpp",
        "algorithm": "Max Weight Independent Set on Path Graph",
        "purpose": "Computes max weight subset of elements with no two adjacent selected (House Robber problem).",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "Array of non-negative weights.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long max_weight_path_independent_set(const std::vector<int>& weights) {
    long long prev2 = 0, prev1 = 0;
    for (int w : weights) {
        long long cur = std::max(prev1, prev2 + w);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    std::vector<int> weights = {2, 7, 9, 3, 1};
    // Choose 2 + 9 + 1 = 12
    assert(max_weight_path_independent_set(weights) == 12);
    return 0;
}
"""
    },
    {
        "filename": "egg_dropping_puzzle.cpp",
        "algorithm": "Egg Dropping Puzzle DP with Binary Search",
        "purpose": "Finds minimum attempts needed in worst case to find critical floor with K eggs and N floors.",
        "time": "O(K * N)",
        "space": "O(K * N)",
        "preconditions": "k >= 1, n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

int egg_drop(int k, int n) {
    // dp[m][k] = maximum floors that can be checked with m moves and k eggs
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
    int m = 0;
    while (dp[m][k] < n) {
        m++;
        for (int i = 1; i <= k; ++i) {
            dp[m][i] = dp[m - 1][i - 1] + dp[m - 1][i] + 1;
        }
    }
    return m;
}

int main() {
    assert(egg_drop(1, 2) == 2);
    assert(egg_drop(2, 6) == 3);
    assert(egg_drop(3, 14) == 4);
    return 0;
}
"""
    },
    {
        "filename": "burst_balloons_dp.cpp",
        "algorithm": "Burst Balloons Maximum Coins Interval DP",
        "purpose": "Calculates maximum coins obtained by bursting balloons with boundary multipliers.",
        "time": "O(N^3)",
        "space": "O(N^2)",
        "preconditions": "Array of balloon values.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_coins_burst_balloons(const std::vector<int>& nums) {
    std::vector<int> b;
    b.push_back(1);
    for (int x : nums) b.push_back(x);
    b.push_back(1);

    int n = b.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int len = 2; len < n; ++len) {
        for (int i = 0; i < n - len; ++i) {
            int j = i + len;
            for (int k = i + 1; k < j; ++k) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k][j] + b[i] * b[k] * b[j]);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> nums = {3, 1, 5, 8};
    assert(max_coins_burst_balloons(nums) == 167);
    return 0;
}
"""
    },
    {
        "filename": "palindrome_partitioning_min_cuts.cpp",
        "algorithm": "Palindrome Partitioning Minimum Cuts DP",
        "purpose": "Finds minimum cuts needed to partition a string such that every part is a palindrome.",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "Non-empty string.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int min_cut_palindrome(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<bool>> is_pal(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) is_pal[i][i] = true;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                is_pal[i][j] = (len == 2) ? true : is_pal[i + 1][j - 1];
            }
        }
    }

    std::vector<int> dp(n, 0);
    for (int i = 0; i < n; ++i) {
        if (is_pal[0][i]) {
            dp[i] = 0;
        } else {
            dp[i] = i;
            for (int j = 0; j < i; ++j) {
                if (is_pal[j + 1][i]) {
                    dp[i] = std::min(dp[i], dp[j] + 1);
                }
            }
        }
    }
    return dp[n - 1];
}

int main() {
    assert(min_cut_palindrome("aab") == 1); // "aa" | "b"
    assert(min_cut_palindrome("a") == 0);
    assert(min_cut_palindrome("ab") == 1);
    return 0;
}
"""
    },
    {
        "filename": "rod_cutting_maximization.cpp",
        "algorithm": "Rod Cutting Profit Maximization DP",
        "purpose": "Finds the maximum revenue obtainable by cutting up a rod of length n and selling the pieces.",
        "time": "O(N^2)",
        "space": "O(N)",
        "preconditions": "Prices array for lengths 1..n.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_rod_cutting_profit(const std::vector<int>& prices) {
    int n = prices.size();
    std::vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] = std::max(dp[i], dp[i - j] + prices[j - 1]);
        }
    }
    return dp[n];
}

int main() {
    std::vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    assert(max_rod_cutting_profit(prices) == 22);
    return 0;
}
"""
    },
    {
        "filename": "optimal_binary_search_tree.cpp",
        "algorithm": "Optimal Binary Search Tree Interval DP",
        "purpose": "Calculates minimum search cost for binary search tree given key frequencies.",
        "time": "O(N^3)",
        "space": "O(N^2)",
        "preconditions": "Sorted keys and positive frequencies.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <climits>

int optimal_bst_cost(const std::vector<int>& freq) {
    int n = freq.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    std::vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + freq[i];

    auto sum = [&](int i, int j) {
        return pref[j + 1] - pref[i];
    };

    for (int i = 0; i < n; ++i) dp[i][i] = freq[i];

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            int s = sum(i, j);
            for (int r = i; r <= j; ++r) {
                int left = (r > i) ? dp[i][r - 1] : 0;
                int right = (r < j) ? dp[r + 1][j] : 0;
                dp[i][j] = std::min(dp[i][j], left + right + s);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> freq = {34, 8, 50};
    assert(optimal_bst_cost(freq) == 142);
    return 0;
}
"""
    },
    {
        "filename": "shortest_common_supersequence.cpp",
        "algorithm": "Shortest Common Supersequence with Reconstruction",
        "purpose": "Finds the shortest sequence that has both input sequences as subsequences.",
        "time": "O(N * M)",
        "space": "O(N * M)",
        "preconditions": "Strings of valid characters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "wildcard_matching_2d_dp.cpp",
        "algorithm": "Wildcard Pattern Matching 2D DP",
        "purpose": "Matches string against pattern containing '?' (any single character) and '*' (any sequence).",
        "time": "O(N * M)",
        "space": "O(N * M)",
        "preconditions": "String and pattern with ascii characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

bool is_wildcard_match(const std::string& s, const std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= m; ++j) {
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}

int main() {
    assert(is_wildcard_match("aa", "*"));
    assert(!is_wildcard_match("cb", "?a"));
    assert(is_wildcard_match("adceb", "*a*b"));
    return 0;
}
"""
    },
    {
        "filename": "box_stacking_3d_dag.cpp",
        "algorithm": "3D Box Stacking via DAG Dynamic Programming",
        "purpose": "Finds the maximum height of a stack of boxes where each box must have strictly smaller 2D base.",
        "time": "O(N^2)",
        "space": "O(N)",
        "preconditions": "List of 3D box dimensions (length, width, height).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Box {
    int l, w, h;
};

int max_box_stack_height(const std::vector<Box>& boxes) {
    std::vector<Box> rot;
    for (const auto& b : boxes) {
        std::vector<int> d = {b.l, b.w, b.h};
        std::sort(d.begin(), d.end());
        // 3 rotations for each box
        rot.push_back({d[1], d[0], d[2]});
        rot.push_back({d[2], d[0], d[1]});
        rot.push_back({d[2], d[1], d[0]});
    }

    std::sort(rot.begin(), rot.end(), [](const Box& a, const Box& b) {
        return 1LL * a.l * a.w > 1LL * b.l * b.w;
    });

    int m = rot.size();
    std::vector<int> dp(m, 0);
    int ans = 0;

    for (int i = 0; i < m; ++i) {
        dp[i] = rot[i].h;
        for (int j = 0; j < i; ++j) {
            if (rot[i].l < rot[j].l && rot[i].w < rot[j].w) {
                dp[i] = std::max(dp[i], dp[j] + rot[i].h);
            }
        }
        ans = std::max(ans, dp[i]);
    }
    return ans;
}

int main() {
    std::vector<Box> boxes = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};
    assert(max_box_stack_height(boxes) == 60);
    return 0;
}
"""
    },
    {
        "filename": "interleaving_string_dp.cpp",
        "algorithm": "Interleaving String DP Check",
        "purpose": "Determines whether string s3 is formed by an interleaving of strings s1 and s2.",
        "time": "O(N * M)",
        "space": "O(M)",
        "preconditions": "|s1| + |s2| == |s3|.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

bool is_interleave(const std::string& s1, const std::string& s2, const std::string& s3) {
    if (s1.size() + s2.size() != s3.size()) return false;
    int n = s1.size(), m = s2.size();
    std::vector<bool> dp(m + 1, false);

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 && j == 0) {
                dp[j] = true;
            } else if (i == 0) {
                dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
            } else if (j == 0) {
                dp[j] = dp[j] && (s1[i - 1] == s3[i - 1]);
            } else {
                dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                        (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
    }
    return dp[m];
}

int main() {
    assert(is_interleave("aabcc", "dbbca", "aadbbcbcac"));
    assert(!is_interleave("aabcc", "dbbca", "aadbbbaccc"));
    return 0;
}
"""
    },
    {
        "filename": "word_break_dp.cpp",
        "algorithm": "Word Break Problem DP",
        "purpose": "Determines if a string can be segmented into a space-separated sequence of dictionary words.",
        "time": "O(N^2)",
        "space": "O(N + TotalDictChars)",
        "preconditions": "String s and dictionary of non-empty words.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cassert>

bool word_break(const std::string& s, const std::vector<std::string>& dict) {
    std::unordered_set<std::string> word_set(dict.begin(), dict.end());
    int n = s.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && word_set.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

int main() {
    std::vector<std::string> dict = {"apple", "pen"};
    assert(word_break("applepenapple", dict));
    assert(!word_break("catsandog", {"cats", "dog", "sand", "and", "cat"}));
    return 0;
}
"""
    },
    {
        "filename": "partition_equal_subset_sum.cpp",
        "algorithm": "Partition Equal Subset Sum DP",
        "purpose": "Determines whether an array can be partitioned into two subsets with equal sum.",
        "time": "O(N * Sum)",
        "space": "O(Sum)",
        "preconditions": "Positive integer values.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

bool can_partition(const std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;

    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
        for (int s = target; s >= num; --s) {
            dp[s] = dp[s] || dp[s - num];
        }
    }
    return dp[target];
}

int main() {
    assert(can_partition({1, 5, 11, 5}));
    assert(!can_partition({1, 2, 3, 5}));
    return 0;
}
"""
    },
    {
        "filename": "minimum_path_sum_grid.cpp",
        "algorithm": "Minimum Path Sum in Grid DP",
        "purpose": "Finds path from top-left to bottom-right of matrix minimizing sum of cell values.",
        "time": "O(R * C)",
        "space": "O(C)",
        "preconditions": "Grid of non-negative integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int min_path_sum(const std::vector<std::vector<int>>& grid) {
    int r = grid.size(), c = grid[0].size();
    std::vector<int> dp(c, 0);
    dp[0] = grid[0][0];

    for (int j = 1; j < c; ++j) dp[j] = dp[j - 1] + grid[0][j];

    for (int i = 1; i < r; ++i) {
        dp[0] += grid[i][0];
        for (int j = 1; j < c; ++j) {
            dp[j] = std::min(dp[j], dp[j - 1]) + grid[i][j];
        }
    }
    return dp[c - 1];
}

int main() {
    std::vector<std::vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    assert(min_path_sum(grid) == 7); // 1 -> 3 -> 1 -> 1 -> 1
    return 0;
}
"""
    },
    {
        "filename": "cherry_pickup_two_paths.cpp",
        "algorithm": "Cherry Pickup Dual Synchronous Path DP",
        "purpose": "Finds maximum cherries collected by two paths moving simultaneously from (0,0) to (n-1, n-1).",
        "time": "O(N^3)",
        "space": "O(N^2)",
        "preconditions": "Grid where 0 is empty, 1 is cherry, -1 is thorn (obstacle).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int cherry_pickup(const std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
    dp[0][0] = grid[0][0];

    int max_steps = 2 * n - 2;
    for (int step = 1; step <= max_steps; ++step) {
        std::vector<std::vector<int>> next_dp(n, std::vector<int>(n, -1));
        for (int r1 = std::max(0, step - (n - 1)); r1 <= std::min(n - 1, step); ++r1) {
            int c1 = step - r1;
            if (grid[r1][c1] == -1) continue;
            for (int r2 = r1; r2 <= std::min(n - 1, step); ++r2) {
                int c2 = step - r2;
                if (grid[r2][c2] == -1) continue;

                int cherries = (r1 == r2) ? grid[r1][c1] : grid[r1][c1] + grid[r2][c2];
                int prev_max = -1;

                if (r1 > 0 && r2 > 0) prev_max = std::max(prev_max, dp[r1 - 1][r2 - 1]);
                if (r1 > 0 && c2 > 0) prev_max = std::max(prev_max, dp[r1 - 1][r2]);
                if (c1 > 0 && r2 > 0) prev_max = std::max(prev_max, dp[r1][r2 - 1]);
                if (c1 > 0 && c2 > 0) prev_max = std::max(prev_max, dp[r1][r2]);

                if (prev_max != -1) {
                    next_dp[r1][r2] = prev_max + cherries;
                }
            }
        }
        dp = next_dp;
    }
    return std::max(0, dp[n - 1][n - 1]);
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, -1},
        {1, 0, -1},
        {1, 1,  1}
    };
    assert(cherry_pickup(grid) == 5);
    return 0;
}
"""
    }
]

for idx, item in enumerate(implementations, 1):
    path = os.path.join(DIR, item["filename"])
    header = f"""// Algorithm: {item["algorithm"]}
// Purpose: {item["purpose"]}
// Time Complexity: {item["time"]}
// Space Complexity: {item["space"]}
// Preconditions: {item["preconditions"]}

"""
    with open(path, "w", encoding="utf-8") as f:
        f.write(header + item["code"].strip() + "\n")
    print(f"Wrote [{idx}/{len(implementations)}]: {item['filename']}")

print(f"\nBatch 10a (Dynamic Programming) completed: {len(implementations)} implementations written.")
