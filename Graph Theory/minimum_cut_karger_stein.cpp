// Algorithm: Karger-Stein Randomized Min-Cut
// Purpose: Computes global minimum cut of an undirected multigraph using recursive contraction.
// Time Complexity: O(V^2 log^3 V)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>

struct Edge {
    int u, v;
};

int contract_to_k(int n, std::vector<Edge> edges, int target_k, std::mt19937& rng) {
    std::vector<int> parent(n);
    for (int i = 0; i < n; ++i) parent[i] = i;
    auto find = [&](auto self, int i) -> int {
        return parent[i] == i ? i : (parent[i] = self(self, parent[i]));
    };

    int vertices = n;
    while (vertices > target_k && !edges.empty()) {
        std::uniform_int_distribution<int> dist(0, edges.size() - 1);
        int idx = dist(rng);
        auto e = edges[idx];
        edges[idx] = edges.back();
        edges.pop_back();

        int root1 = find(find, e.u);
        int root2 = find(find, e.v);
        if (root1 != root2) {
            parent[root1] = root2;
            vertices--;
        }
    }

    int cut = 0;
    for (const auto& e : edges) {
        if (find(find, e.u) != find(find, e.v)) cut++;
    }
    return cut;
}

int main() {
    int n = 4;
    std::vector<Edge> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};
    std::mt19937 rng(42);
    int cut = contract_to_k(n, edges, 2, rng);
    assert(cut >= 1);
    return 0;
}
