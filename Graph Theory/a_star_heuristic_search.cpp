// Algorithm: A* Heuristic Path Search on 2D Grid
// Purpose: Finds optimal path using f(n) = g(n) + h(n) with Manhattan distance heuristic.
// Time Complexity: O(E)
// Space Complexity: O(V)
// Preconditions: 2D grid with passable and blocked cells.

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>

struct Node {
    int r, c, g, f;
    bool operator>(const Node& o) const { return f > o.f; }
};

int a_star_grid(int R, int C, const std::vector<std::vector<int>>& grid,
                std::pair<int, int> start, std::pair<int, int> goal) {
    auto heuristic = [&](int r, int c) {
        return std::abs(r - goal.first) + std::abs(c - goal.second);
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::vector<std::vector<int>> dist(R, std::vector<int>(C, 1e9));

    dist[start.first][start.second] = 0;
    pq.push({start.first, start.second, 0, heuristic(start.first, start.second)});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if (cur.r == goal.first && cur.c == goal.second) return cur.g;
        if (cur.g > dist[cur.r][cur.c]) continue;

        for (int k = 0; k < 4; ++k) {
            int nr = cur.r + dr[k], nc = cur.c + dc[k];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 0) {
                if (cur.g + 1 < dist[nr][nc]) {
                    dist[nr][nc] = cur.g + 1;
                    pq.push({nr, nc, dist[nr][nc], dist[nr][nc] + heuristic(nr, nc)});
                }
            }
        }
    }
    return -1;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    assert(a_star_grid(3, 3, grid, {0, 0}, {2, 2}) == 4);
    return 0;
}
