#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Letter Combinations of a Phone Number
// Purpose: Generates all possible letter combinations that a given phone digit string (2-9) can represent.
// Time Complexity: O(4^N * N) time
// Space Complexity: O(N) recursion depth
// Preconditions: String digits contains characters from '2' to '9'.

class PhoneKeypadLetters {
private:
    static const std::string PAD[10];

    static void backtrack(int idx, const std::string& digits, std::string& cur,
                          std::vector<std::string>& res) {
        if (idx == (int)digits.size()) {
            res.push_back(cur);
            return;
        }
        const std::string& letters = PAD[digits[idx] - '0'];
        for (char c : letters) {
            cur.push_back(c);
            backtrack(idx + 1, digits, cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::string> letter_combinations(const std::string& digits) {
        if (digits.empty()) return {};
        std::vector<std::string> res;
        std::string cur = "";
        backtrack(0, digits, cur, res);
        return res;
    }
};

const std::string PhoneKeypadLetters::PAD[10] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

int main() {
    auto res = PhoneKeypadLetters::letter_combinations("23");
    assert(res.size() == 9);
    assert(res[0] == "ad");
    assert(res.back() == "cf");

    std::cout << "letter_combinations_phone_number tests passed successfully.\n";
    return 0;
}
