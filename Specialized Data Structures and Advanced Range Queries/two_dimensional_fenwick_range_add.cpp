// Algorithm: 2D Fenwick Tree Range Add and Rectangle Sum
// Purpose: Supports 2D rectangular additions and 2D prefix sums using 4 2D Fenwick trees.
// Time Complexity: O(log R * log C) query/update
// Space Complexity: O(R * C)
// Preconditions: 1-indexed 2D coordinates.

#include <iostream>
#include <vector>
#include <cassert>

struct Fenwick2DAddSum {
    int R, C;
    std::vector<std::vector<long long>> t1, t2, t3, t4;

    Fenwick2DAddSum(int r, int c) : R(r), C(c),
        t1(r + 1, std::vector<long long>(c + 1, 0)),
        t2(r + 1, std::vector<long long>(c + 1, 0)),
        t3(r + 1, std::vector<long long>(c + 1, 0)),
        t4(r + 1, std::vector<long long>(c + 1, 0)) {}

    void add_point(int r, int c, long long val) {
        for (int i = r; i <= R; i += i & -i) {
            for (int j = c; j <= C; j += j & -j) {
                t1[i][j] += val;
                t2[i][j] += val * (r - 1);
                t3[i][j] += val * (c - 1);
                t4[i][j] += val * (r - 1) * (c - 1);
            }
        }
    }

    void range_add(int r1, int c1, int r2, int c2, long long val) {
        add_point(r1, c1, val);
        add_point(r1, c2 + 1, -val);
        add_point(r2 + 1, c1, -val);
        add_point(r2 + 1, c2 + 1, val);
    }

    long long query_prefix(int r, int c) {
        long long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
        for (int i = r; i > 0; i -= i & -i) {
            for (int j = c; j > 0; j -= j & -j) {
                s1 += t1[i][j];
                s2 += t2[i][j];
                s3 += t3[i][j];
                s4 += t4[i][j];
            }
        }
        return s1 * r * c - s2 * c - s3 * r + s4;
    }

    long long query(int r1, int c1, int r2, int c2) {
        return query_prefix(r2, c2) - query_prefix(r1 - 1, c2) - query_prefix(r2, c1 - 1) + query_prefix(r1 - 1, c1 - 1);
    }
};

int main() {
    Fenwick2DAddSum f2(3, 3);
    f2.range_add(1, 1, 2, 2, 5); // 2x2 box of 5s -> total 20
    assert(f2.query(1, 1, 2, 2) == 20);
    return 0;
}
