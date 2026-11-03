// Test suite for Advanced Techniques, Search, and Optimization
#include <bits/stdc++.h>
#include <cassert>
#include "Game Theory and Search/nim_game_and_grundy.cpp"
#include "Optimization and Advanced Techniques/simulated_annealing.cpp"
#include "Specialized Data Structures and Advanced Range Queries/mo_algorithm_with_hilbert.cpp"
#include "Computational Complexity and Theory/meet_in_the_middle.cpp"

using namespace std;

void test_game_theory() {
    // Nim game: piles {3, 4, 5}
    // 3 ^ 4 ^ 5 = 2 != 0 -> winning position
    assert(GameTheory::is_winning_nim({3, 4, 5}));
    // Piles {1, 2, 3}: 1 ^ 2 ^ 3 = 0 -> losing position
    assert(!GameTheory::is_winning_nim({1, 2, 3}));

    // Subtraction game: can take 1, 2, or 3 chips
    // State n can transition to n-1, n-2, n-3
    int max_s = 10;
    vector<vector<int>> trans(max_s + 1);
    for (int i = 1; i <= max_s; ++i) {
        for (int take = 1; take <= 3 && i - take >= 0; ++take) {
            trans[i].push_back(i - take);
        }
    }
    auto g = GameTheory::compute_grundy(max_s, trans);
    // G(0) = 0, G(1) = 1, G(2) = 2, G(3) = 3, G(4) = 0, G(n) = n % 4
    for (int i = 0; i <= max_s; ++i) {
        assert(g[i] == i % 4);
    }
}

void test_simulated_annealing() {
    // 4 cities in a square: (0,0), (0,10), (10,10), (10,0)
    // Distance matrix:
    // 0 - 1: 10
    // 1 - 2: 10
    // 2 - 3: 10
    // 3 - 0: 10
    // Diagonals 0-2 and 1-3: 14
    vector<vector<long long>> dist = {
        {0, 10, 14, 10},
        {10, 0, 10, 14},
        {14, 10, 0, 10},
        {10, 14, 10, 0}
    };
    auto [cost, path] = SimulatedAnnealing::solve_tsp(dist, 5000, 1337);
    // Optimal perimeter tour cost is 40
    assert(cost == 40);
}

void test_mo_hilbert() {
    // Count distinct elements in range
    vector<int> a = {1, 2, 1, 3, 2, 4};
    int n = (int)a.size();
    MoHilbert mo(n);
    mo.add_query(0, 2, 0); // {1, 2, 1} -> 2 distinct
    mo.add_query(1, 4, 1); // {2, 1, 3, 2} -> 3 distinct
    mo.add_query(0, 5, 2); // all 6 -> 4 distinct {1, 2, 3, 4}

    vector<int> freq(10, 0);
    int distinct = 0;
    vector<int> ans(3, 0);

    auto add = [&](int idx) {
        if (freq[a[idx]] == 0) distinct++;
        freq[a[idx]]++;
    };

    auto remove = [&](int idx) {
        freq[a[idx]]--;
        if (freq[a[idx]] == 0) distinct--;
    };

    auto report = [&](int q_id) {
        ans[q_id] = distinct;
    };

    mo.solve(add, remove, report);

    assert(ans[0] == 2);
    assert(ans[1] == 3);
    assert(ans[2] == 4);
}

void test_meet_in_the_middle() {
    vector<long long> a = {3, 34, 4, 12, 5, 2};
    assert(MeetInTheMiddle::has_subset_sum(a, 9)); // 4 + 5 = 9
    assert(!MeetInTheMiddle::has_subset_sum(a, 30));
    assert(MeetInTheMiddle::max_subset_sum_le(a, 30) == 26); // 12 + 5 + 4 + 3 + 2 = 26
}

int main() {
    cout << "[TEST] Running test_advanced_techniques suite...\n";
    test_game_theory();
    test_simulated_annealing();
    test_mo_hilbert();
    test_meet_in_the_middle();
    cout << "[TEST] All 4 test sets in test_advanced_techniques passed!\n";
    return 0;
}
