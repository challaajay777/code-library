#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Fast Walsh-Hadamard Transform (XOR Convolution)
// Purpose: Computes the bitwise XOR convolution of two arrays C[k] = sum_{i ^ j = k} A[i] * B[j] in O(N log N).
// Time Complexity: O(N log N) where N = 2^k
// Space Complexity: O(1) auxiliary space in-place
// Preconditions: Size of array must be a power of two.

class FWHT_XOR {
public:
    static void transform(std::vector<long long>& a, bool invert) {
        int n = a.size();
        for (int len = 1; 2 * len <= n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    long long u = a[i + j];
                    long long v = a[i + len + j];
                    a[i + j] = u + v;
                    a[i + len + j] = u - v;
                }
            }
        }
        if (invert) {
            for (int i = 0; i < n; ++i) {
                a[i] /= n;
            }
        }
    }

    static std::vector<long long> convolve(std::vector<long long> a, std::vector<long long> b) {
        int n = a.size();
        transform(a, false);
        transform(b, false);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        transform(a, true);
        return a;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 0, 0};
    std::vector<long long> b = {3, 4, 0, 0};
    auto c = FWHT_XOR::convolve(a, b);
    // c[0] = a[0]*b[0] + a[1]*b[1] = 1*3 + 2*4 = 11
    // c[1] = a[0]*b[1] + a[1]*b[0] = 1*4 + 2*3 = 10
    assert(c[0] == 11);
    assert(c[1] == 10);
    assert(c[2] == 0 && c[3] == 0);

    std::cout << "fwht_xor tests passed successfully.\n";
    return 0;
}
