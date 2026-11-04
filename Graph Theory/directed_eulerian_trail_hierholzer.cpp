// Algorithm: Directed Eulerian Trail via Hierholzer
// Purpose: Finds an Eulerian trail or circuit visiting every directed edge exactly once.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Connected directed graph with valid in/out-degree balance.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

std::vector<int> eulerian_trail_directed(int n, std::vector<std::vector<int>>& adj) {
    std::vector<int> in_deg(n, 0), out_deg(n, 0);
    int total_edges = 0;
    for (int u = 0; u < n; ++u) {
        out_deg[u] = adj[u].size();
        total_edges += out_deg[u];
        for (int v : adj[u]) in_deg[v]++;
    }

    int start_node = 0, start_count = 0, end_count = 0;
    for (int i = 0; i < n; ++i) {
        if (out_deg[i] - in_deg[i] == 1) {
            start_node = i;
            start_count++;
        } else if (in_deg[i] - out_deg[i] == 1) {
            end_count++;
        } else if (in_deg[i] != out_deg[i]) {
            return {};
        }
    }
    if (!((start_count == 0 && end_count == 0) || (start_count == 1 && end_count == 1))) {
        return {};
    }

    std::vector<int> path;
    std::vector<int> st = {start_node};

    while (!st.empty()) {
        int u = st.back();
        if (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }
    std::reverse(path.begin(), path.end());
    if ((int)path.size() != total_edges + 1) return {};
    return path;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);

    auto circuit = eulerian_trail_directed(n, adj);
    assert((int)circuit.size() == 4);
    assert(circuit.front() == 0 && circuit.back() == 0);
    return 0;
}
