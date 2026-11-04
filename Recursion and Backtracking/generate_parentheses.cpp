#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Generate Parentheses
// Purpose: Generates all unique well-formed combinations of N pairs of valid matching parentheses in Catalan(N) time.
// Time Complexity: O(4^N / sqrt(N)) Catalan number bound
// Space Complexity: O(2*N) recursion depth
// Preconditions: 1 <= N <= 12.

class GenerateParentheses {
private:
    static void backtrack(int open_count, int close_count, int n, std::string& cur,
                          std::vector<std::string>& res) {
        if (cur.size() == (size_t)(2 * n)) {
            res.push_back(cur);
            return;
        }
        if (open_count < n) {
            cur.push_back('(');
            backtrack(open_count + 1, close_count, n, cur, res);
            cur.pop_back();
        }
        if (close_count < open_count) {
            cur.push_back(')');
            backtrack(open_count, close_count + 1, n, cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::string> generate(int n) {
        std::vector<std::string> res;
        std::string cur = "";
        backtrack(0, 0, n, cur, res);
        return res;
    }
};

int main() {
    auto p3 = GenerateParentheses::generate(3);
    assert(p3.size() == 5); // C_3 = 5

    auto p4 = GenerateParentheses::generate(4);
    assert(p4.size() == 14); // C_4 = 14

    std::cout << "generate_parentheses tests passed successfully.\n";
    return 0;
}
