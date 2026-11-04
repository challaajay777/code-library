#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Reorganize String (No Adjacent Identical Characters)
// Purpose: Rearranges characters of a string so that no two adjacent characters are identical using max-heap in O(N log Sigma).
// Time Complexity: O(N log 26) time
// Space Complexity: O(26) space
// Preconditions: String of lowercase English letters.

class ReorganizeString {
public:
    static std::string reorganize(const std::string& s) {
        std::vector<int> counts(26, 0);
        for (char c : s) counts[c - 'a']++;

        std::priority_queue<std::pair<int, char>> pq;
        for (int i = 0; i < 26; ++i) {
            if (counts[i] > 0) {
                if (counts[i] > ((int)s.size() + 1) / 2) return "";
                pq.push({counts[i], (char)('a' + i)});
            }
        }

        std::string res = "";
        while (pq.size() >= 2) {
            auto [cnt1, ch1] = pq.top(); pq.pop();
            auto [cnt2, ch2] = pq.top(); pq.pop();

            res.push_back(ch1);
            res.push_back(ch2);

            if (--cnt1 > 0) pq.push({cnt1, ch1});
            if (--cnt2 > 0) pq.push({cnt2, ch2});
        }

        if (!pq.empty()) {
            res.push_back(pq.top().second);
        }
        return res;
    }
};

int main() {
    std::string s1 = "aab";
    auto res1 = ReorganizeString::reorganize(s1);
    assert(res1 == "aba");

    std::string s2 = "aaab";
    assert(ReorganizeString::reorganize(s2) == "");

    std::cout << "reorganize_string_greedy tests passed successfully.\n";
    return 0;
}
