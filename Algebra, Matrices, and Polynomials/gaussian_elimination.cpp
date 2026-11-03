// Algorithm: Gaussian Elimination (System of Linear Equations)
// Supports: Solving Ax = b with partial pivoting, detecting unique/infinite/no solution
// Indexing: 0-based matrix indices [0, n - 1]
// Complexity: O(min(n, m) * n * m) time, O(n * m) memory
// Preconditions: System can be overdetermined, underdetermined, or square

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct GaussianElimination {
    static constexpr double EPS = 1e-9;
    static constexpr int NO_SOLUTION = 0;
    static constexpr int UNIQUE_SOLUTION = 1;
    static constexpr int INFINITE_SOLUTIONS = 2;

    // Solves augmented matrix A[n][m+1] where last column is b.
    // Stores solution vector in ans. Returns status code.
    static int solve(vector<vector<double>> a, vector<double>& ans) {
        int n = (int)a.size();
        int m = (int)a[0].size() - 1;

        vector<int> where(m, -1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int sel = row;
            for (int i = row; i < n; ++i) {
                if (abs(a[i][col]) > abs(a[sel][col])) {
                    sel = i;
                }
            }
            if (abs(a[sel][col]) < EPS) continue;

            swap(a[sel], a[row]);
            where[col] = row;

            for (int i = 0; i < n; ++i) {
                if (i != row) {
                    double c = a[i][col] / a[row][col];
                    for (int j = col; j <= m; ++j) {
                        a[i][j] -= a[row][j] * c;
                    }
                }
            }
            row++;
        }

        ans.assign(m, 0);
        for (int i = 0; i < m; ++i) {
            if (where[i] != -1) {
                ans[i] = a[where[i]][m] / a[where[i]][i];
            }
        }

        // Check for inconsistency (0 == non-zero)
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < m; ++j) {
                sum += ans[j] * a[i][j];
            }
            if (abs(sum - a[i][m]) > EPS) {
                return NO_SOLUTION;
            }
        }

        for (int i = 0; i < m; ++i) {
            if (where[i] == -1) return INFINITE_SOLUTIONS;
        }
        return UNIQUE_SOLUTION;
    }
};
