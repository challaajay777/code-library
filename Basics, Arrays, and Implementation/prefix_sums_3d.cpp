#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 3D Prefix Sums
// Purpose: Queries arbitrary sub-volume sums in a 3D grid in O(1) time after O(X*Y*Z) preprocessing using inclusion-exclusion.
// Time Complexity: O(X*Y*Z) preprocessing, O(1) per box sum query
// Space Complexity: O(X*Y*Z) auxiliary space
// Preconditions: Coordinates satisfy 0 <= x1 <= x2 < X, 0 <= y1 <= y2 < Y, 0 <= z1 <= z2 < Z.

class PrefixSums3D {
private:
    int X, Y, Z;
    std::vector<std::vector<std::vector<long long>>> pref;

public:
    PrefixSums3D(const std::vector<std::vector<std::vector<long long>>>& a) {
        X = a.size();
        Y = (X > 0 ? a[0].size() : 0);
        Z = (Y > 0 ? a[0][0].size() : 0);

        pref.assign(X + 1, std::vector<std::vector<long long>>(Y + 1, std::vector<long long>(Z + 1, 0)));

        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                for (int k = 0; k < Z; ++k) {
                    pref[i + 1][j + 1][k + 1] = a[i][j][k]
                        + pref[i][j + 1][k + 1] + pref[i + 1][j][k + 1] + pref[i + 1][j + 1][k]
                        - pref[i][j][k + 1] - pref[i][j + 1][k] - pref[i + 1][j][k]
                        + pref[i][j][k];
                }
            }
        }
    }

    long long query(int x1, int y1, int z1, int x2, int y2, int z2) const {
        assert(x1 >= 0 && x1 <= x2 && x2 < X);
        assert(y1 >= 0 && y1 <= y2 && y2 < Y);
        assert(z1 >= 0 && z1 <= z2 && z2 < Z);

        int xa = x1, xb = x2 + 1;
        int ya = y1, yb = y2 + 1;
        int za = z1, zb = z2 + 1;

        return pref[xb][yb][zb]
             - pref[xa][yb][zb] - pref[xb][ya][zb] - pref[xb][yb][za]
             + pref[xa][ya][zb] + pref[xa][yb][za] + pref[xb][ya][za]
             - pref[xa][ya][za];
    }
};

int main() {
    int X = 2, Y = 2, Z = 2;
    std::vector<std::vector<std::vector<long long>>> a(X, std::vector<std::vector<long long>>(Y, std::vector<long long>(Z, 1)));
    PrefixSums3D p3(a);

    assert(p3.query(0, 0, 0, 1, 1, 1) == 8);
    assert(p3.query(0, 0, 0, 0, 0, 0) == 1);
    assert(p3.query(0, 0, 0, 1, 0, 0) == 2);

    std::cout << "prefix_sums_3d tests passed successfully.\n";
    return 0;
}
