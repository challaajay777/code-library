// Algorithm: Simulated Annealing Metaheuristic
// Supports: General local search optimization, cooling schedule, Metropolis acceptance criterion
// Complexity: Dependent on time limit and iteration budget
// Preconditions: Objective function evaluable in fast time; deterministic PRNG

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct SimulatedAnnealing {
    static constexpr double DEFAULT_INIT_TEMP = 1e5;
    static constexpr double DEFAULT_FINAL_TEMP = 1e-4;
    static constexpr double DEFAULT_COOLING = 0.9995;

    // Solves Traveling Salesperson Problem (TSP) on distance matrix
    static pair<long long, vector<int>> solve_tsp(const vector<vector<long long>>& dist_matrix,
                                                  int iterations = 100000,
                                                  uint32_t seed = 42) {
        int n = (int)dist_matrix.size();
        assert(n >= 2);

        mt19937 rng(seed);
        uniform_real_distribution<double> dist_01(0.0, 1.0);

        vector<int> current_path(n);
        iota(current_path.begin(), current_path.end(), 0);
        shuffle(current_path.begin(), current_path.end(), rng);

        auto calc_cost = [&](const vector<int>& p) -> long long {
            long long c = 0;
            for (int i = 0; i < n; ++i) {
                c += dist_matrix[p[i]][p[(i + 1) % n]];
            }
            return c;
        };

        long long current_cost = calc_cost(current_path);
        long long best_cost = current_cost;
        vector<int> best_path = current_path;

        double temp = DEFAULT_INIT_TEMP;
        double cooling_factor = pow(DEFAULT_FINAL_TEMP / DEFAULT_INIT_TEMP, 1.0 / iterations);

        for (int iter = 0; iter < iterations; ++iter) {
            int i = rng() % n;
            int j = rng() % n;
            if (i == j) continue;
            if (i > j) swap(i, j);

            // 2-opt move: reverse subsegment [i, j]
            reverse(current_path.begin() + i, current_path.begin() + j + 1);
            long long new_cost = calc_cost(current_path);
            long long delta = new_cost - current_cost;

            if (delta < 0 || exp(-delta / temp) > dist_01(rng)) {
                current_cost = new_cost;
                if (current_cost < best_cost) {
                    best_cost = current_cost;
                    best_path = current_path;
                }
            } else {
                // Reject: revert move
                reverse(current_path.begin() + i, current_path.begin() + j + 1);
            }
            temp *= cooling_factor;
        }

        return {best_cost, best_path};
    }
};
