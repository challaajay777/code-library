// Algorithm: Maximum Clique Branch and Bound
// Purpose: Finds the maximum cardinality clique in an undirected graph using branch and bound with vertex coloring.
// Time Complexity: O(2^V)
// Space Complexity: O(V)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_clique_size = 0;
std::vector<int> best_clique;

void search_clique(std::vector<int>& current_clique, std::vector<int>& candidates,
                   const std::vector<std::vector<bool>>& adj) {
    if (candidates.empty()) {
        if ((int)current_clique.size() > max_clique_size) {
            max_clique_size = current_clique.size();
            best_clique = current_clique;
        }
        return;
    }

    while (!candidates.empty()) {
        if (current_clique.size() + candidates.size() <= (size_t)max_clique_size) return;
        int v = candidates.back();
        candidates.pop_back();

        current_clique.push_back(v);
        std::vector<int> next_candidates;
        for (int u : candidates) {
            if (adj[v][u]) next_candidates.push_back(u);
        }
        search_clique(current_clique, next_candidates, adj);
        current_clique.pop_back();
    }
}

int find_max_clique(int n, const std::vector<std::vector<bool>>& adj) {
    max_clique_size = 0;
    best_clique.clear();
    std::vector<int> cur, candidates(n);
    for (int i = 0; i < n; ++i) candidates[i] = i;
    search_clique(cur, candidates, adj);
    return max_clique_size;
}

int main() {
    int n = 4;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    adj[0][1] = adj[1][0] = true;
    adj[1][2] = adj[2][1] = true;
    adj[2][0] = adj[0][2] = true; // K3 {0, 1, 2}
    adj[2][3] = adj[3][2] = true;

    assert(find_max_clique(n, adj) == 3);
    return 0;
}
