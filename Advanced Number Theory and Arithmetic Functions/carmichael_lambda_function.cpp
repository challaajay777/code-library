#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Carmichael Lambda Function
// Purpose: Calculates Carmichael function lambda(N), the exponent of the multiplicative group of integers modulo N.",
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class CarmichaelFunction {
private:
    static long long lcm(long long a, long long b) {
        return (a / std::gcd(a, b)) * b;
    }

public:
    static long long lambda(long long n) {
        if (n <= 2) return 1;
        long long res = 1;

        if (n % 2 == 0) {
            int count2 = 0;
            while (n % 2 == 0) {
                count2++;
                n /= 2;
            }
            if (count2 == 1) res = 1;
            else if (count2 == 2) res = 2;
            else res = 1LL << (count2 - 2);
        }

        for (long long p = 3; p * p <= n; p += 2) {
            if (n % p == 0) {
                long long p_pow = 1;
                while (n % p == 0) {
                    p_pow *= p;
                    n /= p;
                }
                long long lambda_p = p_pow / p * (p - 1);
                res = lcm(res, lambda_p);
            }
        }
        if (n > 1) {
            res = lcm(res, n - 1);
        }
        return res;
    }
};

int main() {
    assert(CarmichaelFunction::lambda(8) == 2);
    assert(CarmichaelFunction::lambda(15) == 4);
    assert(CarmichaelFunction::lambda(35) == 12);

    std::cout << "carmichael_lambda_function tests passed successfully.\n";
    return 0;
}
