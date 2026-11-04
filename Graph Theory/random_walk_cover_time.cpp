// Algorithm: Random Walk Cover Time Simulation
// Purpose: Simulates random walk to measure expected number of steps to visit all vertices.
// Time Complexity: O(CoverTime)
// Space Complexity: O(V)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <random>
#include <cassert>

int random_walk_cover(int n, const std::vector<std::vector<int>>& adj, std::mt19937& rng) {
    std::vector<bool> visited(n, false);
    int count = 1;
    visited[0] = true;
    int cur = 0, steps = 0;

    while (count < n) {
        steps++;
        std::uniform_int_distribution<int> dist(0, adj[cur].size() - 1);
        cur = adj[cur][dist(rng)];
        if (!visited[cur]) {
            visited[cur] = true;
            count++;
        }
    }
    return steps;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 2}; adj[2] = {0, 1};
    std::mt19937 rng(42);
    int steps = random_walk_cover(n, adj, rng);
    assert(steps >= 2);
    return 0;
}
