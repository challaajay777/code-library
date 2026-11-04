// Algorithm: Chinese Postman Problem Undirected Graph
// Purpose: Finds minimum length closed walk visiting every edge at least once via minimum weight odd-degree matching.
// Time Complexity: O(V^3 + 2^K * K^2)
// Space Complexity: O(V^2)
// Preconditions: Connected undirected graph with non-negative edge weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

int chinese_postman(int n, const std::vector<std::vector<int>>& cost) {
    std::vector<int> deg(n, 0);
    int total_weight = 0;
    std::vector<std::vector<int>> dist = cost;

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (int j = i + 1; j < n; ++j) {
            if (cost[i][j] < INF) {
                deg[i]++;
                deg[j]++;
                total_weight += cost[i][j];
            }
        }
    }

    // Floyd-Warshall for all pairs shortest paths
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    std::vector<int> odds;
    for (int i = 0; i < n; ++i) if (deg[i] % 2 != 0) odds.push_back(i);

    int m = odds.size();
    if (m == 0) return total_weight;

    int total_states = 1 << m;
    std::vector<int> dp(total_states, INF);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == INF) continue;
        int p1 = -1;
        for (int i = 0; i < m; ++i) {
            if (!(mask & (1 << i))) { p1 = i; break; }
        }
        if (p1 == -1) continue;

        for (int p2 = p1 + 1; p2 < m; ++p2) {
            if (!(mask & (1 << p2))) {
                int next_mask = mask | (1 << p1) | (1 << p2);
                dp[next_mask] = std::min(dp[next_mask], dp[mask] + dist[odds[p1]][odds[p2]]);
            }
        }
    }
    return total_weight + dp[total_states - 1];
}

int main() {
    int n = 4;
    const int INF = 1e9;
    std::vector<std::vector<int>> cost(n, std::vector<int>(n, INF));
    cost[0][1] = cost[1][0] = 3;
    cost[1][2] = cost[2][1] = 4;
    cost[2][3] = cost[3][2] = 5;
    cost[3][0] = cost[0][3] = 6;
    cost[0][2] = cost[2][0] = 7;

    int res = chinese_postman(n, cost);
    assert(res > 0);
    return 0;
}
