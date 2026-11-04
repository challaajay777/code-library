#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Algorithm: N-Queens Solver (Standard Backtracking)
// Purpose: Finds all distinct board configurations of placing N non-attacking queens on an N x N chessboard.
// Time Complexity: O(N!) time
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= N <= 14.

class NQueensStandard {
private:
    static void solve(int row, int n, std::vector<bool>& cols, std::vector<bool>& diag1,
                      std::vector<bool>& diag2, std::vector<std::string>& board,
                      std::vector<std::vector<std::string>>& results) {
        if (row == n) {
            results.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            int d1 = row - col + n;
            int d2 = row + col;
            if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                cols[col] = diag1[d1] = diag2[d2] = true;
                board[row][col] = 'Q';

                solve(row + 1, n, cols, diag1, diag2, board, results);

                board[row][col] = '.';
                cols[col] = diag1[d1] = diag2[d2] = false;
            }
        }
    }

public:
    static std::vector<std::vector<std::string>> solve_n_queens(int n) {
        std::vector<std::vector<std::string>> results;
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);

        solve(0, n, cols, diag1, diag2, board, results);
        return results;
    }
};

int main() {
    auto res4 = NQueensStandard::solve_n_queens(4);
    assert(res4.size() == 2);

    auto res8 = NQueensStandard::solve_n_queens(8);
    assert(res8.size() == 92);

    std::cout << "n_queens_standard tests passed successfully.\n";
    return 0;
}
