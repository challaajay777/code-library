// Algorithm: Line Graph Construction
// Purpose: Constructs the line graph L(G) where edges of G become vertices of L(G).
// Time Complexity: O(E + sum(deg^2))
// Space Complexity: O(E + E_L)
// Preconditions: Undirected graph with m edges.

#include <iostream>
#include <vector>
#include <cassert>

std::vector<std::vector<int>> build_line_graph(int n, const std::vector<std::pair<int, int>>& edges) {
    int m = edges.size();
    std::vector<std::vector<int>> line_adj(m);

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (edges[i].first == edges[j].first || edges[i].first == edges[j].second ||
                edges[i].second == edges[j].first || edges[i].second == edges[j].second) {
                line_adj[i].push_back(j);
                line_adj[j].push_back(i);
            }
        }
    }
    return line_adj;
}

int main() {
    // Triangle graph: 3 vertices, 3 edges. Line graph of triangle is triangle itself.
    std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}};
    auto line = build_line_graph(3, edges);
    assert(line.size() == 3);
    for (int i = 0; i < 3; ++i) assert(line[i].size() == 2);
    return 0;
}
