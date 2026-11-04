// Algorithm: BEST Theorem for Number of Eulerian Circuits
// Purpose: Calculates exact number of directed Eulerian circuits via Kirchhoff matrix tree theorem and degree factorials.
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)
// Preconditions: Eulerian directed connected graph.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

double det(std::vector<std::vector<double>>& a) {
    int n = a.size();
    double d = 1.0;
    for (int i = 0; i < n; ++i) {
        int p = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(a[j][i]) > std::abs(a[p][i])) p = j;
        }
        if (std::abs(a[p][i]) < 1e-9) return 0.0;
        if (p != i) {
            std::swap(a[i], a[p]);
            d = -d;
        }
        d *= a[i][i];
        for (int j = i + 1; j < n; ++j) {
            double factor = a[j][i] / a[i][i];
            for (int k = i; k < n; ++k) a[j][k] -= factor * a[i][k];
        }
    }
    return d;
}

long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

long long best_theorem_circuits(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> deg(n, 0);
    for (int u = 0; u < n; ++u) deg[u] = adj[u].size();

    // Laplacian matrix L = D_out - A
    std::vector<std::vector<double>> lap(n - 1, std::vector<double>(n - 1, 0));
    for (int i = 0; i < n - 1; ++i) {
        lap[i][i] = deg[i];
        for (int v : adj[i]) {
            if (v < n - 1) lap[i][v] -= 1.0;
        }
    }

    long long t_w = (long long)std::round(std::abs(det(lap)));
    long long prod = 1;
    for (int u = 0; u < n; ++u) {
        prod *= factorial(deg[u] - 1);
    }
    return t_w * prod;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    // Simple 3-cycle: exactly 1 Eulerian circuit
    assert(best_theorem_circuits(n, adj) == 1);
    return 0;
}
