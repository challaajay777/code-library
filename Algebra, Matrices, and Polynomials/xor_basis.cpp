// Algorithm: Linear Basis / XOR Basis (Gaussian Elimination over GF(2))
// Supports: Vector insertion, maximum XOR sum query, linear independence check, k-th XOR sum
// Indexing: Bits from 0 to BITS - 1 (default 60 bits for 64-bit integers)
// Complexity: O(BITS) per insertion and query, O(BITS) memory
// Preconditions: Values are 64-bit unsigned/signed integers

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct XORBasis {
    static constexpr int BITS = 60;
    long long basis[BITS];
    int sz = 0;

    XORBasis() {
        fill(begin(basis), end(basis), 0);
    }

    // Inserts mask into the basis. Returns true if linearly independent (basis expanded).
    bool insert(long long mask) {
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    sz++;
                    return true;
                }
                mask ^= basis[i];
            }
        }
        return false;
    }

    // Returns true if mask can be represented as XOR sum of basis elements
    bool can_represent(long long mask) const {
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) return false;
                mask ^= basis[i];
            }
        }
        return mask == 0;
    }

    // Returns maximum possible XOR sum from any subset of inserted elements
    long long max_xor() const {
        long long ans = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            if ((ans ^ basis[i]) > ans) {
                ans ^= basis[i];
            }
        }
        return ans;
    }

    int size() const {
        return sz;
    }
};
