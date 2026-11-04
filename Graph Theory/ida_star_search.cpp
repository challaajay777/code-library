// Algorithm: Iterative Deepening A* (IDA*) Grid Search
// Purpose: Finds the shortest path on a grid using memory-efficient depth-first search bounded by threshold.
// Time Complexity: O(b^d)
// Space Complexity: O(d)
// Preconditions: 2D grid with start and goal coordinates.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

const int FOUND = -1;
const int INF = 1e9;

int manhattan(int r1, int c1, int r2, int c2) {
    return std::abs(r1 - r2) + std::abs(c1 - c2);
}

int ida_search(int r, int c, int g, int threshold,
               const std::vector<std::vector<int>>& grid,
               std::pair<int, int> goal,
               std::vector<std::vector<bool>>& vis) {
    int f = g + manhattan(r, c, goal.first, goal.second);
    if (f > threshold) return f;
    if (r == goal.first && c == goal.second) return FOUND;

    int min_t = INF;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int k = 0; k < 4; ++k) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < (int)grid.size() && nc >= 0 && nc < (int)grid[0].size() &&
            grid[nr][nc] == 0 && !vis[nr][nc]) {
            vis[nr][nc] = true;
            int t = ida_search(nr, nc, g + 1, threshold, grid, goal, vis);
            if (t == FOUND) return FOUND;
            min_t = std::min(min_t, t);
            vis[nr][nc] = false;
        }
    }
    return min_t;
}

int ida_star(const std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal) {
    int threshold = manhattan(start.first, start.second, goal.first, goal.second);
    int R = grid.size(), C = grid[0].size();
    std::vector<std::vector<bool>> vis(R, std::vector<bool>(C, false));
    vis[start.first][start.second] = true;

    while (threshold < INF) {
        int t = ida_search(start.first, start.second, 0, threshold, grid, goal, vis);
        if (t == FOUND) return threshold;
        threshold = t;
    }
    return -1;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    assert(ida_star(grid, {0, 0}, {2, 2}) == 4);
    return 0;
}
