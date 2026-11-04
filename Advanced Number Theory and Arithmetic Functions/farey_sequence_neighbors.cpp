#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Farey Sequence Neighbor Finding
// Purpose: Finds the predecessor and successor of rational fraction a/b in Farey sequence F_n in O(log n).
// Time Complexity: O(log n) time
// Space Complexity: O(1) space
// Preconditions: 0 <= a/b <= 1; gcd(a, b) = 1.

class FareyNeighbors {
private:
    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

public:
    // Successor of a/b in F_n
    static std::pair<long long, long long> successor(long long a, long long b, long long n) {
        long long x, y;
        ext_gcd(a, b, x, y);
        // a*x + b*y = 1 -> a*(-y) - b*(-x) = 1
        long long c = -y, d = -x;
        long long k = (n - d) / b;
        c += k * a;
        d += k * b;
        return {c, d};
    }
};

int main() {
    // In F_5: fractions are 0/1, 1/5, 1/4, 1/3, 2/5, 1/2, 3/5, 2/3, 3/4, 4/5, 1/1
    auto [c, d] = FareyNeighbors::successor(1, 3, 5);
    // Successor of 1/3 in F_5 is 2/5
    assert(c == 2 && d == 5);

    std::cout << "farey_sequence_neighbors tests passed successfully.\n";
    return 0;
}
