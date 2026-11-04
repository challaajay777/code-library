#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Gaussian Integers GCD and Norm
// Purpose: Computes Euclidean GCD and norm in the Euclidean domain of Gaussian integers Z[i].
// Time Complexity: O(log(Norm)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Numbers represented as a + b*i.

struct GaussianInt {
    long long r, i;

    long long norm() const {
        return r * r + i * i;
    }

    GaussianInt operator+(const GaussianInt& o) const { return {r + o.r, i + o.i}; }
    GaussianInt operator-(const GaussianInt& o) const { return {r - o.r, i - o.i}; }
    GaussianInt operator*(const GaussianInt& o) const {
        return {r * o.r - i * o.i, r * o.i + i * o.r};
    }

    GaussianInt operator/(const GaussianInt& o) const {
        double d = o.norm();
        double real_q = (r * o.r + i * o.i) / d;
        double imag_q = (i * o.r - r * o.i) / d;
        return {static_cast<long long>(std::round(real_q)),
                static_cast<long long>(std::round(imag_q))};
    }

    GaussianInt operator%(const GaussianInt& o) const {
        GaussianInt q = (*this) / o;
        return (*this) - (q * o);
    }
};

class GaussianGCD {
public:
    static GaussianInt gcd(GaussianInt a, GaussianInt b) {
        while (b.norm() != 0) {
            GaussianInt r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
};

int main() {
    GaussianInt a = {6, 2};
    GaussianInt b = {4, 8};
    GaussianInt g = GaussianGCD::gcd(a, b);
    assert(g.norm() == 20); // (4 + 2i) or associate

    std::cout << "gaussian_integers_gcd tests passed successfully.\n";
    return 0;
}
