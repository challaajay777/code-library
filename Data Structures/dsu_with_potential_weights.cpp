// Algorithm: Potentialized DSU (Weight Difference Relations)
// Purpose: Maintains element components and evaluates potential differences dist(v) - dist(u) = weight.
// Time Complexity: O(alpha(N)) amortized
// Space Complexity: O(N)
// Preconditions: 0-indexed elements, consistent weight relationships.

#include <iostream>
#include <vector>
#include <cassert>

struct PotentialDSU {
    std::vector<int> parent;
    std::vector<long long> diff; // diff[i] = pot[i] - pot[parent[i]]

    PotentialDSU(int n) : parent(n), diff(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        int root = find(parent[i]);
        diff[i] += diff[parent[i]];
        return parent[i] = root;
    }

    // Assert pot[v] - pot[u] = w
    bool unite(int u, int v, long long w) {
        int root_u = find(u), root_v = find(v);
        if (root_u == root_v) {
            return (diff[v] - diff[u] == w);
        }
        parent[root_v] = root_u;
        diff[root_v] = diff[u] - diff[v] + w;
        return true;
    }

    long long get_diff(int u, int v) {
        return diff[v] - diff[u];
    }
};

int main() {
    PotentialDSU dsu(4);
    // pot[1] - pot[0] = 5
    // pot[2] - pot[1] = 3 => pot[2] - pot[0] = 8
    assert(dsu.unite(0, 1, 5));
    assert(dsu.unite(1, 2, 3));
    dsu.find(0); dsu.find(2);
    assert(dsu.get_diff(0, 2) == 8);
    return 0;
}
