#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Knight's Tour (Warnsdorff's Heuristic)
// Purpose: Finds a closed or open Knight's Tour visiting every square of an N x N chessboard exactly once.
// Time Complexity: O(N^2) linear time with Warnsdorff's tie-breaking
// Space Complexity: O(N^2) board grid
// Preconditions: Board size N >= 5.

class KnightsTourWarnsdorff {
private:
    static const int DX[8];
    static const int DY[8];

    static bool is_valid(int x, int y, int n, const std::vector<std::vector<int>>& board) {
        return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
    }

    static int get_degree(int x, int y, int n, const std::vector<std::vector<int>>& board) {
        int count = 0;
        for (int i = 0; i < 8; ++i) {
            if (is_valid(x + DX[i], y + DY[i], n, board)) count++;
        }
        return count;
    }

public:
    static std::vector<std::vector<int>> solve(int n, int start_x = 0, int start_y = 0) {
        std::vector<std::vector<int>> board(n, std::vector<int>(n, -1));
        int cur_x = start_x, cur_y = start_y;
        board[cur_x][cur_y] = 1;

        for (int move = 2; move <= n * n; ++move) {
            int best_idx = -1;
            int min_deg = 9;

            for (int i = 0; i < 8; ++i) {
                int nx = cur_x + DX[i];
                int ny = cur_y + DY[i];
                if (is_valid(nx, ny, n, board)) {
                    int deg = get_degree(nx, ny, n, board);
                    if (deg < min_deg) {
                        min_deg = deg;
                        best_idx = i;
                    }
                }
            }

            if (best_idx == -1) return {}; // Failed (dead end)
            cur_x += DX[best_idx];
            cur_y += DY[best_idx];
            board[cur_x][cur_y] = move;
        }
        return board;
    }
};

const int KnightsTourWarnsdorff::DX[8] = {1, 1, 2, 2, -1, -1, -2, -2};
const int KnightsTourWarnsdorff::DY[8] = {2, -2, 1, -1, 2, -2, 1, -1};

int main() {
    auto board = KnightsTourWarnsdorff::solve(6);
    assert(!board.empty());
    assert(board[0][0] == 1);

    std::cout << "knights_tour_warnsdorff tests passed successfully.\n";
    return 0;
}
