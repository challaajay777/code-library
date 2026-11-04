#include <iostream>
#include <cassert>

// Algorithm: Sum of Divisor Function Sum(Tau) in O(sqrt(N))
// Purpose: Computes sum_{i=1}^N tau(i) = sum_{i=1}^N floor(N / i) in O(sqrt(N)) time using the Harmonic Lemma.
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class FastDivisorSum {
public:
    static long long sum_tau(long long n) {
        long long total = 0;
        for (long long l = 1, r; l <= n; l = r + 1) {
            long long val = n / l;
            r = n / val;
            total += val * (r - l + 1);
        }
        return total;
    }
};

int main() {
    // tau(1)=1, tau(2)=2, tau(3)=2, tau(4)=3, tau(5)=2. Sum = 10
    assert(FastDivisorSum::sum_tau(5) == 10);

    std::cout << "divisor_sum_range_fast tests passed successfully.\n";
    return 0;
}
