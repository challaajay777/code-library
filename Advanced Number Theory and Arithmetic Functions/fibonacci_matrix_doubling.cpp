#include <iostream>
#include <cassert>

// Algorithm: Fast Doubling Fibonacci
// Purpose: Computes F(N) and F(N+1) modulo M in O(log N) operations using fast doubling identities.
// Time Complexity: O(log N) time
// Space Complexity: O(log N) recursion depth
// Preconditions: N >= 0; modulus M >= 1.

class FastDoublingFibonacci {
public:
    // Returns {F(n), F(n + 1)} mod m
    static std::pair<long long, long long> fib(long long n, long long m) {
        if (n == 0) return {0, 1 % m};
        auto [a, b] = fib(n / 2, m);
        long long c = ((unsigned __int128)a * (2 * b - a + m)) % m;
        long long d = ((unsigned __int128)a * a + (unsigned __int128)b * b) % m;

        if (n % 2 == 0) {
            return {c, d};
        } else {
            return {d, (c + d) % m};
        }
    }
};

int main() {
    long long MOD = 1000000007;
    assert(FastDoublingFibonacci::fib(0, MOD).first == 0);
    assert(FastDoublingFibonacci::fib(1, MOD).first == 1);
    assert(FastDoublingFibonacci::fib(10, MOD).first == 55);
    assert(FastDoublingFibonacci::fib(12, MOD).first == 144);

    std::cout << "fibonacci_matrix_doubling tests passed successfully.\n";
    return 0;
}
