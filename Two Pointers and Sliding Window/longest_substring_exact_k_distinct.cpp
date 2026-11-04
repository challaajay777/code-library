#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarrays with Exactly K Distinct Characters
// Purpose: Counts total contiguous subarrays/substrings containing exactly K distinct elements in O(N) via atMost(K) - atMost(K - 1).
// Time Complexity: O(N) time
// Space Complexity: O(Sigma) auxiliary space
// Preconditions: K >= 1.

class SubarraysExactKDistinct {
private:
    static long long at_most_k(const std::vector<int>& a, int k) {
        if (k <= 0) return 0;
        std::vector<int> freq(100005, 0);
        int distinct = 0;
        int left = 0;
        long long total = 0;

        for (int right = 0; right < (int)a.size(); ++right) {
            if (freq[a[right]] == 0) distinct++;
            freq[a[right]]++;

            while (distinct > k) {
                freq[a[left]]--;
                if (freq[a[left]] == 0) distinct--;
                left++;
            }
            total += (right - left + 1);
        }
        return total;
    }

public:
    static long long count_exact_k(const std::vector<int>& a, int k) {
        return at_most_k(a, k) - at_most_k(a, k - 1);
    }
};

int main() {
    std::vector<int> a = {1, 2, 1, 2, 3};
    // Subarrays with exactly 2 distinct: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2] -> 7
    assert(SubarraysExactKDistinct::count_exact_k(a, 2) == 7);

    std::vector<int> b = {1, 2, 1, 3, 4};
    assert(SubarraysExactKDistinct::count_exact_k(b, 3) == 3);

    std::cout << "longest_substring_exact_k_distinct tests passed successfully.\n";
    return 0;
}
