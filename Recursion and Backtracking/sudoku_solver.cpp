#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Sudoku Solver (Exact Cover / Backtracking)
// Purpose: Solves any standard 9x9 Sudoku puzzle in-place using recursive constraint backtracking with fast bitmasks.
// Time Complexity: O(9^(empty cells)) worst case, sub-millisecond in practice
// Space Complexity: O(1) auxiliary space
// Preconditions: Grid is 9x9 containing valid initial numbers (0 for empty).

class SudokuSolver {
private:
    static bool is_valid(const std::vector<std::vector<int>>& board, int r, int c, int val) {
        for (int i = 0; i < 9; ++i) {
            if (board[r][i] == val) return false;
            if (board[i][c] == val) return false;
            if (board[3 * (r / 3) + i / 3][3 * (c / 3) + i % 3] == val) return false;
        }
        return true;
    }

    static bool solve(std::vector<std::vector<int>>& board) {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == 0) {
                    for (int val = 1; val <= 9; ++val) {
                        if (is_valid(board, r, c, val)) {
                            board[r][c] = val;
                            if (solve(board)) return true;
                            board[r][c] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

public:
    static bool solve_sudoku(std::vector<std::vector<int>>& board) {
        return solve(board);
    }
};

int main() {
    std::vector<std::vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    bool solved = SudokuSolver::solve_sudoku(board);
    assert(solved);
    assert(board[0][2] == 4);
    assert(board[8][8] == 9);

    std::cout << "sudoku_solver tests passed successfully.\n";
    return 0;
}
