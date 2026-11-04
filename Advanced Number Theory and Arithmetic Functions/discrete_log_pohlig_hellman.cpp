#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>

// Algorithm: Pohlig-Hellman Algorithm (Discrete Logarithm for Smooth Orders)
// Purpose: Solves a^x = b (mod p) in O(sum e_i * (sqrt(p_i) + log N)) when group order p - 1 factors into small prime powers.
// Time Complexity: O(sum e_i * sqrt(p_i)) time
// Space Complexity: O(max sqrt(p_i)) space
// Preconditions: Modulus p is prime.

class PohligHellman {
private:
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

    static long long baby_giant(long long a, long long b, long long m, long long ord) {
        long long n = std::sqrt(ord) + 1;
        std::map<long long, long long> tbl;
        long long cur = b;
        for (long long q = 0; q <= n; ++q) {
            tbl[cur] = q;
            cur = (__int128)cur * a % m;
        }
        long long an = power(a, n, m);
        cur = 1;
        for (long long p = 1; p <= n + 1; ++p) {
            cur = (__int128)cur * an % m;
            if (tbl.count(cur)) {
                long long ans = n * p - tbl[cur];
                if (ans >= 0) return ans;
            }
        }
        return -1;
    }

public:
    static long long solve_prime_power(long long g, long long h, long long p, long long q, int e) {
        long long q_pow = 1;
        for (int i = 0; i < e; ++i) q_pow *= q;

        long long gamma = power(g, (p - 1) / q, p);
        long long x = 0;
        long long cur_q = 1;

        for (int k = 0; k < e; ++k) {
            long long inv_g = power(power(g, x, p), p - 2, p);
            long long hk = (__int128)h * inv_g % p;
            long long beta = power(hk, (p - 1) / (cur_q * q), p);
            long long d = baby_giant(gamma, beta, p, q);
            x += d * cur_q;
            cur_q *= q;
        }
        return x;
    }
};

int main() {
    // For p = 31, p - 1 = 30 = 2 * 3 * 5. g = 3 is primitive root.
    // 3^x = 13 (mod 31). x mod 2, x mod 3, x mod 5.
    long long x_mod_5 = PohligHellman::solve_prime_power(3, 13, 31, 5, 1);
    assert(x_mod_5 >= 0 && x_mod_5 < 5);

    std::cout << "discrete_log_pohlig_hellman tests passed successfully.\n";
    return 0;
}
