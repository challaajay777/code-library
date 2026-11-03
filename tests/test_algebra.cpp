// Test suite for Algebra, Matrices, and Polynomials
#include <bits/stdc++.h>
#include <cassert>
#include "Algebra, Matrices, and Polynomials/matrix_operations.cpp"
#include "Algebra, Matrices, and Polynomials/gaussian_elimination.cpp"
#include "Algebra, Matrices, and Polynomials/xor_basis.cpp"
#include "Algebra, Matrices, and Polynomials/fast_fourier_transform.cpp"
#include "Algebra, Matrices, and Polynomials/number_theoretic_transform.cpp"

using namespace std;

void test_matrix() {
    // Fibonacci using matrix exponentiation:
    // [1 1] ^ n * [1]
    // [1 0]       [0]
    Matrix<long long> T(2, 2);
    T.mat = {{1, 1}, {1, 0}};
    auto T10 = T.power(10);
    // F(10) is T10[0][1] = 55
    assert(T10.mat[0][1] == 55);
}

void test_gaussian() {
    // 2x + y = 5
    // x + 3y = 10
    // Sol: x = 1, y = 3
    vector<vector<double>> sys = {
        {2.0, 1.0, 5.0},
        {1.0, 3.0, 10.0}
    };
    vector<double> ans;
    int status = GaussianElimination::solve(sys, ans);
    assert(status == GaussianElimination::UNIQUE_SOLUTION);
    assert(abs(ans[0] - 1.0) < 1e-7);
    assert(abs(ans[1] - 3.0) < 1e-7);

    // Inconsistent: x + y = 1, x + y = 2
    vector<vector<double>> inc = {
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 2.0}
    };
    assert(GaussianElimination::solve(inc, ans) == GaussianElimination::NO_SOLUTION);
}

void test_xor_basis() {
    XORBasis basis;
    assert(basis.insert(3)); // 011
    assert(basis.insert(5)); // 101
    assert(basis.size() == 2);
    // Can represent 3 ^ 5 = 6 (110)
    assert(basis.can_represent(6));
    assert(!basis.insert(6)); // Dependent
    assert(basis.size() == 2);
    // Max XOR from {3, 5}: 3 ^ 5 = 6
    assert(basis.max_xor() == 6);
}

void test_fft_and_ntt() {
    // (1 + 2x) * (3 + 4x) = 3 + 10x + 8x^2
    vector<long long> a = {1, 2};
    vector<long long> b = {3, 4};
    auto prod_fft = FFT::multiply(a, b);
    vector<long long> exp_fft = {3, 10, 8};
    assert(prod_fft == exp_fft);

    // NTT mod 998244353
    vector<int> a_ntt = {1, 2};
    vector<int> b_ntt = {3, 4};
    auto prod_ntt = NTT::multiply(a_ntt, b_ntt);
    vector<int> exp_ntt = {3, 10, 8};
    assert(prod_ntt == exp_ntt);
}

int main() {
    cout << "[TEST] Running test_algebra suite...\n";
    test_matrix();
    test_gaussian();
    test_xor_basis();
    test_fft_and_ntt();
    cout << "[TEST] All 4 test sets in test_algebra passed!\n";
    return 0;
}
