// Algorithm: HyperLogLog Distinct Cardinality Estimator
// Purpose: Estimates cardinality of large multiset in O(1) space with small standard error.
// Time Complexity: O(1) update, O(M) estimate
// Space Complexity: O(2^B) registers
// Preconditions: Uniform 32-bit hash function.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

class HyperLogLog {
    int b, m;
    double alpha_m;
    std::vector<int> registers;

    unsigned int hash(int x) const {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        return x;
    }

public:
    HyperLogLog(int b = 6) : b(b), m(1 << b), registers(1 << b, 0) {
        if (m == 16) alpha_m = 0.673;
        else if (m == 32) alpha_m = 0.697;
        else if (m == 64) alpha_m = 0.709;
        else alpha_m = 0.7213 / (1.0 + 1.079 / m);
    }

    void add(int val) {
        unsigned int h = hash(val);
        int j = h >> (32 - b);
        unsigned int w = (h << b) | (1 << (b - 1));
        int lz = __builtin_clz(w) + 1;
        registers[j] = std::max(registers[j], lz);
    }

    double estimate() const {
        double sum = 0;
        for (int r : registers) sum += std::pow(2.0, -r);
        return alpha_m * m * m / sum;
    }
};

int main() {
    HyperLogLog hll(6);
    for (int i = 0; i < 500; ++i) hll.add(i);
    double est = hll.estimate();
    assert(est >= 300 && est <= 700);
    return 0;
}
