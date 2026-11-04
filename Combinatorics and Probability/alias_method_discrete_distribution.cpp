#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Vose's Alias Method (O(1) Discrete Distribution Sampling)
// Purpose: Samples from an arbitrary discrete probability distribution over N outcomes in O(1) time after O(N) setup.
// Time Complexity: O(N) initialization, O(1) per random sample
// Space Complexity: O(N) space for probability and alias tables
// Preconditions: Probabilities non-negative and sum to 1.0.

class AliasMethod {
private:
    int n;
    std::vector<double> prob;
    std::vector<int> alias;

public:
    explicit AliasMethod(const std::vector<double>& p) : n(p.size()), prob(n), alias(n) {
        std::vector<double> scaled_p(n);
        std::vector<int> small, large;

        for (int i = 0; i < n; ++i) {
            scaled_p[i] = p[i] * n;
            if (scaled_p[i] < 1.0) small.push_back(i);
            else large.push_back(i);
        }

        while (!small.empty() && !large.empty()) {
            int l = small.back(); small.pop_back();
            int g = large.back(); large.pop_back();

            prob[l] = scaled_p[l];
            alias[l] = g;

            scaled_p[g] = (scaled_p[g] + scaled_p[l]) - 1.0;
            if (scaled_p[g] < 1.0) small.push_back(g);
            else large.push_back(g);
        }

        while (!large.empty()) {
            prob[large.back()] = 1.0;
            large.pop_back();
        }
        while (!small.empty()) {
            prob[small.back()] = 1.0;
            small.pop_back();
        }
    }

    int sample(double rand_unit, double rand_fair) const {
        int i = static_cast<int>(rand_fair * n);
        if (i >= n) i = n - 1;
        return (rand_unit < prob[i]) ? i : alias[i];
    }
};

int main() {
    std::vector<double> p = {0.1, 0.4, 0.5};
    AliasMethod am(p);
    int outcome = am.sample(0.05, 0.0);
    assert(outcome >= 0 && outcome < 3);

    std::cout << "alias_method_discrete_distribution tests passed successfully.\n";
    return 0;
}
