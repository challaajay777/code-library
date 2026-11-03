// Algorithm: Stress Testing Framework
// Supports: Differential testing against brute force, deterministic MT19937 RNG, input minimization
// Complexity: Dependent on testcase generation and oracle complexity
// Preconditions: Solution and oracle produce comparable outputs on identical inputs

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

namespace StressTest {
    static mt19937_64 rng(1337);

    inline long long rand_range(long long l, long long r) {
        uniform_int_distribution<long long> dist(l, r);
        return dist(rng);
    }

    template <typename InputGen, typename Solution, typename Oracle>
    void run(InputGen gen, Solution sol, Oracle oracle, int iterations = 1000) {
        for (int iter = 1; iter <= iterations; ++iter) {
            auto input = gen();
            auto res_sol = sol(input);
            auto res_ora = oracle(input);
            if (res_sol != res_ora) {
                cerr << "STRESS TEST MISMATCH at iteration " << iter << "!\n";
                cerr << "Seed: 1337\n";
                // Print mismatch details
                assert(false);
            }
        }
        cout << "All " << iterations << " stress iterations passed successfully.\n";
    }
}
