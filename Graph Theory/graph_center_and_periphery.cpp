// Algorithm: Graph Center and Periphery
// Purpose: Calculates vertex eccentricities to identify the center (min eccentricity) and periphery (max eccentricity).
// Time Complexity: O(V * (V + E))
// Space Complexity: O(V)
// Preconditions: Connected unweighted graph.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct GraphExtrema {
    int radius, diameter;
    std::vector<int> center, periphery;
};

GraphExtrema find_center_and_periphery(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> ecc(n, 0);
    for (int s = 0; s < n; ++s) {
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        dist[s] = 0;
        q.push(s);
        int max_d = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            max_d = std::max(max_d, dist[u]);
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        ecc[s] = max_d;
    }

    int rad = *std::min_element(ecc.begin(), ecc.end());
    int diam = *std::max_element(ecc.begin(), ecc.end());
    std::vector<int> center, periphery;
    for (int i = 0; i < n; ++i) {
        if (ecc[i] == rad) center.push_back(i);
        if (ecc[i] == diam) periphery.push_back(i);
    }
    return {rad, diam, center, periphery};
}

int main() {
    // Path graph 0-1-2-3-4
    int n = 5;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1, 3}; adj[3] = {2, 4}; adj[4] = {3};

    auto res = find_center_and_periphery(n, adj);
    assert(res.radius == 2);
    assert(res.diameter == 4);
    assert(res.center == std::vector<int>({2}));
    return 0;
}
