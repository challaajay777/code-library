// Test suite for Number Theory algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Number Theory/sieve_of_eratosthenes.cpp"
#include "Number Theory/linear_sieve.cpp"
#include "Number Theory/extended_gcd_and_modular_inverse.cpp"
#include "Number Theory/chinese_remainder_theorem.cpp"
#include "Number Theory/euler_totient.cpp"
#include "Number Theory/miller_rabin_primality.cpp"
#include "Number Theory/pollards_rho.cpp"

using namespace std;

void test_sieves() {
    Sieve s(30);
    assert(!s.check(0) && !s.check(1));
    assert(s.check(2) && s.check(3) && s.check(5) && s.check(29));
    assert(!s.check(4) && !s.check(27));
    assert(s.primes.size() == 10); // 2, 3, 5, 7, 11, 13, 17, 19, 23, 29

    LinearSieve ls(100);
    assert(ls.spf[12] == 2);
    assert(ls.spf[49] == 7);
    auto factors = ls.factorize(60); // 2^2 * 3 * 5
    vector<pair<int, int>> exp = {{2, 2}, {3, 1}, {5, 1}};
    assert(factors == exp);
}

void test_extgcd_and_crt() {
    long long x, y;
    long long g = ExtendedGCD::extgcd(35, 15, x, y);
    assert(g == 5);
    assert(35 * x + 15 * y == 5);

    long long inv = ExtendedGCD::mod_inverse(3, 11);
    assert(inv == 4); // 3 * 4 = 12 = 1 (mod 11)
    assert(ExtendedGCD::mod_inverse(6, 9) == -1); // not coprime

    // CRT: x = 2 (mod 3), x = 3 (mod 5), x = 2 (mod 7)
    // Solution: x = 23 (mod 105)
    vector<long long> rems = {2, 3, 2};
    vector<long long> mods = {3, 5, 7};
    auto crt_res = CRT::solve(rems, mods);
    assert(crt_res.first == 23 && crt_res.second == 105);

    // Non-coprime CRT: x = 2 (mod 4), x = 4 (mod 6) -> x = 10 (mod 12)
    auto crt_nc = CRT::solve({2, 4}, {4, 6});
    assert(crt_nc.first == 10 && crt_nc.second == 12);
}

void test_totient() {
    assert(EulerTotient::phi(1) == 1);
    assert(EulerTotient::phi(9) == 6); // 1, 2, 4, 5, 7, 8
    assert(EulerTotient::phi(13) == 12);

    auto phi_arr = EulerTotient::sieve_phi(20);
    assert(phi_arr[9] == 6);
    assert(phi_arr[13] == 12);
    assert(phi_arr[20] == 8);
}

void test_primality_and_rho() {
    assert(!MillerRabin::is_prime(0) && !MillerRabin::is_prime(1));
    assert(MillerRabin::is_prime(2) && MillerRabin::is_prime(3));
    assert(!MillerRabin::is_prime(4));
    // Carmichael number 561 = 3 * 11 * 17
    assert(!MillerRabin::is_prime(561));
    // Large prime 10^9 + 7
    assert(MillerRabin::is_prime(1000000007ULL));
    // Large prime 2^61 - 1 (Mersenne prime M61)
    assert(MillerRabin::is_prime((1ULL << 61) - 1));

    // Pollard's Rho
    unsigned long long num = 123456789012345ULL; // 3 * 5 * 8230452600823
    auto facs = PollardsRho::factorize(num);
    unsigned long long prod = 1;
    for (auto f : facs) {
        assert(MillerRabin::is_prime(f));
        prod *= f;
    }
    assert(prod == num);
}

int main() {
    cout << "[TEST] Running test_number_theory suite...\n";
    test_sieves();
    test_extgcd_and_crt();
    test_totient();
    test_primality_and_rho();
    cout << "[TEST] All 4 test sets in test_number_theory passed!\n";
    return 0;
}
