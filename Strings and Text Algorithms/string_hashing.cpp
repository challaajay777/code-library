// Algorithm: Double Rolling Polynomial String Hash
// Supports: O(1) substring hash queries with randomized bases to prevent anti-hash collisions
// Indexing: 0-based substring indices [l, r]
// Complexity: O(n) preprocessing, O(1) per substring hash query, O(n) memory
// Preconditions: Moduli are large primes (e.g. 10^9+7, 10^9+9)

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct StringHash {
    static constexpr int MOD1 = 1e9 + 7;
    static constexpr int MOD2 = 1e9 + 9;
    static int BASE1;
    static int BASE2;
    static bool initialized;

    int n;
    vector<int> pref1, pref2;
    vector<int> pow1, pow2;

    static void init_bases() {
        if (initialized) return;
        mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
        BASE1 = uniform_int_distribution<int>(300, 1000)(rng) | 1;
        BASE2 = uniform_int_distribution<int>(300, 1000)(rng) | 1;
        initialized = true;
    }

    explicit StringHash(const string& s) : n((int)s.size()), pref1(n + 1, 0), pref2(n + 1, 0), pow1(n + 1, 1), pow2(n + 1, 1) {
        init_bases();
        for (int i = 0; i < n; ++i) {
            pref1[i + 1] = (int)((1LL * pref1[i] * BASE1 + s[i]) % MOD1);
            pref2[i + 1] = (int)((1LL * pref2[i] * BASE2 + s[i]) % MOD2);
            pow1[i + 1] = (int)((1LL * pow1[i] * BASE1) % MOD1);
            pow2[i + 1] = (int)((1LL * pow2[i] * BASE2) % MOD2);
        }
    }

    // Returns {hash1, hash2} of substring s[l..r] inclusive
    pair<int, int> get_hash(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        int h1 = pref1[r + 1] - (int)((1LL * pref1[l] * pow1[r - l + 1]) % MOD1);
        if (h1 < 0) h1 += MOD1;
        int h2 = pref2[r + 1] - (int)((1LL * pref2[l] * pow2[r - l + 1]) % MOD2);
        if (h2 < 0) h2 += MOD2;
        return {h1, h2};
    }
};

int StringHash::BASE1 = 313;
int StringHash::BASE2 = 317;
bool StringHash::initialized = false;
