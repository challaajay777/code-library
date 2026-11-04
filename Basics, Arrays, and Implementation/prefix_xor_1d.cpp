#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 1D Prefix XOR
// Purpose: Computes range XOR sum queries on static array in O(1) time after O(N) preprocessing.
// Time Complexity: O(N) preprocessing, O(1) per query
// Space Complexity: O(N) auxiliary space
// Preconditions: Array indices 0 <= L <= R < N.

class PrefixXor1D {
private:
    std::vector<long long> px;

public:
    PrefixXor1D() = default;
    explicit PrefixXor1D(const std::vector<long long>& a) {
        int n = a.size();
        px.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            px[i + 1] = px[i] ^ a[i];
        }
    }

    // Returns XOR sum of elements in [l, r] (0-indexed, inclusive)
    long long query(int l, int r) const {
        assert(l >= 0 && r + 1 < (int)px.size() && l <= r);
        return px[r + 1] ^ px[l];
    }
};

int main() {
    std::vector<long long> a = {3, 8, 2, 5, 1, 4, 7};
    PrefixXor1D px(a);

    assert(px.query(0, 0) == 3);
    assert(px.query(0, 1) == (3 ^ 8));
    assert(px.query(1, 3) == (8 ^ 2 ^ 5));
    assert(px.query(0, 6) == (3 ^ 8 ^ 2 ^ 5 ^ 1 ^ 4 ^ 7));
    assert(px.query(2, 4) == (2 ^ 5 ^ 1));

    std::cout << "prefix_xor_1d tests passed successfully.\n";
    return 0;
}
