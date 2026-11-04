#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Hamiltonian Cycle (Backtracking)
// Purpose: Finds a simple cycle in an undirected graph that visits every vertex exactly once and returns to starting node.
// Time Complexity: O(N!) worst case
// Space Complexity: O(N) auxiliary space
// Preconditions: Graph represented as adjacency matrix; V <= 20.

class HamiltonianCycle {
private:
    static bool is_safe(int v, const std::vector<std::vector<int>>& graph,
                        const std::vector<int>& path, int pos) {
        if (!graph[path[pos - 1]][v]) return false;
        for (int i = 0; i < pos; ++i) {
            if (path[i] == v) return false;
        }
        return true;
    }

    static bool cycle_util(const std::vector<std::vector<int>>& graph,
                           std::vector<int>& path, int pos, int v) {
        if (pos == v) {
            return graph[path[pos - 1]][path[0]] == 1;
        }
        for (int u = 1; u < v; ++u) {
            if (is_safe(u, graph, path, pos)) {
                path[pos] = u;
                if (cycle_util(graph, path, pos + 1, v)) return true;
                path[pos] = -1;
            }
        }
        return false;
    }

public:
    static std::vector<int> find_cycle(const std::vector<std::vector<int>>& graph) {
        int v = graph.size();
        std::vector<int> path(v, -1);
        path[0] = 0;

        if (!cycle_util(graph, path, 1, v)) {
            return {};
        }
        path.push_back(0); // return to start
        return path;
    }
};

int main() {
    std::vector<std::vector<int>> g = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };
    auto cycle = HamiltonianCycle::find_cycle(g);
    assert(!cycle.empty());
    assert(cycle.front() == 0 && cycle.back() == 0);

    std::cout << "hamiltonian_cycle_backtracking tests passed successfully.\n";
    return 0;
}
