// Algorithm: Chinese Remainder Theorem (CRT)
// Supports: Solving systems of linear congruences x = r_i (mod m_i) for general non-coprime moduli
// Indexing: 0-based congruence indices
// Complexity: O(k * log(lcm(m))) time, O(1) space
// Preconditions: Moduli m_i > 0; returns {-1, -1} if no simultaneous solution exists

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct CRT {
    static long long extgcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        long long x1, y1;
        long long g = extgcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return g;
    }

    // Merges two congruences: x = r1 (mod m1) and x = r2 (mod m2)
    // Returns {r, m} such that x = r (mod m) where m = lcm(m1, m2), or {-1, -1} on failure
    static pair<long long, long long> merge(long long r1, long long m1, long long r2, long long m2) {
        if (m1 == -1 || m2 == -1) return {-1, -1};
        long long p, q;
        long long g = extgcd(m1, m2, p, q);
        if ((r2 - r1) % g != 0) return {-1, -1}; // Incompatible

        long long mod = (m1 / g) * m2;
        long long step = (r2 - r1) / g;
        long long ans = (r1 + (__int128)step * p % (m2 / g) * m1) % mod;
        if (ans < 0) ans += mod;
        return {ans, mod};
    }

    // Solves system of congruences: x = rems[i] (mod mods[i])
    // Returns pair {remainder, combined_modulus}, or {-1, -1} if contradiction occurs
    static pair<long long, long long> solve(const vector<long long>& rems, const vector<long long>& mods) {
        assert(rems.size() == mods.size());
        long long cur_rem = 0, cur_mod = 1;

        for (size_t i = 0; i < rems.size(); ++i) {
            auto res = merge(cur_rem, cur_mod, rems[i], mods[i]);
            if (res.second == -1) return {-1, -1};
            cur_rem = res.first;
            cur_mod = res.second;
        }
        return {cur_rem, cur_mod};
    }
};
