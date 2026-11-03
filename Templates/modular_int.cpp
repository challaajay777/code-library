// Algorithm: Modular Integer (Mint)
// Supports: Addition, subtraction, multiplication, division (via modular inverse), power
// Complexity: O(1) for +, -, *, O(log MOD) for division and power
// Preconditions: MOD is prime for arbitrary division; gcd(v, MOD) == 1 for invertibility

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <int MOD>
struct Mint {
    int v;
    static_assert(MOD > 0, "MOD must be positive");

    Mint() : v(0) {}
    Mint(long long _v) {
        v = (int)(_v % MOD);
        if (v < 0) v += MOD;
    }

    Mint& operator+=(const Mint& o) {
        v += o.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    Mint& operator-=(const Mint& o) {
        v -= o.v;
        if (v < 0) v += MOD;
        return *this;
    }
    Mint& operator*=(const Mint& o) {
        v = (int)((1LL * v * o.v) % MOD);
        return *this;
    }

    Mint pow(long long p) const {
        assert(p >= 0);
        Mint res(1), a(*this);
        while (p > 0) {
            if (p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }

    Mint inv() const {
        int a = v, m = MOD, u = 0, u1 = 1;
        assert(a != 0 && "Division by zero");
        while (a != 0) {
            int q = m / a;
            m -= q * a; swap(a, m);
            u -= q * u1; swap(u, u1);
        }
        assert(m == 1 && "Modular inverse does not exist (not coprime)");
        if (u < 0) u += MOD;
        return Mint(u);
    }

    Mint& operator/=(const Mint& o) {
        return *this *= o.inv();
    }

    friend Mint operator+(Mint a, const Mint& b) { return a += b; }
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
    friend bool operator==(const Mint& a, const Mint& b) { return a.v == b.v; }
    friend bool operator!=(const Mint& a, const Mint& b) { return a.v != b.v; }

    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.v; }
    friend istream& operator>>(istream& is, Mint& m) {
        long long val;
        is >> val;
        m = Mint(val);
        return is;
    }
};

using mint = Mint<1000000007>;
using mint998 = Mint<998244353>;
