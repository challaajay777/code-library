// Algorithm: Boruvka Minimum Spanning Tree Algorithm
// Purpose: Constructs minimum spanning tree in O(E log V) time by contracting components simultaneously.
// Time Complexity: O(E log V)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph with distinct or properly tied edge weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

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

long long boruvka_mst(int n, const std::vector<Edge>& edges) {
    DSU dsu(n);
    int num_components = n;
    long long mst_weight = 0;

    while (num_components > 1) {
        std::vector<int> cheapest(n, -1);

        for (int i = 0; i < (int)edges.size(); ++i) {
            int set1 = dsu.find(edges[i].u);
            int set2 = dsu.find(edges[i].v);
            if (set1 != set2) {
                if (cheapest[set1] == -1 || edges[i].weight < edges[cheapest[set1]].weight) cheapest[set1] = i;
                if (cheapest[set2] == -1 || edges[i].weight < edges[cheapest[set2]].weight) cheapest[set2] = i;
            }
        }

        bool progress = false;
        for (int i = 0; i < n; ++i) {
            if (cheapest[i] != -1) {
                int e_idx = cheapest[i];
                if (dsu.unite(edges[e_idx].u, edges[e_idx].v)) {
                    mst_weight += edges[e_idx].weight;
                    num_components--;
                    progress = true;
                }
            }
        }
        if (!progress) break;
    }
    return mst_weight;
}

int main() {
    int n = 4;
    std::vector<Edge> edges = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {3, 0, 4},
        {0, 2, 5}
    };
    assert(boruvka_mst(n, edges) == 6); // 1 + 2 + 3
    return 0;
}
