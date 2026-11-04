// Algorithm: Undirected Eulerian Circuit Hierholzer
// Purpose: Finds an Eulerian circuit in an undirected graph where every vertex has even degree.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph with all degrees even.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct EdgeRef {
    int to, id;
};

std::vector<int> eulerian_circuit_undirected(int n, const std::vector<std::pair<int, int>>& edges) {
    int m = edges.size();
    std::vector<std::vector<EdgeRef>> adj(n);
    for (int i = 0; i < m; ++i) {
        adj[edges[i].first].push_back({edges[i].second, i});
        adj[edges[i].second].push_back({edges[i].first, i});
    }

    for (int i = 0; i < n; ++i) {
        if (adj[i].size() % 2 != 0) return {};
    }

    std::vector<bool> used(m, false);
    std::vector<int> st = {0}, circuit;

    while (!st.empty()) {
        int u = st.back();
        while (!adj[u].empty() && used[adj[u].back().id]) {
            adj[u].pop_back();
        }
        if (!adj[u].empty()) {
            auto [v, id] = adj[u].back();
            adj[u].pop_back();
            used[id] = true;
            st.push_back(v);
        } else {
            circuit.push_back(u);
            st.pop_back();
        }
    }
    if ((int)circuit.size() != m + 1) return {};
    return circuit;
}

int main() {
    int n = 3;
    std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}};
    auto circuit = eulerian_circuit_undirected(n, edges);
    assert((int)circuit.size() == 4);
    return 0;
}
