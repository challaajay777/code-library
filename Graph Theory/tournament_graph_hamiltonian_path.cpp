// Algorithm: Hamiltonian Path in Tournament Graph
// Purpose: Constructs a Hamiltonian path in any complete directed tournament graph in O(N^2) time.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: Complete directed graph with exactly one directed edge between every pair of vertices.

#include <iostream>
#include <vector>
#include <cassert>

std::vector<int> tournament_hamiltonian_path(int n, const std::vector<std::vector<bool>>& adj) {
    std::vector<int> path = {0};

    for (int v = 1; v < n; ++v) {
        if (adj[v][path[0]]) {
            path.insert(path.begin(), v);
        } else if (adj[path.back()][v]) {
            path.push_back(v);
        } else {
            for (size_t i = 0; i < path.size() - 1; ++i) {
                if (adj[path[i]][v] && adj[v][path[i + 1]]) {
                    path.insert(path.begin() + i + 1, v);
                    break;
                }
            }
        }
    }
    return path;
}

int main() {
    int n = 3;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    adj[0][1] = true;
    adj[1][2] = true;
    adj[2][0] = true;

    auto path = tournament_hamiltonian_path(n, adj);
    assert((int)path.size() == 3);
    for (int i = 0; i < 2; ++i) {
        assert(adj[path[i]][path[i + 1]]);
    }
    return 0;
}
