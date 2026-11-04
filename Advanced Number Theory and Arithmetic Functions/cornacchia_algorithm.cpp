#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Cornacchia's Algorithm (x^2 + d*y^2 = p)
// Purpose: Solves Diophantine equation x^2 + d*y^2 = p for prime p using modified Euclidean algorithm in O(log p).
// Time Complexity: O(log p) time
// Space Complexity: O(1) auxiliary space
// Preconditions: p is prime; 1 <= d < p; (-d / p) = 1.

class Cornacchia {
public:
    // Takes r such that r^2 = -d mod p
    static std::pair<long long, long long> solve(long long p, long long d, long long r) {
        if (2 * r < p) r = p - r;
        long long a = p, b = r;
        long long lim = std::sqrt(p);

        while (b > lim) {
            long long rem = a % b;
            a = b;
            b = rem;
        }

        long long c = p - b * b;
        if (c % d != 0) return {-1, -1};
        long long y = std::round(std::sqrt(c / d));
        if (b * b + d * y * y == p) {
            return {b, y};
        }
        return {-1, -1};
    }
};

int main() {
    // p = 29, d = 1. r = 12 (12^2 = 144 = -1 mod 29)
    auto [x, y] = Cornacchia::solve(29, 1, 12);
    assert(x * x + y * y == 29); // 5^2 + 2^2 = 29

    std::cout << "cornacchia_algorithm tests passed successfully.\n";
    return 0;
}
