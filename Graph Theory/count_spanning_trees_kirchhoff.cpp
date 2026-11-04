// Algorithm: Kirchhoff Matrix Tree Theorem
// Purpose: Counts the exact number of spanning trees via the determinant of any cofactor of the Laplacian matrix.
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

double determinant(std::vector<std::vector<double>>& a) {
    int n = a.size();
    double det = 1.0;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(a[j][i]) > std::abs(a[pivot][i])) pivot = j;
        }
        if (std::abs(a[pivot][i]) < 1e-9) return 0.0;
        if (pivot != i) {
            std::swap(a[i], a[pivot]);
            det = -det;
        }
        det *= a[i][i];
        for (int j = i + 1; j < n; ++j) {
            double factor = a[j][i] / a[i][i];
            for (int k = i; k < n; ++k) a[j][k] -= factor * a[i][k];
        }
    }
    return det;
}

long long count_spanning_trees(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<std::vector<double>> lap(n - 1, std::vector<double>(n - 1, 0));
    for (int i = 0; i < n - 1; ++i) {
        lap[i][i] = adj[i].size();
        for (int v : adj[i]) {
            if (v < n - 1) lap[i][v] -= 1.0;
        }
    }
    return (long long)std::round(std::abs(determinant(lap)));
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    // Complete graph K4 has 4^(4-2) = 16 spanning trees
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) if (i != j) adj[i].push_back(j);
    }
    assert(count_spanning_trees(n, adj) == 16);
    return 0;
}
