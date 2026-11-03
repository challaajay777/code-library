// Test suite for Dynamic Programming algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Dynamic Programming/longest_increasing_subsequence.cpp"
#include "Dynamic Programming/knapsack_01_and_bounded.cpp"
#include "Dynamic Programming/unbounded_knapsack.cpp"
#include "Dynamic Programming/convex_hull_trick.cpp"
#include "Dynamic Programming/li_chao_tree.cpp"
#include "Dynamic Programming/divide_and_conquer_dp.cpp"
#include "Dynamic Programming/sos_dp.cpp"
#include "Dynamic Programming/digit_dp.cpp"

using namespace std;

void test_lis() {
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    auto strict_indices = LIS<int>::solve_strict(a);
    // LIS is {2, 3, 7, 101} or {2, 5, 7, 101} or {2, 3, 7, 18} -> length 4
    assert(strict_indices.size() == 4);

    vector<int> b = {1, 3, 2, 2, 4};
    assert(LIS<int>::length_non_decreasing(b) == 4); // {1, 2, 2, 4}
}

void test_knapsacks() {
    // 0-1 knapsack
    vector<pair<int, long long>> items = {{2, 3}, {3, 4}, {4, 5}, {5, 6}};
    assert(knapsack_01(5, items) == 7); // weight 2+3=5, val 3+4=7

    // Bounded knapsack
    vector<Item> b_items = {
        {2, 3, 2}, // wt 2, val 3, qty 2
        {3, 4, 1}  // wt 3, val 4, qty 1
    };
    assert(knapsack_bounded(5, b_items) == 7);

    // Unbounded knapsack
    vector<pair<int, long long>> u_items = {{2, 5}, {3, 7}};
    // W = 6: 3 items of wt 2 -> val 15, or 2 items of wt 3 -> val 14. Max is 15.
    assert(knapsack_unbounded(6, u_items) == 15);
}

void test_cht_and_li_chao() {
    LineContainer cht;
    cht.add_line(2, 3); // y = 2x + 3
    cht.add_line(1, 5); // y = x + 5
    // at x = 0: max(3, 5) = 5
    assert(cht.query_max(0) == 5);
    // at x = 3: max(2*3+3=9, 1*3+5=8) = 9
    assert(cht.query_max(3) == 9);

    // Li Chao Tree
    LiChaoTree lct(100);
    lct.add_line(2, 5);  // y = 2x + 5
    lct.add_line(-1, 20); // y = -x + 20
    // at x = 0: min(5, 20) = 5
    assert(lct.query_min(0) == 5);
    // at x = 10: min(2*10+5=25, -10+20=10) = 10
    assert(lct.query_min(10) == 10);
}

void test_dc_dp_and_sos() {
    // D&C DP: divide array into K segments minimizing sum of squared lengths
    int n = 6, K = 2;
    auto cost = [](int i, int j) -> long long {
        long long len = j - i;
        return len * len;
    };
    DCOptimizationDP<decltype(cost)> dcdp(n, K, cost);
    // Optimal split of 6 elements into 2 parts is 3 and 3 -> 3^2 + 3^2 = 18
    assert(dcdp.solve() == 18);

    // SOS DP
    int bits = 3; // masks 0..7
    vector<int> dp(8, 0);
    dp[1] = 2; // mask 001
    dp[2] = 3; // mask 010
    dp[4] = 5; // mask 100
    // Submask sum for mask 7 (111) should include dp[0]+dp[1]+dp[2]+dp[4] = 10
    SOS_DP<int> sos(bits);
    sos.compute_submask_sums(dp);
    assert(dp[7] == 10);
    assert(dp[3] == 5); // 001 + 010
}

void test_digit_dp() {
    DigitDP ddp;
    // Numbers 0..9: sum of digits = 0+1+2+...+9 = 45
    assert(ddp.count_range(0, 9) == 45);
    // Numbers 10..11: sum of digits = (1+0) + (1+1) = 3
    assert(ddp.count_range(10, 11) == 3);
}

int main() {
    cout << "[TEST] Running test_dynamic_programming suite...\n";
    test_lis();
    test_knapsacks();
    test_cht_and_li_chao();
    test_dc_dp_and_sos();
    test_digit_dp();
    cout << "[TEST] All 5 test sets in test_dynamic_programming passed!\n";
    return 0;
}
