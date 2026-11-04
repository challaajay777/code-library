#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Graph M-Coloring (Backtracking)
// Purpose: Assigns one of M colors to each vertex such that no two adjacent vertices share the same color.
// Time Complexity: O(M^V) worst case
// Space Complexity: O(V) recursion depth
// Preconditions: Graph adjacency matrix; M >= 1.

class GraphMColoring {
private:
    static bool is_safe(int v, const std::vector<std::vector<int>>& graph,
                        const std::vector<int>& color, int c) {
        for (int i = 0; i < (int)graph.size(); ++i) {
            if (graph[v][i] && color[i] == c) return false;
        }
        return true;
    }

    static bool color_util(int v, int m, const std::vector<std::vector<int>>& graph,
                           std::vector<int>& color) {
        if (v == (int)graph.size()) return true;

        for (int c = 1; c <= m; ++c) {
            if (is_safe(v, graph, color, c)) {
                color[v] = c;
                if (color_util(v + 1, m, graph, color)) return true;
                color[v] = 0;
            }
        }
        return false;
    }

public:
    static std::vector<int> color_graph(const std::vector<std::vector<int>>& graph, int m) {
        int n = graph.size();
        std::vector<int> color(n, 0);
        if (color_util(0, m, graph, color)) {
            return color;
        }
        return {};
    }
};

int main() {
    std::vector<std::vector<int>> g = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    auto colors = GraphMColoring::color_graph(g, 3);
    assert(!colors.empty());

    std::cout << "graph_m_coloring tests passed successfully.\n";
    return 0;
}
