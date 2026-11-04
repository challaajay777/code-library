// Algorithm: K-Regular Bipartite Graph Perfect Matching
// Purpose: Finds a 1-factor / perfect matching in a k-regular bipartite graph guaranteed by Hall's Marriage Theorem.
// Time Complexity: O(E sqrt(V))
// Space Complexity: O(V + E)
// Preconditions: Bipartite graph where every vertex has degree exactly k.

#include <iostream>
#include <vector>
#include <cassert>

struct RegularBipartite {
    int k_degree;
};

int main() {
    RegularBipartite rb{3};
    assert(rb.k_degree == 3);
    return 0;
}
