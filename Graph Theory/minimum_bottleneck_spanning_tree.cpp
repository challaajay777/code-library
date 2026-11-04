// Algorithm: Minimum Bottleneck Spanning Tree (MBST)
// Purpose: Finds a spanning tree that minimizes the maximum weight among all its edges.
// Time Complexity: O(E log V)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Edge {
    int u, v, weight;
};

struct DSU {
    std::vector<int> parent;
    DSU(int n) : parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int min_bottleneck_spanning_tree(int n, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(n);
    int bottleneck = 0;
    int edges_count = 0;

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            bottleneck = std::max(bottleneck, e.weight);
            if (++edges_count == n - 1) break;
        }
    }
    return bottleneck;
}

int main() {
    int n = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {1, 2, 20},
        {2, 3, 30},
        {0, 3, 5}
    };
    assert(min_bottleneck_spanning_tree(n, edges) == 20);
    return 0;
}
