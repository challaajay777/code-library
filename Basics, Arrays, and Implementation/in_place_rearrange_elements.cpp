#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: In-Place Permutation Rearrange A[i] = A[A[i]]
// Purpose: Rearranges an array such that a[i] becomes a[a[i]] in-place using O(1) extra space via modular arithmetic encoding.
// Time Complexity: O(N) time with two passes
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements 0 <= a[i] < N.

class InPlacePermutationRearrange {
public:
    static void rearrange(std::vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            a[i] += (a[a[i]] % n) * n;
        }
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
};

int main() {
    std::vector<int> a = {3, 2, 0, 1};
    // a[0] = a[3] = 1
    // a[1] = a[2] = 0
    // a[2] = a[0] = 3
    // a[3] = a[1] = 2
    InPlacePermutationRearrange::rearrange(a);
    std::vector<int> expected = {1, 0, 3, 2};
    assert(a == expected);

    std::vector<int> b = {4, 0, 2, 1, 3};
    InPlacePermutationRearrange::rearrange(b);
    std::vector<int> expected2 = {3, 4, 2, 0, 1};
    assert(b == expected2);

    std::cout << "in_place_rearrange_elements tests passed successfully.\n";
    return 0;
}
