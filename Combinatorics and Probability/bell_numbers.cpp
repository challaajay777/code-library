#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Bell Numbers (Set Partitions Count)
// Purpose: Computes Bell numbers B(n), the total number of partitions of an n-element set, using the Bell triangle in O(N^2).
// Time Complexity: O(N^2) time
// Space Complexity: O(N) auxiliary space
// Preconditions: N >= 0.

class BellNumbers {
public:
    static std::vector<long long> compute_bell(int n, long long mod = 1e9 + 7) {
        std::vector<long long> bell(n + 1, 0);
        std::vector<long long> row = {1};
        bell[0] = 1;

        for (int i = 1; i <= n; ++i) {
            std::vector<long long> next_row(i + 1);
            next_row[0] = row.back();
            for (int j = 1; j <= i; ++j) {
                next_row[j] = (next_row[j - 1] + row[j - 1]) % mod;
            }
            bell[i] = next_row[0];
            row = std::move(next_row);
        }
        return bell;
    }
};

int main() {
    auto B = BellNumbers::compute_bell(5);
    // B(0)=1, B(1)=1, B(2)=2, B(3)=5, B(4)=15, B(5)=52
    assert(B[0] == 1);
    assert(B[1] == 1);
    assert(B[2] == 2);
    assert(B[3] == 5);
    assert(B[4] == 15);
    assert(B[5] == 52);

    std::cout << "bell_numbers tests passed successfully.\n";
    return 0;
}
