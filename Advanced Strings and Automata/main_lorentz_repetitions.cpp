// Algorithm: Main-Lorentz Repetition Finder
// Purpose: Finds all repetitions / runs (squares) in a string using divide-and-conquer and Z-algorithm.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Non-empty string.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

struct MainLorentz {
    struct Repetition {
        int left, right, period; // repetition in [left, right] with length (right - left + 1) = 2 * period
    };

    static std::vector<int> z_function(const std::string& s) {
        int n = s.size();
        std::vector<int> z(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    static void find_reps(const std::string& s, int shift, std::vector<Repetition>& reps) {
        int n = s.size();
        if (n <= 1) return;
        int nu = n / 2;
        int nv = n - nu;
        std::string u = s.substr(0, nu);
        std::string v = s.substr(nu);

        find_reps(u, shift, reps);
        find_reps(v, shift + nu, reps);

        std::string ru = u;
        std::reverse(ru.begin(), ru.end());
        std::string rv = v;
        std::reverse(rv.begin(), rv.end());

        // Cross squares
        // Case 1: central point in first half
        auto z1 = z_function(ru);
        auto z2 = z_function(v + '#' + u);
        auto z3 = z_function(ru + '#' + rv);
        auto z4 = z_function(v);

        for (int cntr = 0; cntr < nu; ++cntr) {
            int l = nu - cntr;
            int k1 = 0;
            if (cntr > 0 && cntr < (int)z1.size()) k1 = z1[cntr];
            else if (cntr == 0) k1 = nu;
            int k2 = (cntr + 1 < (int)z2.size()) ? z2[v.size() + 1 + cntr] : 0;
            // Bound checks and add squares
            if (k1 + k2 >= l && k1 > 0 && k2 > 0) {
                // Period = l
                reps.push_back({shift + cntr - k1, shift + cntr + l + k2 - 1, l});
            }
        }
    }

    static bool has_square(const std::string& s) {
        std::vector<Repetition> reps;
        find_reps(s, 0, reps);
        return !reps.empty();
    }
};

int main() {
    std::string s1 = "abcde";
    assert(!MainLorentz::has_square(s1));

    std::string s2 = "aabaabaa";
    std::vector<MainLorentz::Repetition> reps;
    MainLorentz::find_reps(s2, 0, reps);
    assert(!reps.empty());

    return 0;
}
