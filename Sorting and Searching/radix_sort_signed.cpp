#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Signed 32-bit Radix Sort
// Purpose: Sorts 32-bit signed integers in O(N) by flipping the sign bit and running 4-pass base-256 radix sort.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Signed 32-bit integers.

class RadixSortSigned {
public:
    static void sort(std::vector<int32_t>& a) {
        int n = a.size();
        if (n <= 1) return;

        // Invert sign bit so negative numbers map below positive numbers
        for (int i = 0; i < n; ++i) {
            a[i] ^= (1U << 31);
        }

        std::vector<int32_t> buffer(n);
        for (int shift = 0; shift < 32; shift += 8) {
            int count[256] = {0};
            for (int i = 0; i < n; ++i) {
                uint8_t byte = ((uint32_t)a[i] >> shift) & 0xFF;
                count[byte]++;
            }
            int offset[256];
            offset[0] = 0;
            for (int i = 1; i < 256; ++i) {
                offset[i] = offset[i - 1] + count[i - 1];
            }
            for (int i = 0; i < n; ++i) {
                uint8_t byte = ((uint32_t)a[i] >> shift) & 0xFF;
                buffer[offset[byte]++] = a[i];
            }
            a = buffer;
        }

        // Restore sign bit
        for (int i = 0; i < n; ++i) {
            a[i] ^= (1U << 31);
        }
    }
};

int main() {
    std::vector<int32_t> a = {-10, 5, -200, 100, 0, -1, 35};
    RadixSortSigned::sort(a);
    std::vector<int32_t> expected = {-200, -10, -1, 0, 5, 35, 100};
    assert(a == expected);

    std::cout << "radix_sort_signed tests passed successfully.\n";
    return 0;
}
