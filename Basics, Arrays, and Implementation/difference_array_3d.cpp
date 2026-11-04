#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 3D Difference Array
// Purpose: Performs subvolume updates in O(1) time and reconstructs the full 3D array in O(X*Y*Z).
// Time Complexity: O(1) per 3D box update, O(X*Y*Z) prefix reconstruction
// Space Complexity: O(X*Y*Z) space
// Preconditions: Coordinates 0 <= x1 <= x2 < X, 0 <= y1 <= y2 < Y, 0 <= z1 <= z2 < Z.

class DifferenceArray3D {
private:
    int X, Y, Z;
    std::vector<std::vector<std::vector<long long>>> d;

    void add_corner(int x, int y, int z, long long val) {
        if (x <= X && y <= Y && z <= Z) {
            d[x][y][z] += val;
        }
    }

public:
    DifferenceArray3D(int x, int y, int z) : X(x), Y(y), Z(z),
        d(x + 2, std::vector<std::vector<long long>>(y + 2, std::vector<long long>(z + 2, 0))) {}

    void add_box(int x1, int y1, int z1, int x2, int y2, int z2, long long val) {
        assert(x1 >= 0 && x1 <= x2 && x2 < X);
        assert(y1 >= 0 && y1 <= y2 && y2 < Y);
        assert(z1 >= 0 && z1 <= z2 && z2 < Z);

        add_corner(x1, y1, z1, val);
        add_corner(x2 + 1, y1, z1, -val);
        add_corner(x1, y2 + 1, z1, -val);
        add_corner(x1, y1, z2 + 1, -val);
        add_corner(x2 + 1, y2 + 1, z1, val);
        add_corner(x2 + 1, y1, z2 + 1, val);
        add_corner(x1, y2 + 1, z2 + 1, val);
        add_corner(x2 + 1, y2 + 1, z2 + 1, -val);
    }

    std::vector<std::vector<std::vector<long long>>> reconstruct() {
        auto res = d;
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                for (int k = 0; k < Z; ++k) {
                    long long cur = res[i][j][k];
                    if (i > 0) cur += res[i - 1][j][k];
                    if (j > 0) cur += res[i][j - 1][k];
                    if (k > 0) cur += res[i][j][k - 1];
                    if (i > 0 && j > 0) cur -= res[i - 1][j - 1][k];
                    if (i > 0 && k > 0) cur -= res[i - 1][j][k - 1];
                    if (j > 0 && k > 0) cur -= res[i][j - 1][k - 1];
                    if (i > 0 && j > 0 && k > 0) cur += res[i - 1][j - 1][k - 1];
                    res[i][j][k] = cur;
                }
            }
        }
        res.resize(X);
        for (auto& plane : res) {
            plane.resize(Y);
            for (auto& row : plane) {
                row.resize(Z);
            }
        }
        return res;
    }
};

int main() {
    DifferenceArray3D da(3, 3, 3);
    da.add_box(0, 0, 0, 1, 1, 1, 5);
    da.add_box(1, 1, 1, 2, 2, 2, 3);
    auto grid = da.reconstruct();

    assert(grid[0][0][0] == 5);
    assert(grid[1][1][1] == 8); // 5 + 3
    assert(grid[2][2][2] == 3);
    assert(grid[0][2][2] == 0);

    std::cout << "difference_array_3d tests passed successfully.\n";
    return 0;
}
