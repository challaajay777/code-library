// Test suite for Combinatorics and Probability algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Combinatorics and Probability/combinatorics_mod.cpp"
#include "Combinatorics and Probability/lucas_theorem.cpp"
#include "Combinatorics and Probability/catalan_numbers.cpp"
#include "Combinatorics and Probability/derangements.cpp"
#include "Combinatorics and Probability/birthday_paradox.cpp"

using namespace std;

void test_combinatorics_mod() {
    Combinatorics<1000000007> comb(20);
    assert(comb.nCr(5, 2) == 10);
    assert(comb.nCr(6, 3) == 20);
    assert(comb.nPr(5, 2) == 20);
    assert(comb.nCr(5, 0) == 1);
    assert(comb.nCr(5, 5) == 1);
    assert(comb.nCr(5, 6) == 0);

    // Stars and bars: 3 items into 2 bins: (3+2-1) C (2-1) = 4 C 1 = 4
    assert(comb.stars_and_bars(3, 2) == 4);
}

void test_lucas() {
    // Prime p = 7
    LucasTheorem lt(7);
    // 10 C 3: 10 = 1*7 + 3, 3 = 0*7 + 3
    // Lucas: (1 C 0) * (3 C 3) = 1 * 1 = 1 (mod 7)
    // Direct: 10 C 3 = 120 = 17 * 7 + 1 = 1 (mod 7)
    assert(lt.nCr(10, 3) == 1);
    assert(lt.nCr(1000000000000LL, 1000000000000LL) == 1);
}

void test_catalan_and_derangements() {
    CatalanNumbers<1000000007> cat(10);
    assert(cat.get(0) == 1);
    assert(cat.get(1) == 1);
    assert(cat.get(2) == 2);
    assert(cat.get(3) == 5);
    assert(cat.get(4) == 14);
    assert(cat.get(5) == 42);

    Derangements<1000000007> der(10);
    assert(der.get(0) == 1);
    assert(der.get(1) == 0);
    assert(der.get(2) == 1);
    assert(der.get(3) == 2);
    assert(der.get(4) == 9);
    assert(der.get(5) == 44);
}

void test_probability() {
    // Standard birthday paradox: with 23 people and 365 days, P >= 0.5
    double p23 = ProbabilityUtils::collision_probability(23, 365);
    assert(p23 > 0.50);
    double p22 = ProbabilityUtils::collision_probability(22, 365);
    assert(p22 < 0.50);

    long long req = ProbabilityUtils::required_samples_for_collision(365, 0.5);
    assert(req == 23);

    // Coin flips: 4 flips, 2 heads, p = 0.5: 6 * (1/16) = 0.375
    double b_pmf = ProbabilityUtils::binomial_pmf(4, 2, 0.5);
    assert(abs(b_pmf - 0.375) < 1e-9);
}

int main() {
    cout << "[TEST] Running test_combinatorics suite...\n";
    test_combinatorics_mod();
    test_lucas();
    test_catalan_and_derangements();
    test_probability();
    cout << "[TEST] All 4 test sets in test_combinatorics passed!\n";
    return 0;
}
