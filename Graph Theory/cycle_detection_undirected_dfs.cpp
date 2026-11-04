// Algorithm: Undirected Cycle Detection with Path Extraction
// Purpose: Detects a cycle in an undirected graph and extracts the sequence of vertices forming the cycle.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Undirected graph without multi-edges.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

bool dfs_undirected(int u, int p, const std::vector<std::vector<int>>& adj,
                    std::vector<bool>& visited, std::vector<int>& parent,
                    int& cycle_start, int& cycle_end) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (visited[v]) {
            cycle_start = v;
            cycle_end = u;
            return true;
        }
        parent[v] = u;
        if (dfs_undirected(v, u, adj, visited, parent, cycle_start, cycle_end)) {
            return true;
        }
    }
    return false;
}

std::vector<int> find_cycle_undirected(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);
    int cycle_start = -1, cycle_end = -1;

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dfs_undirected(i, -1, adj, visited, parent, cycle_start, cycle_end)) {
            break;
        }
    }

    if (cycle_start == -1) return {};
    std::vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int cur = cycle_end; cur != cycle_start; cur = parent[cur]) {
        cycle.push_back(cur);
    }
    cycle.push_back(cycle_start);
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {0, 2};
    adj[2] = {0, 1, 3};
    adj[3] = {2};

    auto cycle = find_cycle_undirected(n, adj);
    assert(!cycle.empty());
    assert(cycle.front() == cycle.back());
    return 0;
}
