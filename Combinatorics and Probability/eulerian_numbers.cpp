#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Eulerian Numbers A(n, m)
// Purpose: Computes Eulerian numbers A(n, m) counting permutations of {1..n} with exactly m ascents in O(n * m).
// Time Complexity: O(N * M) time
// Space Complexity: O(N * M) auxiliary space
// Preconditions: 0 <= m < n.

class EulerianNumbers {
public:
    static std::vector<std::vector<long long>> compute_eulerian(int n, long long mod = 1e9 + 7) {
        std::vector<std::vector<long long>> a(n + 1, std::vector<long long>(n + 1, 0));
        a[1][0] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                // A(i, j) = (j + 1) * A(i - 1, j) + (i - j) * A(i - 1, j - 1)
                long long t1 = (j + 1) * a[i - 1][j] % mod;
                long long t2 = (j > 0 ? (i - j) * a[i - 1][j - 1] % mod : 0);
                a[i][j] = (t1 + t2) % mod;
            }
        }
        return a;
    }
};

int main() {
    auto a = EulerianNumbers::compute_eulerian(3);
    // Permutations of 3:
    // 0 ascents: [3, 2, 1] -> 1
    // 1 ascent:  [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2] -> 4
    // 2 ascents: [1, 2, 3] -> 1
    assert(a[3][0] == 1);
    assert(a[3][1] == 4);
    assert(a[3][2] == 1);

    std::cout << "eulerian_numbers tests passed successfully.\n";
    return 0;
}
