// Algorithm: Number Theoretic Transform (NTT)
// Supports: Exact integer polynomial multiplication modulo 998244353 (primitive root 3)
// Indexing: 0-based coefficient degree [0, n - 1]
// Complexity: O(N log N) time, O(N) memory
// Preconditions: Modulo MOD = 998244353, primitive root G = 3

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct NTT {
    static constexpr int MOD = 998244353;
    static constexpr int G = 3;

    static int power_mod(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return (int)res;
    }

    static int mod_inverse(int n) {
        return power_mod(n, MOD - 2);
    }

    static void ntt(vector<int>& a, bool invert) {
        int n = (int)a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            int wlen = power_mod(G, (MOD - 1) / len);
            if (invert) wlen = mod_inverse(wlen);
            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len / 2; ++j) {
                    int u = a[i + j];
                    int v = (int)(1LL * a[i + j + len / 2] * w % MOD);
                    a[i + j] = (u + v >= MOD ? u + v - MOD : u + v);
                    a[i + j + len / 2] = (u - v < 0 ? u - v + MOD : u - v);
                    w = (int)(1LL * w * wlen % MOD);
                }
            }
        }

        if (invert) {
            int n_inv = mod_inverse(n);
            for (int& x : a) {
                x = (int)(1LL * x * n_inv % MOD);
            }
        }
    }

    // Multiplies two polynomials A and B modulo 998244353
    static vector<int> multiply(const vector<int>& a, const vector<int>& b) {
        if (a.empty() || b.empty()) return {};
        int need = (int)(a.size() + b.size() - 1);
        int n = 1;
        while (n < need) n <<= 1;

        vector<int> fa(n, 0), fb(n, 0);
        copy(a.begin(), a.end(), fa.begin());
        copy(b.begin(), b.end(), fb.begin());

        ntt(fa, false);
        ntt(fb, false);
        for (int i = 0; i < n; ++i) {
            fa[i] = (int)(1LL * fa[i] * fb[i] % MOD);
        }
        ntt(fa, true);
        fa.resize(need);
        return fa;
    }
};
