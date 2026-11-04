#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Fast Walsh-Hadamard Transform (OR Convolution)
// Purpose: Computes bitwise OR convolution C[k] = sum_{i | j = k} A[i] * B[j] in O(N log N).
// Time Complexity: O(N log N) where N = 2^k
// Space Complexity: O(1) auxiliary space
// Preconditions: Size of array must be a power of two.

class FWHT_OR {
public:
    static void transform(std::vector<long long>& a, bool invert) {
        int n = a.size();
        for (int len = 1; 2 * len <= n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    long long u = a[i + j];
                    long long v = a[i + len + j];
                    if (!invert) {
                        a[i + len + j] = u + v;
                    } else {
                        a[i + len + j] = v - u;
                    }
                }
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
    std::vector<long long> a = {1, 2, 3, 4};
    std::vector<long long> b = {2, 1, 0, 5};
    auto c = FWHT_OR::convolve(a, b);

    // Naive check for index 3: sum of a[i]*b[j] where i | j == 3
    long long naive_3 = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((i | j) == 3) naive_3 += a[i] * b[j];
        }
    }
    assert(c[3] == naive_3);

    std::cout << "fwht_or tests passed successfully.\n";
    return 0;
}
