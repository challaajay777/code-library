#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Derangements (Subfactorial !n)
// Purpose: Computes the number of permutations of n elements having no fixed points using recurrence !n = (n-1)*(!(n-1) + !(n-2)).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: N >= 0.

class Subfactorial {
public:
    static std::vector<long long> compute_derangements(int n, long long mod = 1e9 + 7) {
        std::vector<long long> d(n + 1, 0);
        if (n >= 0) d[0] = 1;
        if (n >= 1) d[1] = 0;

        for (int i = 2; i <= n; ++i) {
            d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % mod;
        }
        return d;
    }
};

int main() {
    auto d = Subfactorial::compute_derangements(5);
    // !0=1, !1=0, !2=1, !3=2, !4=9, !5=44
    assert(d[0] == 1);
    assert(d[1] == 0);
    assert(d[2] == 1);
    assert(d[3] == 2);
    assert(d[4] == 9);
    assert(d[5] == 44);

    std::cout << "derangements_subfactorial tests passed successfully.\n";
    return 0;
}
