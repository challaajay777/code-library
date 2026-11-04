#include <iostream>
#include <cassert>

// Algorithm: Cipolla's Algorithm (Modular Square Root in Field Extension)
// Purpose: Finds x such that x^2 = n (mod p) for odd prime p using field extension GF(p^2) in expected O(log p) multiplications.
// Time Complexity: O(log p) expected time
// Space Complexity: O(1) auxiliary space
// Preconditions: p is an odd prime; n is a quadratic residue modulo p.

class Cipolla {
private:
    struct ComplexField {
        long long real, imag;
    };

    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static ComplexField mul(const ComplexField& a, const ComplexField& b, long long w, long long p) {
        long long r = ((__int128)a.real * b.real + (__int128)a.imag * b.imag % p * w) % p;
        long long i = ((__int128)a.real * b.imag + (__int128)a.imag * b.real) % p;
        return {r, i};
    }

    static ComplexField power_field(ComplexField base, long long exp, long long w, long long p) {
        ComplexField res = {1, 0};
        while (exp > 0) {
            if (exp & 1) res = mul(res, base, w, p);
            base = mul(base, base, w, p);
            exp >>= 1;
        }
        return res;
    }

public:
    static long long sqrt_mod(long long n, long long p) {
        n %= p;
        if (n == 0) return 0;
        if (power(n, (p - 1) / 2, p) != 1) return -1; // No solution

        long long a = 0;
        long long w = 0;
        while (true) {
            a = (a + 1) % p;
            w = ((__int128)a * a - n % p + p) % p;
            if (power(w, (p - 1) / 2, p) == p - 1) {
                break; // Found non-residue in field
            }
        }

        ComplexField res = power_field({a, 1}, (p + 1) / 2, w, p);
        return res.real;
    }
};

int main() {
    long long r = Cipolla::sqrt_mod(10, 13);
    assert(r != -1);
    assert((r * r) % 13 == 10);

    long long r2 = Cipolla::sqrt_mod(5, 41);
    assert(r2 != -1);
    assert((r2 * r2) % 41 == 5);

    std::cout << "cipolla_modular_sqrt tests passed successfully.\n";
    return 0;
}
