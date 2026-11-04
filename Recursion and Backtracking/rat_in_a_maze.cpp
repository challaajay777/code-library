#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// Algorithm: Rat in a Maze (All Directional Paths)
// Purpose: Finds all distinct paths from (0, 0) to (N-1, N-1) in a grid with obstacles, returning move sequences 'DLRU'.
// Time Complexity: O(4^(N^2)) worst case
// Space Complexity: O(N^2) recursion depth
// Preconditions: Grid consists of 0 (blocked) and 1 (free cell).

class RatInMaze {
private:
    static void solve(int r, int c, int n, std::vector<std::vector<int>>& maze,
                      std::string& current_path, std::vector<std::string>& all_paths) {
        if (r == n - 1 && c == n - 1) {
            all_paths.push_back(current_path);
            return;
        }

        maze[r][c] = 0; // Mark visited

        // Down
        if (r + 1 < n && maze[r + 1][c] == 1) {
            current_path.push_back('D');
            solve(r + 1, c, n, maze, current_path, all_paths);
            current_path.pop_back();
        }
        // Left
        if (c - 1 >= 0 && maze[r][c - 1] == 1) {
            current_path.push_back('L');
            solve(r, c - 1, n, maze, current_path, all_paths);
            current_path.pop_back();
        }
        // Right
        if (c + 1 < n && maze[r][c + 1] == 1) {
            current_path.push_back('R');
            solve(r, c + 1, n, maze, current_path, all_paths);
            current_path.pop_back();
        }
        // Up
        if (r - 1 >= 0 && maze[r - 1][c] == 1) {
            current_path.push_back('U');
            solve(r - 1, c, n, maze, current_path, all_paths);
            current_path.pop_back();
        }

        maze[r][c] = 1; // Unmark
    }

public:
    static std::vector<std::string> find_paths(std::vector<std::vector<int>> maze) {
        int n = maze.size();
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) return {};

        std::vector<std::string> all_paths;
        std::string current_path = "";
        solve(0, 0, n, maze, current_path, all_paths);
        std::sort(all_paths.begin(), all_paths.end());
        return all_paths;
    }
};

int main() {
    std::vector<std::vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    auto paths = RatInMaze::find_paths(maze);
    assert(paths.size() == 2);
    assert(paths[0] == "DDRDRR");
    assert(paths[1] == "DRDDRR");

    std::cout << "rat_in_a_maze tests passed successfully.\n";
    return 0;
}
