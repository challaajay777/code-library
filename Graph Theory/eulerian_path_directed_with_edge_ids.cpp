// Algorithm: Directed Eulerian Path with Edge IDs
// Purpose: Finds Eulerian path on directed multigraph returning exact edge sequence indices.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Directed multigraph.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct DirectedEdge {
    int to, id;
};

std::vector<int> eulerian_edges_directed(int n, int m, std::vector<std::vector<DirectedEdge>>& adj, int start) {
    std::vector<int> path_edges;
    std::vector<int> cur_edge(n, 0);
    std::vector<int> st = {start};

    while (!st.empty()) {
        int u = st.back();
        if (cur_edge[u] < (int)adj[u].size()) {
            auto e = adj[u][cur_edge[u]++];
            st.push_back(e.to);
            path_edges.push_back(e.id);
        } else {
            st.pop_back();
        }
    }
    return path_edges;
}

int main() {
    int n = 3, m = 3;
    std::vector<std::vector<DirectedEdge>> adj(n);
    adj[0].push_back({1, 0});
    adj[1].push_back({2, 1});
    adj[2].push_back({0, 2});

    auto edges = eulerian_edges_directed(n, m, adj, 0);
    assert(edges.size() == 3);
    return 0;
}
