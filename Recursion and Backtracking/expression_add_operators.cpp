#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Expression Add Operators
// Purpose: Adds binary operators (+, -, *) between digits of num string so that expression evaluates to target.
// Time Complexity: O(4^N) time
// Space Complexity: O(N) recursion stack
// Preconditions: String num contains digits '0'-'9'.

class ExpressionAddOperators {
private:
    static void dfs(int idx, const std::string& num, long long target, long long diff,
                    long long cur_val, std::string expr, std::vector<std::string>& res) {
        if (idx == (int)num.size()) {
            if (cur_val == target) res.push_back(expr);
            return;
        }

        for (int len = 1; idx + len <= (int)num.size(); ++len) {
            std::string sub = num.substr(idx, len);
            if (sub.size() > 1 && sub[0] == '0') break; // No leading zero numbers
            long long val = std::stoll(sub);

            if (idx == 0) {
                dfs(idx + len, num, target, val, val, sub, res);
            } else {
                dfs(idx + len, num, target, val, cur_val + val, expr + "+" + sub, res);
                dfs(idx + len, num, target, -val, cur_val - val, expr + "-" + sub, res);
                dfs(idx + len, num, target, diff * val, (cur_val - diff) + diff * val, expr + "*" + sub, res);
            }
        }
    }

public:
    static std::vector<std::string> add_operators(const std::string& num, long long target) {
        std::vector<std::string> res;
        dfs(0, num, target, 0, 0, "", res);
        return res;
    }
};

int main() {
    auto res = ExpressionAddOperators::add_operators("123", 6);
    // "1+2+3", "1*2*3" -> 2 expressions
    assert(res.size() == 2);

    auto res2 = ExpressionAddOperators::add_operators("232", 8);
    // "2*3+2", "2+3*2" -> 2 expressions
    assert(res2.size() == 2);

    std::cout << "expression_add_operators tests passed successfully.\n";
    return 0;
}
