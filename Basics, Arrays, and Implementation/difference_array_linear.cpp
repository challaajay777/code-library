#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Difference Array (Arithmetic Progression Range Update)
// Purpose: Supports range addition of an arithmetic progression A[i] += a*i + b in O(1) time using second-order difference arrays.
// Time Complexity: O(1) per range addition, O(N) array reconstruction
// Space Complexity: O(N) auxiliary space
// Preconditions: 0 <= l <= r < N.

class LinearDifferenceArray {
private:
    int n;
    std::vector<long long> d2;

public:
    explicit LinearDifferenceArray(int size) : n(size), d2(size + 3, 0) {}

    // Adds (start_val + k * diff) to index (l + k) for k = 0, 1, ..., r - l
    void add_ap(int l, int r, long long start_val, long long diff) {
        assert(l >= 0 && r < n && l <= r);
        long long len = r - l + 1;
        long long end_val = start_val + (len - 1) * diff;

        d2[l] += start_val;
        d2[l + 1] += diff - start_val;
        d2[r + 1] -= end_val + diff;
        d2[r + 2] += end_val;
    }

    std::vector<long long> reconstruct() const {
        std::vector<long long> d1(n + 1, 0);
        long long run = 0;
        for (int i = 0; i < n; ++i) {
            run += d2[i];
            d1[i] = run;
        }
        std::vector<long long> res(n, 0);
        long long val = 0;
        for (int i = 0; i < n; ++i) {
            val += d1[i];
            res[i] = val;
        }
        return res;
    }
};

int main() {
    LinearDifferenceArray lda(5);
    // Add AP [2, 5, 8] from index 1 to 3: start=2, diff=3
    lda.add_ap(1, 3, 2, 3);
    auto res = lda.reconstruct();
    std::vector<long long> expected = {0, 2, 5, 8, 0};
    assert(res == expected);

    // Add another constant AP [4, 4] from index 2 to 3: start=4, diff=0
    lda.add_ap(2, 3, 4, 0);
    res = lda.reconstruct();
    expected = {0, 2, 9, 12, 0};
    assert(res == expected);

    std::cout << "difference_array_linear tests passed successfully.\n";
    return 0;
}
