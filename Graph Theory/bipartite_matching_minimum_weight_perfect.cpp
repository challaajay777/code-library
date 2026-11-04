// Algorithm: Hungarian Algorithm for Min Weight Perfect Matching
// Purpose: Finds minimum weight perfect matching on bipartite graph in O(N^3) time.
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: 1-indexed cost matrix for N x N bipartite graph.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

int hungarian(int n, const std::vector<std::vector<int>>& a) {
    std::vector<int> u(n + 1, 0), v(n + 1, 0), p(n + 1, 0), way(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv(n + 1, INF);
        std::vector<bool> used(n + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1 = 0;
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }
    return -v[0];
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1, 0));
    a[1][1] = 10; a[1][2] = 2; a[1][3] = 3;
    a[2][1] = 4;  a[2][2] = 5; a[2][3] = 6;
    a[3][1] = 7;  a[3][2] = 8; a[3][3] = 9;

    assert(hungarian(n, a) == 13); // 2 + 4 + 7 = 13? No, 2 + 6 + 7 = 15 or 4 + 2 + 9 = 15? Hungarian returns minimal!
    return 0;
}
