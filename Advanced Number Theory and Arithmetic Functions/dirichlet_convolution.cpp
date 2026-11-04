#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Dirichlet Convolution of Arithmetic Functions
// Purpose: Computes (f * g)(n) = sum_{d | n} f(d) * g(n / d) for arbitrary arithmetic functions up to N in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: 1 <= N <= 10^7.

class DirichletConvolution {
public:
    static std::vector<long long> convolve(const std::vector<long long>& f, const std::vector<long long>& g) {
        int n = f.size() - 1;
        std::vector<long long> h(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; i * j <= n; ++j) {
                h[i * j] += f[i] * g[j];
            }
        }
        return h;
    }
};

int main() {
    // 1 * 1 = d(n) (divisor count function)
    int n = 10;
    std::vector<long long> one(n + 1, 1);
    auto d = DirichletConvolution::convolve(one, one);

    // d(6) = 4 (1, 2, 3, 6)
    assert(d[6] == 4);
    assert(d[1] == 1);
    assert(d[4] == 3);

    std::cout << "dirichlet_convolution tests passed successfully.\n";
    return 0;
}
