// Algorithm: 3D Fenwick Tree Point Update Volume Query
// Purpose: Supports point additions and rectangular 3D box subvolume prefix sum queries in O(log X * log Y * log Z).
// Time Complexity: O(log X * log Y * log Z) query/update
// Space Complexity: O(X * Y * Z)
// Preconditions: Coordinates 1..X, 1..Y, 1..Z.

#include <iostream>
#include <vector>
#include <cassert>

struct Fenwick3D {
    int X, Y, Z;
    std::vector<std::vector<std::vector<long long>>> tree;

    Fenwick3D(int x, int y, int z) : X(x), Y(y), Z(z),
        tree(x + 1, std::vector<std::vector<long long>>(y + 1, std::vector<long long>(z + 1, 0))) {}

    void add(int x, int y, int z, long long delta) {
        for (int i = x; i <= X; i += i & -i) {
            for (int j = y; j <= Y; j += j & -j) {
                for (int k = z; k <= Z; k += k & -k) {
                    tree[i][j][k] += delta;
                }
            }
        }
    }

    long long query(int x, int y, int z) {
        long long sum = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                for (int k = z; k > 0; k -= k & -k) {
                    sum += tree[i][j][k];
                }
            }
        }
        return sum;
    }
};

int main() {
    Fenwick3D f3(3, 3, 3);
    f3.add(1, 1, 1, 10);
    f3.add(2, 2, 2, 20);
    assert(f3.query(1, 1, 1) == 10);
    assert(f3.query(2, 2, 2) == 30);
    return 0;
}
