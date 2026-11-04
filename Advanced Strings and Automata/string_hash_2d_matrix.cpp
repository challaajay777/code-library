// Algorithm: 2D Polynomial Rolling Hash for Subgrid Matching
// Purpose: Computes 2D rolling hashes over a character grid to query subgrid hashes in O(1).
// Time Complexity: O(R * C) precomputation, O(1) query
// Space Complexity: O(R * C)
// Preconditions: 2D grid of dimensions R x C.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Hash2D {
    static const unsigned long long P1 = 313ULL;
    static const unsigned long long P2 = 1009ULL;
    int R, C;
    std::vector<std::vector<unsigned long long>> h, pow1, pow2;

public:
    Hash2D(const std::vector<std::string>& grid) {
        R = grid.size();
        C = grid[0].size();
        h.assign(R + 1, std::vector<unsigned long long>(C + 1, 0));
        pow1.assign(R + 1, std::vector<unsigned long long>(C + 1, 1));
        pow2.assign(R + 1, std::vector<unsigned long long>(C + 1, 1));

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                pow1[i + 1][j + 1] = pow1[i][j + 1] * P1;
                pow2[i + 1][j + 1] = pow2[i + 1][j] * P2;
            }
        }

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                h[i + 1][j + 1] = h[i][j + 1] * P1 + h[i + 1][j] * P2 - h[i][j] * P1 * P2 + (unsigned char)grid[i][j];
            }
        }
    }

    // Query hash of subgrid [r1, r2] x [c1, c2] inclusive (0-indexed)
    unsigned long long get_subgrid(int r1, int c1, int r2, int c2) {
        int dr = r2 - r1 + 1;
        int dc = c2 - c1 + 1;
        unsigned long long p1 = 1;
        for (int i = 0; i < dr; ++i) p1 *= P1;
        unsigned long long p2 = 1;
        for (int j = 0; j < dc; ++j) p2 *= P2;

        return h[r2 + 1][c2 + 1] - h[r1][c2 + 1] * p1 - h[r2 + 1][c1] * p2 + h[r1][c1] * p1 * p2;
    }
};

int main() {
    std::vector<std::string> grid = {
        "abcd",
        "efgh",
        "abcd",
        "efgh"
    };
    Hash2D h2d(grid);
    // Subgrid [0..1, 0..1] is {"ab", "ef"}
    // Subgrid [2..3, 0..1] is {"ab", "ef"}
    assert(h2d.get_subgrid(0, 0, 1, 1) == h2d.get_subgrid(2, 0, 3, 1));
    // Different subgrid
    assert(h2d.get_subgrid(0, 0, 1, 1) != h2d.get_subgrid(0, 2, 1, 3));
    return 0;
}
