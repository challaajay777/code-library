// Algorithm: Multi-Source BFS on 2D Grid
// Purpose: Calculates shortest distance from every cell to nearest facility/source simultaneously.
// Time Complexity: O(R * C)
// Space Complexity: O(R * C)
// Preconditions: 2D grid with marked sources.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::vector<std::vector<int>> multi_source_bfs(int r, int c, const std::vector<std::pair<int, int>>& sources) {
    const int INF = 1e9;
    std::vector<std::vector<int>> dist(r, std::vector<int>(c, INF));
    std::queue<std::pair<int, int>> q;

    for (auto [sr, sc] : sources) {
        dist[sr][sc] = 0;
        q.push({sr, sc});
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();

        for (int k = 0; k < 4; ++k) {
            int nr = cr + dr[k], nc = cc + dc[k];
            if (nr >= 0 && nr < r && nc >= 0 && nc < c && dist[nr][nc] == INF) {
                dist[nr][nc] = dist[cr][cc] + 1;
                q.push({nr, nc});
            }
        }
    }
    return dist;
}

int main() {
    auto dist = multi_source_bfs(3, 3, {{0, 0}, {2, 2}});
    assert(dist[0][0] == 0);
    assert(dist[2][2] == 0);
    assert(dist[1][1] == 2);
    assert(dist[0][1] == 1);
    return 0;
}
