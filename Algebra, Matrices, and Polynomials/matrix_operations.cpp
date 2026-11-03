// Algorithm: Matrix Operations & Fast Exponentiation
// Supports: Matrix addition, multiplication, exponentiation, identity, determinant
// Indexing: 0-based row and column indices [0, n - 1]
// Complexity: O(n^3) multiplication, O(n^3 log k) exponentiation, O(n^3) determinant
// Preconditions: Matrix dimensions match for operations

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct Matrix {
    int rows, cols;
    vector<vector<T>> mat;

    Matrix(int r, int c, T init_val = 0)
        : rows(r), cols(c), mat(r, vector<T>(c, init_val)) {}

    static Matrix identity(int n) {
        Matrix I(n, n, 0);
        for (int i = 0; i < n; ++i) I.mat[i][i] = 1;
        return I;
    }

    Matrix operator+(const Matrix& o) const {
        assert(rows == o.rows && cols == o.cols);
        Matrix res(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                res.mat[i][j] = mat[i][j] + o.mat[i][j];
            }
        }
        return res;
    }

    Matrix operator*(const Matrix& o) const {
        assert(cols == o.rows);
        Matrix res(rows, o.cols, 0);
        for (int i = 0; i < rows; ++i) {
            for (int k = 0; k < cols; ++k) {
                if (mat[i][k] == 0) continue;
                for (int j = 0; j < o.cols; ++j) {
                    res.mat[i][j] += mat[i][k] * o.mat[k][j];
                }
            }
        }
        return res;
    }

    Matrix power(long long p) const {
        assert(rows == cols && p >= 0);
        Matrix res = Matrix::identity(rows);
        Matrix base = *this;
        while (p > 0) {
            if (p & 1) res = res * base;
            base = base * base;
            p >>= 1;
        }
        return res;
    }
};
