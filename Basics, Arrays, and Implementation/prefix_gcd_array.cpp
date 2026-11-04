#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Prefix and Suffix GCD
// Purpose: Computes GCD of the entire array excluding one element in O(1) per candidate using prefix and suffix GCD tables.
// Time Complexity: O(N log(max_A)) preprocessing, O(1) query
// Space Complexity: O(N) auxiliary space
// Preconditions: Elements are non-negative integers.

class PrefixSuffixGcd {
private:
    int n;
    std::vector<long long> pref;
    std::vector<long long> suff;

public:
    explicit PrefixSuffixGcd(const std::vector<long long>& a) : n(a.size()), pref(n), suff(n) {
        assert(n > 0);
        pref[0] = a[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = std::gcd(pref[i - 1], a[i]);
        }
        suff[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suff[i] = std::gcd(suff[i + 1], a[i]);
        }
    }

    // Returns GCD of all elements except a[i]
    long long gcd_excluding(int i) const {
        assert(n >= 2 && i >= 0 && i < n);
        if (i == 0) return suff[1];
        if (i == n - 1) return pref[n - 2];
        return std::gcd(pref[i - 1], suff[i + 1]);
    }

    // Finds maximum GCD achievable by removing exactly one element
    long long max_gcd_after_removal() const {
        long long best = 0;
        for (int i = 0; i < n; ++i) {
            best = std::max(best, gcd_excluding(i));
        }
        return best;
    }
};

int main() {
    std::vector<long long> a = {12, 15, 18, 7};
    PrefixSuffixGcd psg(a);

    // Removing 7 leaves {12, 15, 18} with gcd = 3
    assert(psg.gcd_excluding(3) == 3);
    assert(psg.max_gcd_after_removal() == 3);

    std::cout << "prefix_gcd_array tests passed successfully.\n";
    return 0;
}
