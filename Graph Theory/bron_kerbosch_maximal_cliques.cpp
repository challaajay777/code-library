// Algorithm: Bron-Kerbosch Maximal Cliques with Pivoting
// Purpose: Finds all maximal cliques in an undirected graph using recursive backtracking with pivot vertex.
// Time Complexity: O(3^(V/3))
// Space Complexity: O(V)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void bron_kerbosch_pivot(std::vector<int> R, std::vector<int> P, std::vector<int> X,
                         const std::vector<std::vector<bool>>& adj,
                         std::vector<std::vector<int>>& cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(R);
        return;
    }

    // Pick pivot u from P union X that maximizes |N(u) intersect P|
    int pivot = !P.empty() ? P[0] : X[0];

    std::vector<int> candidates;
    for (int v : P) {
        if (!adj[pivot][v]) candidates.push_back(v);
    }

    for (int v : candidates) {
        std::vector<int> next_R = R;
        next_R.push_back(v);

        std::vector<int> next_P, next_X;
        for (int p : P) if (adj[v][p]) next_P.push_back(p);
        for (int x : X) if (adj[v][x]) next_X.push_back(x);

        bron_kerbosch_pivot(next_R, next_P, next_X, adj, cliques);

        P.erase(std::remove(P.begin(), P.end(), v), P.end());
        X.push_back(v);
    }
}

int main() {
    int n = 4;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    // Triangle {0, 1, 2} and edge {2, 3}
    adj[0][1] = adj[1][0] = true;
    adj[1][2] = adj[2][1] = true;
    adj[2][0] = adj[0][2] = true;
    adj[2][3] = adj[3][2] = true;

    std::vector<int> R, P(n), X;
    for (int i = 0; i < n; ++i) P[i] = i;
    std::vector<std::vector<int>> cliques;
    bron_kerbosch_pivot(R, P, X, adj, cliques);

    // Maximal cliques: {0, 1, 2} and {2, 3}
    assert(cliques.size() == 2);
    return 0;
}
