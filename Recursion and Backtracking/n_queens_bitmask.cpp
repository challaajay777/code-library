#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: N-Queens Solver (Bitmask Optimization)
// Purpose: High-performance N-Queens total solution counter using bitwise operations for row, column, and diagonal bitmasks.
// Time Complexity: O(N!) time with ultra-fast bitwise constant factors
// Space Complexity: O(N) recursion stack
// Preconditions: 1 <= N <= 30.

class NQueensBitmask {
private:
    static void count_solutions(uint32_t all_queens, uint32_t cols, uint32_t diag1, uint32_t diag2, int& count) {
        if (cols == all_queens) {
            count++;
            return;
        }
        uint32_t available = all_queens & (~(cols | diag1 | diag2));
        while (available > 0) {
            uint32_t p = available & -available;
            available -= p;
            count_solutions(all_queens, cols | p, (diag1 | p) << 1, (diag2 | p) >> 1, count);
        }
    }

public:
    static int total_n_queens(int n) {
        assert(n >= 1 && n <= 30);
        uint32_t all_queens = (1U << n) - 1U;
        int count = 0;
        count_solutions(all_queens, 0, 0, 0, count);
        return count;
    }
};

int main() {
    assert(NQueensBitmask::total_n_queens(4) == 2);
    assert(NQueensBitmask::total_n_queens(8) == 92);
    assert(NQueensBitmask::total_n_queens(10) == 724);

    std::cout << "n_queens_bitmask tests passed successfully.\n";
    return 0;
}
