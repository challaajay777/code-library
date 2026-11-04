#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Prefix Products with Zero Counts
// Purpose: Answers range modular products in O(1) time in arrays containing zero values by tracking zero frequencies.
// Time Complexity: O(N) preprocessing, O(1) query
// Space Complexity: O(N) space
// Preconditions: Modulus M is prime for modular inverse.

class PrefixProductWithZeros {
private:
    int n;
    long long mod;
    std::vector<int> zero_pref;
    std::vector<long long> non_zero_prod;
    std::vector<long long> inv_prod;

    long long power(long long base, long long exp) const {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

    long long mod_inverse(long long x) const {
        return power(x, mod - 2);
    }

public:
    PrefixProductWithZeros(const std::vector<long long>& a, long long m = 1e9 + 7) : n(a.size()), mod(m) {
        zero_pref.assign(n + 1, 0);
        non_zero_prod.assign(n + 1, 1);
        inv_prod.assign(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            zero_pref[i + 1] = zero_pref[i] + (a[i] == 0 ? 1 : 0);
            long long val = (a[i] == 0 ? 1LL : (a[i] % mod + mod) % mod);
            non_zero_prod[i + 1] = (non_zero_prod[i] * val) % mod;
            inv_prod[i + 1] = mod_inverse(non_zero_prod[i + 1]);
        }
    }

    long long query(int l, int r) const {
        assert(l >= 0 && r < n && l <= r);
        int zeros = zero_pref[r + 1] - zero_pref[l];
        if (zeros > 0) return 0;
        return (non_zero_prod[r + 1] * inv_prod[l]) % mod;
    }
};

int main() {
    std::vector<long long> a = {2, 3, 0, 4, 5};
    PrefixProductWithZeros pp(a, 1000000007);

    assert(pp.query(0, 1) == 6);
    assert(pp.query(0, 2) == 0);
    assert(pp.query(1, 3) == 0);
    assert(pp.query(3, 4) == 20);

    std::cout << "prefix_product_with_zeros tests passed successfully.\n";
    return 0;
}
