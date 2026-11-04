#include <iostream>
#include <cassert>

// Algorithm: Montmort Derangements Numbers Modulo M
// Purpose: Calculates derangements sequence D(N) modulo arbitrary composite integer M in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0; M >= 1.

class MontmortDerangements {
public:
    static long long derangement(int n, long long m) {
        if (n == 0) return 1 % m;
        if (n == 1) return 0;

        long long d0 = 1 % m;
        long long d1 = 0;

        for (int i = 2; i <= n; ++i) {
            long long d_next = (i - 1) * (d1 + d0) % m;
            d0 = d1;
            d1 = d_next;
        }
        return d1;
    }
};

int main() {
    assert(MontmortDerangements::derangement(4, 100) == 9);
    assert(MontmortDerangements::derangement(5, 100) == 44);

    std::cout << "montmort_derangements_modulo tests passed successfully.\n";
    return 0;
}
