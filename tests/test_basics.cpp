// Test suite for Basics, Arrays, and Implementation
#include <bits/stdc++.h>
#include <cassert>
#include "Basics, Arrays, and Implementation/prefix_sums_1d.cpp"
#include "Basics, Arrays, and Implementation/prefix_sums_2d.cpp"
#include "Basics, Arrays, and Implementation/difference_array_1d.cpp"
#include "Basics, Arrays, and Implementation/difference_array_2d.cpp"
#include "Basics, Arrays, and Implementation/coordinate_compression.cpp"
#include "Basics, Arrays, and Implementation/sliding_window_min_max.cpp"
#include "Basics, Arrays, and Implementation/maximum_subarray_sum.cpp"
#include "Basics, Arrays, and Implementation/binary_search_helpers.cpp"
#include "Basics, Arrays, and Implementation/ternary_search.cpp"
#include "Basics, Arrays, and Implementation/misra_gries_heavy_hitters.cpp"
#include "Basics, Arrays, and Implementation/interval_operations.cpp"
#include "Basics, Arrays, and Implementation/fast_exponentiation.cpp"

using namespace std;

void test_prefix_sums_1d() {
    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    PrefixSums1D<long long> ps(a);
    assert(ps.query(0, 0) == 3);
    assert(ps.query(0, 7) == 31);
    assert(ps.query(2, 4) == 4 + 1 + 5);
}

void test_prefix_sums_2d() {
    vector<vector<int>> g = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    PrefixSums2D<int> ps2(g);
    assert(ps2.query(0, 0, 0, 0) == 1);
    assert(ps2.query(0, 0, 2, 2) == 45);
    assert(ps2.query(1, 1, 2, 2) == 5 + 6 + 8 + 9);
}

void test_difference_arrays() {
    DifferenceArray1D<int> da(5);
    da.add_range(1, 3, 10);
    da.add_range(2, 4, 5);
    auto res = da.build();
    vector<int> expected = {0, 10, 15, 15, 5};
    assert(res == expected);

    DifferenceArray2D<int> da2(3, 3);
    da2.add_rect(0, 0, 1, 1, 2);
    da2.add_rect(1, 1, 2, 2, 3);
    auto g = da2.build();
    assert(g[0][0] == 2);
    assert(g[1][1] == 5);
    assert(g[2][2] == 3);
}

void test_coordinate_compression() {
    vector<int> raw = {100, -50, 100, 25, 0, -50};
    CoordinateCompression<int> cc(raw);
    assert(cc.size() == 4);
    assert(cc.get_rank(-50) == 0);
    assert(cc.get_rank(0) == 1);
    assert(cc.get_rank(25) == 2);
    assert(cc.get_rank(100) == 3);
    assert(cc.get_value(2) == 25);
}

void test_sliding_window() {
    vector<int> a = {1, 3, -1, -3, 5, 3, 6, 7};
    auto mins = sliding_window_minimum(a, 3);
    vector<int> exp_min = {-1, -3, -3, -3, 3, 3};
    assert(mins == exp_min);

    auto maxs = sliding_window_maximum(a, 3);
    vector<int> exp_max = {3, 3, 5, 5, 6, 7};
    assert(maxs == exp_max);
}

void test_kadane() {
    vector<long long> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto res = kadane(a);
    assert(res.sum == 6);
    assert(res.left == 3 && res.right == 6);

    vector<long long> circ = {5, -3, 5};
    assert(max_circular_subarray_sum(circ) == 10);

    vector<long long> all_neg = {-5, -2, -8};
    assert(max_circular_subarray_sum(all_neg) == -2);
}

void test_binary_search() {
    assert(integer_sqrt(0) == 0);
    assert(integer_sqrt(1) == 1);
    assert(integer_sqrt(15) == 3);
    assert(integer_sqrt(16) == 4);
    assert(integer_sqrt(1000000000000000000ULL) == 1000000000ULL);

    vector<int> sorted = {2, 4, 6, 8, 10};
    int ft = first_true(0, 4, [&](int i) { return sorted[i] >= 6; });
    assert(ft == 2);
    int lt = last_true(0, 4, [&](int i) { return sorted[i] <= 7; });
    assert(lt == 2);
}

void test_ternary_search() {
    // Unimodal quadratic f(x) = (x - 7)^2 + 3, minimum at x = 7
    auto f = [](long long x) { return (x - 7) * (x - 7) + 3; };
    assert(ternary_search_int_min(-100LL, 100LL, f) == 7);
}

void test_heavy_hitters() {
    vector<int> a = {2, 2, 1, 1, 1, 2, 2};
    auto maj = boyer_moore_majority(a);
    assert(maj.first && maj.second == 2);

    vector<int> b = {1, 2, 3, 4};
    auto no_maj = boyer_moore_majority(b);
    assert(!no_maj.first);

    vector<int> mg_a = {1, 1, 1, 2, 2, 3}; // n=6, k=3, threshold > 2 -> {1}
    auto mg = misra_gries(mg_a, 3);
    assert(find(mg.begin(), mg.end(), 1) != mg.end());
}

void test_intervals() {
    vector<Interval> ivs = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    auto merged = merge_intervals(ivs);
    assert(merged.size() == 3);
    assert(merged[0].l == 1 && merged[0].r == 6);
}

void test_exponentiation() {
    assert(power_mod(2, 10, 1000) == 24);
    assert(power_mod(3, 0, 1000) == 1);

    long long mod = 1e9 + 7;
    // F(0)=0, F(1)=1, F(2)=1, F(3)=2, F(4)=3, F(5)=5, F(6)=8, F(7)=13, F(8)=21, F(9)=34, F(10)=55
    assert(get_fibonacci(0, mod) == 0);
    assert(get_fibonacci(1, mod) == 1);
    assert(get_fibonacci(10, mod) == 55);
}

int main() {
    cout << "[TEST] Running test_basics suite...\n";
    test_prefix_sums_1d();
    test_prefix_sums_2d();
    test_difference_arrays();
    test_coordinate_compression();
    test_sliding_window();
    test_kadane();
    test_binary_search();
    test_ternary_search();
    test_heavy_hitters();
    test_intervals();
    test_exponentiation();
    cout << "[TEST] All 11 test sets in test_basics passed!\n";
    return 0;
}
