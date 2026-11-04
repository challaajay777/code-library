// Algorithm: 2D Grid Flood Fill via BFS
// Purpose: Recolors connected matching component on 2D grid starting from (sr, sc).
// Time Complexity: O(R * C)
// Space Complexity: O(R * C)
// Preconditions: 2D grid, valid starting coordinates (sr, sc).

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

void flood_fill(std::vector<std::vector<int>>& image, int sr, int sc, int new_color) {
    int old_color = image[sr][sc];
    if (old_color == new_color) return;
    int r = image.size(), c = image[0].size();
    std::queue<std::pair<int, int>> q;
    q.push({sr, sc});
    image[sr][sc] = new_color;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();
        for (int k = 0; k < 4; ++k) {
            int nr = cr + dr[k], nc = cc + dc[k];
            if (nr >= 0 && nr < r && nc >= 0 && nc < c && image[nr][nc] == old_color) {
                image[nr][nc] = new_color;
                q.push({nr, nc});
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };
    flood_fill(grid, 1, 1, 2);
    assert(grid[1][1] == 2);
    assert(grid[0][0] == 2);
    assert(grid[2][2] == 1);
    return 0;
}
