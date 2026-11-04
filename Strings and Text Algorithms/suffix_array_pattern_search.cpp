#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Suffix Array Pattern Search
// Purpose: Finds all occurrences of pattern P in string S via binary search on Suffix Array in O(|P| log |S|).
// Time Complexity: O(|P| log |S|) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Suffix array matches string s.

class SuffixArraySearch {
public:
    static bool contains_pattern(const std::string& s, const std::vector<int>& sa, const std::string& p) {
        int low = 0, high = (int)sa.size() - 1;
        int m = p.size();

        while (low <= high) {
            int mid = low + (high - low) / 2;
            std::string sub = s.substr(sa[mid], m);

            if (sub == p) {
                return true;
            } else if (sub < p) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};

int main() {
    std::string s = "banana";
    std::vector<int> sa = {5, 3, 1, 0, 4, 2};
    assert(SuffixArraySearch::contains_pattern(s, sa, "nan") == true);
    assert(SuffixArraySearch::contains_pattern(s, sa, "apple") == false);

    std::cout << "suffix_array_pattern_search tests passed successfully.\n";
    return 0;
}
