#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Pythagorean Triples Generator (Euclid's Formula)
// Purpose: Generates all primitive Pythagorean triples (a, b, c) with hypotenuse c <= limit using Euclid's parameters.
// Time Complexity: O(sqrt(limit) log(limit)) time
// Space Complexity: O(1) auxiliary space beyond result
// Preconditions: limit >= 5.

struct Triple {
    long long a, b, c;
};

class PythagoreanTriples {
public:
    static std::vector<Triple> generate_primitive(long long max_c) {
        std::vector<Triple> triples;
        for (long long m = 2; m * m <= max_c; ++m) {
            for (long long n = 1; n < m; ++n) {
                if ((m - n) % 2 == 1 && std::gcd(m, n) == 1) {
                    long long a = m * m - n * n;
                    long long b = 2 * m * n;
                    long long c = m * m + n * n;
                    if (c <= max_c) {
                        triples.push_back({std::min(a, b), std::max(a, b), c});
                    }
                }
            }
        }
        return triples;
    }
};

int main() {
    auto t = PythagoreanTriples::generate_primitive(25);
    // (3, 4, 5), (5, 12, 13), (8, 15, 17), (7, 24, 25)
    assert(t.size() == 4);

    std::cout << "pythagorean_triples_generator tests passed successfully.\n";
    return 0;
}
