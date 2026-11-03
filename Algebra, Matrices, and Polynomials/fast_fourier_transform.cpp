// Algorithm: Fast Fourier Transform (FFT)
// Supports: Polynomial multiplication in O(N log N) via Cooley-Tukey radix-2 FFT
// Indexing: 0-based coefficient degree [0, n - 1]
// Complexity: O(N log N) time, O(N) memory
// Preconditions: Complex floating-point precision (suitable for integer products <= 10^14)

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct FFT {
    using cd = complex<double>;
    static constexpr double PI = acos(-1.0);

    static void fft(vector<cd>& a, bool invert) {
        int n = (int)a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; ++j) {
                    cd u = a[i + j];
                    cd v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (cd& x : a) x /= n;
        }
    }

    // Multiplies two polynomials A and B: returns coefficients of A * B
    static vector<long long> multiply(const vector<long long>& a, const vector<long long>& b) {
        if (a.empty() || b.empty()) return {};
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < (int)(a.size() + b.size())) n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i) fa[i] *= fb[i];
        fft(fa, true);

        vector<long long> result(a.size() + b.size() - 1);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = (long long)round(fa[i].real());
        }
        return result;
    }
};
