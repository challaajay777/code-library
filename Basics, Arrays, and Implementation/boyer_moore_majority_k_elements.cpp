#include <iostream>
#include <vector>
#include <map>
#include <cassert>

// Algorithm: Generalized Boyer-Moore Majority Vote (N/K Frequency)
// Purpose: Finds all elements appearing strictly more than floor(N/K) times in an array using at most K-1 candidate registers.
// Time Complexity: O(N * K) time
// Space Complexity: O(K) auxiliary space
// Preconditions: K >= 2.

class GeneralizedMajorityVote {
public:
    template <typename T>
    static std::vector<T> find_majority_nk(const std::vector<T>& a, int k) {
        assert(k >= 2);
        int n = a.size();
        if (n == 0) return {};

        std::map<T, int> candidates;

        for (const auto& x : a) {
            if (candidates.count(x)) {
                candidates[x]++;
            } else if ((int)candidates.size() < k - 1) {
                candidates[x] = 1;
            } else {
                for (auto it = candidates.begin(); it != candidates.end();) {
                    it->second--;
                    if (it->second == 0) {
                        it = candidates.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

        // Verification pass
        std::map<T, int> actual_counts;
        for (const auto& x : a) {
            if (candidates.count(x)) {
                actual_counts[x]++;
            }
        }

        std::vector<T> result;
        for (const auto& pair : actual_counts) {
            if (pair.second > n / k) {
                result.push_back(pair.first);
            }
        }
        return result;
    }
};

int main() {
    std::vector<int> a = {3, 1, 2, 2, 1, 2, 3, 3}; // n=8, k=4, threshold > 2
    auto res = GeneralizedMajorityVote::find_majority_nk(a, 4);
    // Elements appearing > 2 times: 2 (3 times), 3 (3 times)
    assert(res.size() == 2);
    assert(res[0] == 2 && res[1] == 3);

    std::cout << "boyer_moore_majority_k_elements tests passed successfully.\n";
    return 0;
}
