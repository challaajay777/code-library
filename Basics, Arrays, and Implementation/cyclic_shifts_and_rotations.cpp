#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Array Cyclic Rotations (Reversal and Juggling)
// Purpose: Rotates an array by K positions left or right in-place using O(1) extra memory.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Valid vector, any integer k (positive, negative, or zero).

class CyclicRotations {
public:
    // Rotates array to the left by k positions via 3-step reversal
    template <typename T>
    static void rotate_left_reversal(std::vector<T>& a, int k) {
        int n = a.size();
        if (n <= 1) return;
        k = (k % n + n) % n;
        if (k == 0) return;

        std::reverse(a.begin(), a.begin() + k);
        std::reverse(a.begin() + k, a.end());
        std::reverse(a.begin(), a.end());
    }

    // Rotates array to the right by k positions
    template <typename T>
    static void rotate_right(std::vector<T>& a, int k) {
        int n = a.size();
        if (n <= 1) return;
        k = (k % n + n) % n;
        rotate_left_reversal(a, n - k);
    }

    // Juggling algorithm for left rotation
    template <typename T>
    static void rotate_left_juggling(std::vector<T>& a, int k) {
        int n = a.size();
        if (n <= 1) return;
        k = (k % n + n) % n;
        if (k == 0) return;

        int num_cycles = std::gcd(n, k);
        for (int i = 0; i < num_cycles; ++i) {
            T temp = a[i];
            int j = i;
            while (true) {
                int next_idx = (j + k) % n;
                if (next_idx == i) break;
                a[j] = a[next_idx];
                j = next_idx;
            }
            a[j] = temp;
        }
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    CyclicRotations::rotate_left_reversal(a, 2);
    std::vector<int> exp1 = {3, 4, 5, 6, 7, 1, 2};
    assert(a == exp1);

    CyclicRotations::rotate_right(a, 2);
    std::vector<int> exp2 = {1, 2, 3, 4, 5, 6, 7};
    assert(a == exp2);

    CyclicRotations::rotate_left_juggling(a, 3);
    std::vector<int> exp3 = {4, 5, 6, 7, 1, 2, 3};
    assert(a == exp3);

    std::cout << "cyclic_shifts_and_rotations tests passed successfully.\n";
    return 0;
}
