#include <iostream>
#include <cassert>

// Algorithm: Elliptic Curve Point Addition and Multiplication
// Purpose: Performs point addition and double-and-add scalar multiplication on Weierstrass curve y^2 = x^3 + ax + b (mod p).
// Time Complexity: O(log k) operations per scalar multiplication k * P
// Space Complexity: O(1) auxiliary space
// Preconditions: Modulus p is prime.

struct ECPoint {
    long long x, y;
    bool is_infinity;
};

class EllipticCurve {
private:
    long long a, b, p;

    long long ext_gcd(long long u, long long v, long long& x, long long& y) const {
        if (v == 0) { x = 1; y = 0; return u; }
        long long x1, y1;
        long long d = ext_gcd(v, u % v, x1, y1);
        x = y1;
        y = x1 - y1 * (u / v);
        return d;
    }

    long long mod_inv(long long val) const {
        long long x, y;
        ext_gcd((val % p + p) % p, p, x, y);
        return (x % p + p) % p;
    }

public:
    EllipticCurve(long long curve_a, long long curve_b, long long prime_p)
        : a(curve_a), b(curve_b), p(prime_p) {}

    ECPoint add(const ECPoint& P, const ECPoint& Q) const {
        if (P.is_infinity) return Q;
        if (Q.is_infinity) return P;
        if (P.x == Q.x && (P.y + Q.y) % p == 0) return {0, 0, true};

        long long lambda;
        if (P.x == Q.x && P.y == Q.y) {
            long long num = (3 * P.x % p * P.x + a) % p;
            long long den = (2 * P.y) % p;
            lambda = (num * mod_inv(den)) % p;
        } else {
            long long num = (Q.y - P.y + p) % p;
            long long den = (Q.x - P.x + p) % p;
            lambda = (num * mod_inv(den)) % p;
        }

        long long rx = (lambda * lambda - P.x - Q.x) % p;
        rx = (rx + p) % p;
        long long ry = (lambda * (P.x - rx) - P.y) % p;
        ry = (ry + p) % p;
        return {rx, ry, false};
    }

    ECPoint multiply(ECPoint P, long long k) const {
        ECPoint res = {0, 0, true};
        while (k > 0) {
            if (k & 1) res = add(res, P);
            P = add(P, P);
            k >>= 1;
        }
        return res;
    }
};

int main() {
    // Curve y^2 = x^3 + 2x + 3 (mod 5)
    EllipticCurve ec(2, 3, 5);
    ECPoint P = {1, 1, false}; // 1^2 = 1, 1^3 + 2*1 + 3 = 6 = 1 mod 5
    ECPoint double_P = ec.add(P, P);
    assert(!double_P.is_infinity);

    std::cout << "elliptic_curve_point_addition tests passed successfully.\n";
    return 0;
}
