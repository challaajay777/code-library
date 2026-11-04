#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Base-256 Radix Sort (32-bit Unsigned)
// Purpose: Sorts 32-bit unsigned integers in linear time using 4 passes of 8-bit counting sort.
// Time Complexity: O(4 * (N + 256)) = O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Unsigned 32-bit integers.

class RadixSortBase256 {
public:
    static void sort(std::vector<uint32_t>& a) {
        int n = a.size();
        if (n <= 1) return;

        std::vector<uint32_t> buffer(n);
        for (int shift = 0; shift < 32; shift += 8) {
            int count[256] = {0};
            for (int i = 0; i < n; ++i) {
                uint8_t byte = (a[i] >> shift) & 0xFF;
                count[byte]++;
            }
            int offset[256];
            offset[0] = 0;
            for (int i = 1; i < 256; ++i) {
                offset[i] = offset[i - 1] + count[i - 1];
            }
            for (int i = 0; i < n; ++i) {
                uint8_t byte = (a[i] >> shift) & 0xFF;
                buffer[offset[byte]++] = a[i];
            }
            a = buffer;
        }
    }
};

int main() {
    std::vector<uint32_t> a = {170, 45, 75, 90, 802, 24, 2, 66};
    RadixSortBase256::sort(a);
    std::vector<uint32_t> expected = {2, 24, 45, 66, 75, 90, 170, 802};
    assert(a == expected);

    std::cout << "radix_sort_base256 tests passed successfully.\n";
    return 0;
}
