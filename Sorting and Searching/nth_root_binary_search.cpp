#include <iostream>
#include <cassert>

// Algorithm: Integer N-th Root via Binary Search
// Purpose: Computes floor(X^(1/N)) for large integers safely preventing integer overflow.
// Time Complexity: O(N * log X) time
// Space Complexity: O(1) auxiliary space
// Preconditions: X >= 0, N >= 1.

class NthRootBinarySearch {
private:
    // Returns 1 if mid^n == m, 2 if mid^n > m, 0 if mid^n < m
    static int check_power(long long mid, int n, long long m) {
        long long ans = 1;
        for (int i = 1; i <= n; ++i) {
            if (m / mid < ans) return 2; // Overflow or exceeded m
            ans *= mid;
        }
        if (ans == m) return 1;
        return 0;
    }

public:
    static long long nth_root_exact(int n, long long m) {
        long long low = 1, high = m;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            int status = check_power(mid, n, m);
            if (status == 1) return mid;
            if (status == 0) low = mid + 1;
            else high = mid - 1;
        }
        return -1; // No exact integer root
    }
};

int main() {
    assert(NthRootBinarySearch::nth_root_exact(3, 27) == 3);
    assert(NthRootBinarySearch::nth_root_exact(4, 69) == -1);
    assert(NthRootBinarySearch::nth_root_exact(2, 9) == 3);

    std::cout << "nth_root_binary_search tests passed successfully.\n";
    return 0;
}
