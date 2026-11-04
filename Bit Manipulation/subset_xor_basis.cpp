#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Linear Basis for XOR (Gaussian Elimination in GF(2))
// Purpose: Maintains a vector space basis under XOR to find max XOR subset, test subspace span, and query rank in O(B).
// Time Complexity: O(B) per insertion and max XOR query where B = 60
// Space Complexity: O(B) space
// Preconditions: 64-bit unsigned integers.

class LinearXorBasis {
private:
    static const int BITS = 62;
    uint64_t basis[BITS];
    int size;

public:
    LinearXorBasis() : size(0) {
        for (int i = 0; i < BITS; ++i) basis[i] = 0;
    }

    bool insert(uint64_t mask) {
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    size++;
                    return true;
                }
                mask ^= basis[i];
            }
        }
        return false; // Linearly dependent
    }

    uint64_t get_max_xor() const {
        uint64_t max_xor = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            if ((max_xor ^ basis[i]) > max_xor) {
                max_xor ^= basis[i];
            }
        }
        return max_xor;
    }

    bool can_form(uint64_t mask) const {
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) return false;
                mask ^= basis[i];
            }
        }
        return true;
    }

    int rank() const { return size; }
};

int main() {
    LinearXorBasis b;
    b.insert(3); // 011
    b.insert(5); // 101
    assert(b.get_max_xor() == 6); // 3 ^ 5 = 6 (110)
    assert(b.can_form(6) == true);
    assert(b.can_form(7) == false);

    std::cout << "subset_xor_basis tests passed successfully.\n";
    return 0;
}
