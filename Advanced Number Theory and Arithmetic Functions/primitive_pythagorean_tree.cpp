#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Berggren's Tree of Primitive Pythagorean Triples
// Purpose: Generates complete ternary tree of all primitive Pythagorean triples using 3 linear matrix transformations.
// Time Complexity: O(3^Depth) time
// Space Complexity: O(Depth) recursion stack
// Preconditions: Base root triple is (3, 4, 5).

struct PPTriple {
    long long a, b, c;
};

class BerggrenTree {
private:
    static void branch(long long a, long long b, long long c, int depth, std::vector<PPTriple>& res) {
        if (depth == 0) return;
        res.push_back({a, b, c});

        // Matrix 1
        branch( a - 2*b + 2*c,  2*a - b + 2*c,  2*a - 2*b + 3*c, depth - 1, res);
        // Matrix 2
        branch( a + 2*b + 2*c,  2*a + b + 2*c,  2*a + 2*b + 3*c, depth - 1, res);
        // Matrix 3
        branch(-a + 2*b + 2*c, -2*a + b + 2*c, -2*a + 2*b + 3*c, depth - 1, res);
    }

public:
    static std::vector<PPTriple> generate_triples(int depth) {
        std::vector<PPTriple> res;
        branch(3, 4, 5, depth, res);
        return res;
    }
};

int main() {
    auto triples = BerggrenTree::generate_triples(2);
    // Root + 3 children = 4 triples
    assert(triples.size() == 4);
    for (const auto& t : triples) {
        assert(t.a * t.a + t.b * t.b == t.c * t.c);
    }

    std::cout << "primitive_pythagorean_tree tests passed successfully.\n";
    return 0;
}
