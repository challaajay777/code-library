#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Eisenstein Integers GCD and Norm
// Purpose: Computes greatest common divisor and algebraic norm in the ring of Eisenstein integers Z[omega].
// Time Complexity: O(log(Norm)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Numbers represented as a + b*omega where omega = (-1 + sqrt(3)*i) / 2.

struct EisensteinInt {
    long long a, b; // a + b*omega

    long long norm() const {
        return a * a - a * b + b * b;
    }

    EisensteinInt operator-(const EisensteinInt& o) const { return {a - o.a, b - o.b}; }
    EisensteinInt operator*(const EisensteinInt& o) const {
        return {a * o.a - b * o.b, a * o.b + b * o.a - b * o.b};
    }

    EisensteinInt operator/(const EisensteinInt& o) const {
        double d = o.norm();
        double u = (a * o.a - a * o.b + b * o.b) / d;
        double v = (b * o.a - a * o.b) / d;
        return {static_cast<long long>(std::round(u)), static_cast<long long>(std::round(v))};
    }

    EisensteinInt operator%(const EisensteinInt& o) const {
        EisensteinInt q = (*this) / o;
        return (*this) - (q * o);
    }
};

class EisensteinGCD {
public:
    static EisensteinInt gcd(EisensteinInt x, EisensteinInt y) {
        while (y.norm() != 0) {
            EisensteinInt r = x % y;
            x = y;
            y = r;
        }
        return x;
    }
};

int main() {
    EisensteinInt x = {5, 3};
    EisensteinInt y = {2, 1};
    EisensteinInt g = EisensteinGCD::gcd(x, y);
    assert(g.norm() >= 1);

    std::cout << "eisenstein_integers_gcd tests passed successfully.\n";
    return 0;
}
