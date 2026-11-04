#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Palindrome Partitioning
// Purpose: Finds all partitions of string S such that every substring in the partition is a palindrome.
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(N) recursion depth
// Preconditions: String characters printable ASCII.

class PalindromePartitioning {
private:
    static bool is_palindrome(const std::string& s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }

    static void dfs(int start, const std::string& s, std::vector<std::string>& cur,
                    std::vector<std::vector<std::string>>& res) {
        if (start == (int)s.size()) {
            res.push_back(cur);
            return;
        }
        for (int end = start; end < (int)s.size(); ++end) {
            if (is_palindrome(s, start, end)) {
                cur.push_back(s.substr(start, end - start + 1));
                dfs(end + 1, s, cur, res);
                cur.pop_back();
            }
        }
    }

public:
    static std::vector<std::vector<std::string>> partition(const std::string& s) {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> cur;
        dfs(0, s, cur, res);
        return res;
    }
};

int main() {
    auto res = PalindromePartitioning::partition("aab");
    // [["a", "a", "b"], ["aa", "b"]]
    assert(res.size() == 2);

    std::cout << "palindrome_partitioning tests passed successfully.\n";
    return 0;
}
