#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Algorithm: 2D Grid Word Search
// Purpose: Determines if a word exists in an R x C grid using adjacent horizontal and vertical moves with backtrack marking.
// Time Complexity: O(R * C * 3^L) time where L is word length
// Space Complexity: O(L) recursion depth
// Preconditions: Grid characters match word casing.

class WordSearchGrid {
private:
    static bool dfs(std::vector<std::vector<char>>& board, int r, int c, const std::string& word, int idx) {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[0].size() || board[r][c] != word[idx]) {
            return false;
        }

        char temp = board[r][c];
        board[r][c] = '#'; // Mark visited

        bool found = dfs(board, r + 1, c, word, idx + 1) ||
                     dfs(board, r - 1, c, word, idx + 1) ||
                     dfs(board, r, c + 1, word, idx + 1) ||
                     dfs(board, r, c - 1, word, idx + 1);

        board[r][c] = temp; // Unmark
        return found;
    }

public:
    static bool exist(std::vector<std::vector<char>>& board, const std::string& word) {
        if (board.empty() || board[0].empty()) return false;
        for (size_t r = 0; r < board.size(); ++r) {
            for (size_t c = 0; c < board[0].size(); ++c) {
                if (board[r][c] == word[0] && dfs(board, r, c, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<char>> b = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    assert(WordSearchGrid::exist(b, "ABCCED") == true);
    assert(WordSearchGrid::exist(b, "SEE") == true);
    assert(WordSearchGrid::exist(b, "ABCB") == false);

    std::cout << "word_search_grid tests passed successfully.\n";
    return 0;
}
