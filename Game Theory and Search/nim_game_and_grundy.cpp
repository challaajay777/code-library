// Algorithm: Sprague-Grundy Theorem & Nim Sum
// Supports: Nim game evaluation, MEX (Minimum Excludant) computation, impartial games
// Indexing: 0-based game states
// Complexity: O(states * transitions) for Grundy values, O(piles) for Nim sum
// Preconditions: Finite impartial game under normal play convention (last player to move wins)

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct GameTheory {
    // Computes Minimum Excludant (MEX) of a set of integers
    static int mex(const vector<int>& values) {
        int n = (int)values.size();
        vector<bool> present(n + 1, false);
        for (int x : values) {
            if (x >= 0 && x <= n) {
                present[x] = true;
            }
        }
        for (int i = 0; i <= n; ++i) {
            if (!present[i]) return i;
        }
        return n + 1;
    }

    // Evaluates standard Nim game: returns true if first player has winning strategy
    static bool is_winning_nim(const vector<long long>& piles) {
        long long xor_sum = 0;
        for (long long p : piles) {
            xor_sum ^= p;
        }
        return xor_sum != 0;
    }

    // Computes Grundy values for all states 0..max_state given DAG transitions
    static vector<int> compute_grundy(int max_state, const vector<vector<int>>& transitions) {
        assert(max_state >= 0 && (int)transitions.size() > max_state);
        vector<int> g(max_state + 1, 0);

        for (int state = 0; state <= max_state; ++state) {
            vector<int> reachable;
            for (int next_state : transitions[state]) {
                reachable.push_back(g[next_state]);
            }
            g[state] = mex(reachable);
        }
        return g;
    }
};
