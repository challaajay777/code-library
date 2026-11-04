#!/usr/bin/env python3
"""
Batch 5 Generator: Recursion and Backtracking (25 implementations)
Target Directory: Recursion and Backtracking
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Recursion and Backtracking"

FILES = [
    {
        "filename": "n_queens_standard.cpp",
        "algorithm": "N-Queens Solver (Standard Backtracking)",
        "purpose": "Finds all distinct board configurations of placing N non-attacking queens on an N x N chessboard.",
        "time_complexity": "O(N!) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "1 <= N <= 14.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Algorithm: N-Queens Solver (Standard Backtracking)
// Purpose: Finds all distinct board configurations of placing N non-attacking queens on an N x N chessboard.
// Time Complexity: O(N!) time
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= N <= 14.

class NQueensStandard {
private:
    static void solve(int row, int n, std::vector<bool>& cols, std::vector<bool>& diag1,
                      std::vector<bool>& diag2, std::vector<std::string>& board,
                      std::vector<std::vector<std::string>>& results) {
        if (row == n) {
            results.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            int d1 = row - col + n;
            int d2 = row + col;
            if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                cols[col] = diag1[d1] = diag2[d2] = true;
                board[row][col] = 'Q';

                solve(row + 1, n, cols, diag1, diag2, board, results);

                board[row][col] = '.';
                cols[col] = diag1[d1] = diag2[d2] = false;
            }
        }
    }

public:
    static std::vector<std::vector<std::string>> solve_n_queens(int n) {
        std::vector<std::vector<std::string>> results;
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);

        solve(0, n, cols, diag1, diag2, board, results);
        return results;
    }
};

int main() {
    auto res4 = NQueensStandard::solve_n_queens(4);
    assert(res4.size() == 2);

    auto res8 = NQueensStandard::solve_n_queens(8);
    assert(res8.size() == 92);

    std::cout << "n_queens_standard tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "n_queens_bitmask.cpp",
        "algorithm": "N-Queens Solver (Bitmask Optimization)",
        "purpose": "High-performance N-Queens total solution counter using bitwise operations for row, column, and diagonal bitmasks.",
        "time_complexity": "O(N!) time with ultra-fast bitwise constant factors",
        "space_complexity": "O(N) recursion stack",
        "preconditions": "1 <= N <= 30.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: N-Queens Solver (Bitmask Optimization)
// Purpose: High-performance N-Queens total solution counter using bitwise operations for row, column, and diagonal bitmasks.
// Time Complexity: O(N!) time with ultra-fast bitwise constant factors
// Space Complexity: O(N) recursion stack
// Preconditions: 1 <= N <= 30.

class NQueensBitmask {
private:
    static void count_solutions(uint32_t all_queens, uint32_t cols, uint32_t diag1, uint32_t diag2, int& count) {
        if (cols == all_queens) {
            count++;
            return;
        }
        uint32_t available = all_queens & (~(cols | diag1 | diag2));
        while (available > 0) {
            uint32_t p = available & -available;
            available -= p;
            count_solutions(all_queens, cols | p, (diag1 | p) << 1, (diag2 | p) >> 1, count);
        }
    }

public:
    static int total_n_queens(int n) {
        assert(n >= 1 && n <= 30);
        uint32_t all_queens = (1U << n) - 1U;
        int count = 0;
        count_solutions(all_queens, 0, 0, 0, count);
        return count;
    }
};

int main() {
    assert(NQueensBitmask::total_n_queens(4) == 2);
    assert(NQueensBitmask::total_n_queens(8) == 92);
    assert(NQueensBitmask::total_n_queens(10) == 724);

    std::cout << "n_queens_bitmask tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "sudoku_solver.cpp",
        "algorithm": "Sudoku Solver (Exact Cover / Backtracking)",
        "purpose": "Solves any standard 9x9 Sudoku puzzle in-place using recursive constraint backtracking with fast bitmasks.",
        "time_complexity": "O(9^(empty cells)) worst case, sub-millisecond in practice",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Grid is 9x9 containing valid initial numbers (0 for empty).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Sudoku Solver (Exact Cover / Backtracking)
// Purpose: Solves any standard 9x9 Sudoku puzzle in-place using recursive constraint backtracking with fast bitmasks.
// Time Complexity: O(9^(empty cells)) worst case, sub-millisecond in practice
// Space Complexity: O(1) auxiliary space
// Preconditions: Grid is 9x9 containing valid initial numbers (0 for empty).

class SudokuSolver {
private:
    static bool is_valid(const std::vector<std::vector<int>>& board, int r, int c, int val) {
        for (int i = 0; i < 9; ++i) {
            if (board[r][i] == val) return false;
            if (board[i][c] == val) return false;
            if (board[3 * (r / 3) + i / 3][3 * (c / 3) + i % 3] == val) return false;
        }
        return true;
    }

    static bool solve(std::vector<std::vector<int>>& board) {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == 0) {
                    for (int val = 1; val <= 9; ++val) {
                        if (is_valid(board, r, c, val)) {
                            board[r][c] = val;
                            if (solve(board)) return true;
                            board[r][c] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

public:
    static bool solve_sudoku(std::vector<std::vector<int>>& board) {
        return solve(board);
    }
};

int main() {
    std::vector<std::vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    bool solved = SudokuSolver::solve_sudoku(board);
    assert(solved);
    assert(board[0][2] == 4);
    assert(board[8][8] == 9);

    std::cout << "sudoku_solver tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subsets_lexicographic.cpp",
        "algorithm": "Lexicographical Subsets Generation",
        "purpose": "Generates all 2^N subsets of an array in lexicographical order using recursive choice.",
        "time_complexity": "O(N * 2^N) time",
        "space_complexity": "O(N) recursion depth",
        "preconditions": "Array elements distinct and pre-sorted.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Lexicographical Subsets Generation
// Purpose: Generates all 2^N subsets of an array in lexicographical order using recursive choice.
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(N) recursion depth
// Preconditions: Array elements distinct and pre-sorted.

class LexicographicalSubsets {
private:
    static void dfs(int idx, const std::vector<int>& nums, std::vector<int>& cur,
                    std::vector<std::vector<int>>& result) {
        result.push_back(cur);
        for (int i = idx; i < (int)nums.size(); ++i) {
            cur.push_back(nums[i]);
            dfs(i + 1, nums, cur, result);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> subsets(std::vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        dfs(0, nums, cur, result);
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3};
    auto subs = LexicographicalSubsets::subsets(nums);
    assert(subs.size() == 8);

    std::cout << "subsets_lexicographic tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subsets_with_duplicates.cpp",
        "algorithm": "Subsets II (Subsets with Duplicates)",
        "purpose": "Generates all unique subsets from an array containing duplicate elements in O(N * 2^N).",
        "time_complexity": "O(N * 2^N) time",
        "space_complexity": "O(N) recursion depth",
        "preconditions": "General array of elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Subsets II (Subsets with Duplicates)
// Purpose: Generates all unique subsets from an array containing duplicate elements in O(N * 2^N).
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(N) recursion depth
// Preconditions: General array of elements.

class SubsetsWithDuplicates {
private:
    static void dfs(int idx, const std::vector<int>& nums, std::vector<int>& cur,
                    std::vector<std::vector<int>>& result) {
        result.push_back(cur);
        for (int i = idx; i < (int)nums.size(); ++i) {
            if (i > idx && nums[i] == nums[i - 1]) continue;
            cur.push_back(nums[i]);
            dfs(i + 1, nums, cur, result);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> subsets_with_dup(std::vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        dfs(0, nums, cur, result);
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 2};
    auto subs = SubsetsWithDuplicates::subsets_with_dup(nums);
    // Unique subsets: [], [1], [1, 2], [1, 2, 2], [2], [2, 2] -> total 6
    assert(subs.size() == 6);

    std::cout << "subsets_with_duplicates tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "permutations_all.cpp",
        "algorithm": "Permutations Generator",
        "purpose": "Generates all N! permutations of an array of distinct elements via recursive backtracking swaps.",
        "time_complexity": "O(N * N!) time",
        "space_complexity": "O(N) recursion depth",
        "preconditions": "Elements are distinct.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Permutations Generator
// Purpose: Generates all N! permutations of an array of distinct elements via recursive backtracking swaps.
// Time Complexity: O(N * N!) time
// Space Complexity: O(N) recursion depth
// Preconditions: Elements are distinct.

class PermutationsGenerator {
private:
    static void backtrack(int start, std::vector<int>& nums, std::vector<std::vector<int>>& res) {
        if (start == (int)nums.size()) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < (int)nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            backtrack(start + 1, nums, res);
            std::swap(nums[start], nums[i]);
        }
    }

public:
    static std::vector<std::vector<int>> permute(std::vector<int> nums) {
        std::vector<std::vector<int>> res;
        backtrack(0, nums, res);
        return res;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3};
    auto p = PermutationsGenerator::permute(nums);
    assert(p.size() == 6);

    std::cout << "permutations_all tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "permutations_with_duplicates.cpp",
        "algorithm": "Permutations II (Unique Permutations with Duplicates)",
        "purpose": "Generates all unique permutations of an array containing duplicate elements in O(N * N!).",
        "time_complexity": "O(N * N!) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "General array of elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Permutations II (Unique Permutations with Duplicates)
// Purpose: Generates all unique permutations of an array containing duplicate elements in O(N * N!).
// Time Complexity: O(N * N!) time
// Space Complexity: O(N) auxiliary space
// Preconditions: General array of elements.

class PermutationsWithDuplicates {
private:
    static void backtrack(std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& cur,
                          std::vector<std::vector<int>>& res) {
        if (cur.size() == nums.size()) {
            res.push_back(cur);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

            used[i] = true;
            cur.push_back(nums[i]);
            backtrack(nums, used, cur, res);
            cur.pop_back();
            used[i] = false;
        }
    }

public:
    static std::vector<std::vector<int>> permute_unique(std::vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        std::vector<bool> used(nums.size(), false);
        backtrack(nums, used, cur, res);
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 1, 2};
    auto p = PermutationsWithDuplicates::permute_unique(a);
    // [1, 1, 2], [1, 2, 1], [2, 1, 1] -> 3 permutations
    assert(p.size() == 3);

    std::cout << "permutations_with_duplicates tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "combination_sum_unlimited.cpp",
        "algorithm": "Combination Sum (Unlimited Use)",
        "purpose": "Finds all distinct combinations of candidates where each number may be used an unlimited number of times.",
        "time_complexity": "O(2^Target) worst case",
        "space_complexity": "O(Target) recursion stack",
        "preconditions": "Candidate numbers are positive and distinct; target > 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Combination Sum (Unlimited Use)
// Purpose: Finds all distinct combinations of candidates where each number may be used an unlimited number of times.
// Time Complexity: O(2^Target) worst case
// Space Complexity: O(Target) recursion stack
// Preconditions: Candidate numbers are positive and distinct; target > 0.

class CombinationSumUnlimited {
private:
    static void backtrack(int start, const std::vector<int>& candidates, int target,
                          std::vector<int>& cur, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (candidates[i] > target) break;
            cur.push_back(candidates[i]);
            backtrack(i, candidates, target - candidates[i], cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> combination_sum(std::vector<int> candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        backtrack(0, candidates, target, cur, res);
        return res;
    }
};

int main() {
    std::vector<int> c = {2, 3, 6, 7};
    auto res = CombinationSumUnlimited::combination_sum(c, 7);
    // [2, 2, 3] and [7] -> 2 combinations
    assert(res.size() == 2);

    std::cout << "combination_sum_unlimited tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "combination_sum_unique.cpp",
        "algorithm": "Combination Sum II (Single Use with Duplicates)",
        "purpose": "Finds all unique combinations in candidates that sum to target where each candidate may only be used once.",
        "time_complexity": "O(2^N) time",
        "space_complexity": "O(N) recursion stack",
        "preconditions": "All elements positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Combination Sum II (Single Use with Duplicates)
// Purpose: Finds all unique combinations in candidates that sum to target where each candidate may only be used once.
// Time Complexity: O(2^N) time
// Space Complexity: O(N) recursion stack
// Preconditions: All elements positive.

class CombinationSumUnique {
private:
    static void backtrack(int start, const std::vector<int>& candidates, int target,
                          std::vector<int>& cur, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (candidates[i] > target) break;
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            cur.push_back(candidates[i]);
            backtrack(i + 1, candidates, target - candidates[i], cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> combination_sum2(std::vector<int> candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        backtrack(0, candidates, target, cur, res);
        return res;
    }
};

int main() {
    std::vector<int> c = {10, 1, 2, 7, 6, 1, 5};
    auto res = CombinationSumUnique::combination_sum2(c, 8);
    // [1, 1, 6], [1, 2, 5], [1, 7], [2, 6] -> 4 combinations
    assert(res.size() == 4);

    std::cout << "combination_sum_unique tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "combination_sum_fixed_k.cpp",
        "algorithm": "Combination Sum III (K Numbers from 1 to 9)",
        "purpose": "Finds all valid combinations of K distinct numbers selected from 1..9 that add up to target N.",
        "time_complexity": "O(C(9, K)) time",
        "space_complexity": "O(K) recursion depth",
        "preconditions": "1 <= K <= 9, 1 <= N <= 60.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Combination Sum III (K Numbers from 1 to 9)
// Purpose: Finds all valid combinations of K distinct numbers selected from 1..9 that add up to target N.
// Time Complexity: O(C(9, K)) time
// Space Complexity: O(K) recursion depth
// Preconditions: 1 <= K <= 9, 1 <= N <= 60.

class CombinationSumFixedK {
private:
    static void backtrack(int start, int k, int n, std::vector<int>& cur,
                          std::vector<std::vector<int>>& res) {
        if (cur.size() == (size_t)k && n == 0) {
            res.push_back(cur);
            return;
        }
        if (cur.size() >= (size_t)k || n < 0) return;

        for (int i = start; i <= 9; ++i) {
            if (i > n) break;
            cur.push_back(i);
            backtrack(i + 1, k, n - i, cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> combination_sum3(int k, int n) {
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        backtrack(1, k, n, cur, res);
        return res;
    }
};

int main() {
    auto res1 = CombinationSumFixedK::combination_sum3(3, 7);
    assert(res1.size() == 1 && res1[0] == std::vector<int>({1, 2, 4}));

    auto res2 = CombinationSumFixedK::combination_sum3(3, 9);
    assert(res2.size() == 3); // [1,2,6], [1,3,5], [2,3,4]

    std::cout << "combination_sum_fixed_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "word_search_grid.cpp",
        "algorithm": "2D Grid Word Search",
        "purpose": "Determines if a word exists in an R x C grid using adjacent horizontal and vertical moves with backtrack marking.",
        "time_complexity": "O(R * C * 3^L) time where L is word length",
        "space_complexity": "O(L) recursion depth",
        "preconditions": "Grid characters match word casing.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Algorithm: 2D Grid Word Search
// Purpose: Determines if a word exists in an R x C grid using adjacent horizontal and vertical moves with backtrack marking.
// Time Complexity: O(R * C * 3^L) time where L is word length
// Space Complexity: O(L) recursion depth
// Preconditions: Grid characters match word casing.

class WordSearchGrid {
private:
    static bool dfs(std::vector<std::vector<char>>& board, int r, int c, const std::string& word, int idx) {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[0].size() || board[r][c] != word[idx]) {
            return false;
        }

        char temp = board[r][c];
        board[r][c] = '#'; // Mark visited

        bool found = dfs(board, r + 1, c, word, idx + 1) ||
                     dfs(board, r - 1, c, word, idx + 1) ||
                     dfs(board, r, c + 1, word, idx + 1) ||
                     dfs(board, r, c - 1, word, idx + 1);

        board[r][c] = temp; // Unmark
        return found;
    }

public:
    static bool exist(std::vector<std::vector<char>>& board, const std::string& word) {
        if (board.empty() || board[0].empty()) return false;
        for (size_t r = 0; r < board.size(); ++r) {
            for (size_t c = 0; c < board[0].size(); ++c) {
                if (board[r][c] == word[0] && dfs(board, r, c, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<char>> b = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    assert(WordSearchGrid::exist(b, "ABCCED") == true);
    assert(WordSearchGrid::exist(b, "SEE") == true);
    assert(WordSearchGrid::exist(b, "ABCB") == false);

    std::cout << "word_search_grid tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "word_break_backtracking.cpp",
        "algorithm": "Word Break II (Sentence Generation)",
        "purpose": "Constructs all valid sentences formed by inserting spaces in string S such that each word is in the dictionary.",
        "time_complexity": "O(2^N) worst case",
        "space_complexity": "O(N^2) memoization table",
        "preconditions": "Non-empty string and dictionary.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

// Algorithm: Word Break II (Sentence Generation)
// Purpose: Constructs all valid sentences formed by inserting spaces in string S such that each word is in the dictionary.
// Time Complexity: O(2^N) worst case
// Space Complexity: O(N^2) memoization table
// Preconditions: Non-empty string and dictionary.

class WordBreakSentences {
private:
    static std::vector<std::string> dfs(const std::string& s, const std::unordered_set<std::string>& dict,
                                        std::unordered_map<std::string, std::vector<std::string>>& memo) {
        if (memo.count(s)) return memo[s];
        if (s.empty()) return {""};

        std::vector<std::string> sentences;
        for (size_t len = 1; len <= s.size(); ++len) {
            std::string prefix = s.substr(0, len);
            if (dict.count(prefix)) {
                auto suffixes = dfs(s.substr(len), dict, memo);
                for (const auto& suf : suffixes) {
                    sentences.push_back(prefix + (suf.empty() ? "" : " ") + suf);
                }
            }
        }
        return memo[s] = sentences;
    }

public:
    static std::vector<std::string> word_break(const std::string& s, const std::vector<std::string>& word_dict) {
        std::unordered_set<std::string> dict(word_dict.begin(), word_dict.end());
        std::unordered_map<std::string, std::vector<std::string>> memo;
        return dfs(s, dict, memo);
    }
};

int main() {
    std::string s = "catsanddog";
    std::vector<std::string> dict = {"cat", "cats", "and", "sand", "dog"};
    auto sentences = WordBreakSentences::word_break(s, dict);
    // "cats and dog", "cat sand dog"
    assert(sentences.size() == 2);

    std::cout << "word_break_backtracking tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "palindrome_partitioning.cpp",
        "algorithm": "Palindrome Partitioning",
        "purpose": "Finds all partitions of string S such that every substring in the partition is a palindrome.",
        "time_complexity": "O(N * 2^N) time",
        "space_complexity": "O(N) recursion depth",
        "preconditions": "String characters printable ASCII.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "partition_k_equal_sum_subsets.cpp",
        "algorithm": "Partition to K Equal Sum Subsets",
        "purpose": "Determines whether an array of integers can be partitioned into K non-empty subsets with equal sum.",
        "time_complexity": "O(K * 2^N) time with pruning",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "1 <= K <= N.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Partition to K Equal Sum Subsets
// Purpose: Determines whether an array of integers can be partitioned into K non-empty subsets with equal sum.
// Time Complexity: O(K * 2^N) time with pruning
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= K <= N.

class PartitionKEqualSubsets {
private:
    static bool dfs(int idx, int count_k, int cur_sum, int target,
                    const std::vector<int>& nums, std::vector<bool>& used) {
        if (count_k == 0) return true;
        if (cur_sum == target) {
            return dfs(0, count_k - 1, 0, target, nums, used);
        }

        for (int i = idx; i < (int)nums.size(); ++i) {
            if (used[i] || cur_sum + nums[i] > target) continue;
            used[i] = true;
            if (dfs(i + 1, count_k, cur_sum + nums[i], target, nums, used)) {
                return true;
            }
            used[i] = false;
            // Prune duplicate failures
            while (i + 1 < (int)nums.size() && nums[i + 1] == nums[i]) i++;
            if (cur_sum == 0) break;
        }
        return false;
    }

public:
    static bool can_partition_k_subsets(std::vector<int> nums, int k) {
        int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;
        int target = total / k;

        std::sort(nums.rbegin(), nums.rend());
        if (nums[0] > target) return false;

        std::vector<bool> used(nums.size(), false);
        return dfs(0, k, 0, target, nums, used);
    }
};

int main() {
    std::vector<int> a = {4, 3, 2, 3, 5, 2, 1};
    assert(PartitionKEqualSubsets::can_partition_k_subsets(a, 4) == true);

    std::vector<int> b = {1, 2, 3, 4};
    assert(PartitionKEqualSubsets::can_partition_k_subsets(b, 3) == false);

    std::cout << "partition_k_equal_sum_subsets tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "knights_tour_warnsdorff.cpp",
        "algorithm": "Knight's Tour (Warnsdorff's Heuristic)",
        "purpose": "Finds a closed or open Knight's Tour visiting every square of an N x N chessboard exactly once.",
        "time_complexity": "O(N^2) linear time with Warnsdorff's tie-breaking",
        "space_complexity": "O(N^2) board grid",
        "preconditions": "Board size N >= 5.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Knight's Tour (Warnsdorff's Heuristic)
// Purpose: Finds a closed or open Knight's Tour visiting every square of an N x N chessboard exactly once.
// Time Complexity: O(N^2) linear time with Warnsdorff's tie-breaking
// Space Complexity: O(N^2) board grid
// Preconditions: Board size N >= 5.

class KnightsTourWarnsdorff {
private:
    static const int DX[8];
    static const int DY[8];

    static bool is_valid(int x, int y, int n, const std::vector<std::vector<int>>& board) {
        return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
    }

    static int get_degree(int x, int y, int n, const std::vector<std::vector<int>>& board) {
        int count = 0;
        for (int i = 0; i < 8; ++i) {
            if (is_valid(x + DX[i], y + DY[i], n, board)) count++;
        }
        return count;
    }

public:
    static std::vector<std::vector<int>> solve(int n, int start_x = 0, int start_y = 0) {
        std::vector<std::vector<int>> board(n, std::vector<int>(n, -1));
        int cur_x = start_x, cur_y = start_y;
        board[cur_x][cur_y] = 1;

        for (int move = 2; move <= n * n; ++move) {
            int best_idx = -1;
            int min_deg = 9;

            for (int i = 0; i < 8; ++i) {
                int nx = cur_x + DX[i];
                int ny = cur_y + DY[i];
                if (is_valid(nx, ny, n, board)) {
                    int deg = get_degree(nx, ny, n, board);
                    if (deg < min_deg) {
                        min_deg = deg;
                        best_idx = i;
                    }
                }
            }

            if (best_idx == -1) return {}; // Failed (dead end)
            cur_x += DX[best_idx];
            cur_y += DY[best_idx];
            board[cur_x][cur_y] = move;
        }
        return board;
    }
};

const int KnightsTourWarnsdorff::DX[8] = {1, 1, 2, 2, -1, -1, -2, -2};
const int KnightsTourWarnsdorff::DY[8] = {2, -2, 1, -1, 2, -2, 1, -1};

int main() {
    auto board = KnightsTourWarnsdorff::solve(6);
    assert(!board.empty());
    assert(board[0][0] == 1);

    std::cout << "knights_tour_warnsdorff tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "hamiltonian_cycle_backtracking.cpp",
        "algorithm": "Hamiltonian Cycle (Backtracking)",
        "purpose": "Finds a simple cycle in an undirected graph that visits every vertex exactly once and returns to starting node.",
        "time_complexity": "O(N!) worst case",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Graph represented as adjacency matrix; V <= 20.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Hamiltonian Cycle (Backtracking)
// Purpose: Finds a simple cycle in an undirected graph that visits every vertex exactly once and returns to starting node.
// Time Complexity: O(N!) worst case
// Space Complexity: O(N) auxiliary space
// Preconditions: Graph represented as adjacency matrix; V <= 20.

class HamiltonianCycle {
private:
    static bool is_safe(int v, const std::vector<std::vector<int>>& graph,
                        const std::vector<int>& path, int pos) {
        if (!graph[path[pos - 1]][v]) return false;
        for (int i = 0; i < pos; ++i) {
            if (path[i] == v) return false;
        }
        return true;
    }

    static bool cycle_util(const std::vector<std::vector<int>>& graph,
                           std::vector<int>& path, int pos, int v) {
        if (pos == v) {
            return graph[path[pos - 1]][path[0]] == 1;
        }
        for (int u = 1; u < v; ++u) {
            if (is_safe(u, graph, path, pos)) {
                path[pos] = u;
                if (cycle_util(graph, path, pos + 1, v)) return true;
                path[pos] = -1;
            }
        }
        return false;
    }

public:
    static std::vector<int> find_cycle(const std::vector<std::vector<int>>& graph) {
        int v = graph.size();
        std::vector<int> path(v, -1);
        path[0] = 0;

        if (!cycle_util(graph, path, 1, v)) {
            return {};
        }
        path.push_back(0); // return to start
        return path;
    }
};

int main() {
    std::vector<std::vector<int>> g = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };
    auto cycle = HamiltonianCycle::find_cycle(g);
    assert(!cycle.empty());
    assert(cycle.front() == 0 && cycle.back() == 0);

    std::cout << "hamiltonian_cycle_backtracking tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "graph_m_coloring.cpp",
        "algorithm": "Graph M-Coloring (Backtracking)",
        "purpose": "Assigns one of M colors to each vertex such that no two adjacent vertices share the same color.",
        "time_complexity": "O(M^V) worst case",
        "space_complexity": "O(V) recursion depth",
        "preconditions": "Graph adjacency matrix; M >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Graph M-Coloring (Backtracking)
// Purpose: Assigns one of M colors to each vertex such that no two adjacent vertices share the same color.
// Time Complexity: O(M^V) worst case
// Space Complexity: O(V) recursion depth
// Preconditions: Graph adjacency matrix; M >= 1.

class GraphMColoring {
private:
    static bool is_safe(int v, const std::vector<std::vector<int>>& graph,
                        const std::vector<int>& color, int c) {
        for (int i = 0; i < (int)graph.size(); ++i) {
            if (graph[v][i] && color[i] == c) return false;
        }
        return true;
    }

    static bool color_util(int v, int m, const std::vector<std::vector<int>>& graph,
                           std::vector<int>& color) {
        if (v == (int)graph.size()) return true;

        for (int c = 1; c <= m; ++c) {
            if (is_safe(v, graph, color, c)) {
                color[v] = c;
                if (color_util(v + 1, m, graph, color)) return true;
                color[v] = 0;
            }
        }
        return false;
    }

public:
    static std::vector<int> color_graph(const std::vector<std::vector<int>>& graph, int m) {
        int n = graph.size();
        std::vector<int> color(n, 0);
        if (color_util(0, m, graph, color)) {
            return color;
        }
        return {};
    }
};

int main() {
    std::vector<std::vector<int>> g = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    auto colors = GraphMColoring::color_graph(g, 3);
    assert(!colors.empty());

    std::cout << "graph_m_coloring tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "rat_in_a_maze.cpp",
        "algorithm": "Rat in a Maze (All Directional Paths)",
        "purpose": "Finds all distinct paths from (0, 0) to (N-1, N-1) in a grid with obstacles, returning move sequences 'DLRU'.",
        "time_complexity": "O(4^(N^2)) worst case",
        "space_complexity": "O(N^2) recursion depth",
        "preconditions": "Grid consists of 0 (blocked) and 1 (free cell).",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// Algorithm: Rat in a Maze (All Directional Paths)
// Purpose: Finds all distinct paths from (0, 0) to (N-1, N-1) in a grid with obstacles, returning move sequences 'DLRU'.
// Time Complexity: O(4^(N^2)) worst case
// Space Complexity: O(N^2) recursion depth
// Preconditions: Grid consists of 0 (blocked) and 1 (free cell).

class RatInMaze {
private:
    static void solve(int r, int c, int n, std::vector<std::vector<int>>& maze,
                      std::string& current_path, std::vector<std::string>& all_paths) {
        if (r == n - 1 && c == n - 1) {
            all_paths.push_back(current_path);
            return;
        }

        maze[r][c] = 0; // Mark visited

        // Down
        if (r + 1 < n && maze[r + 1][c] == 1) {
            current_path.push_back('D');
            solve(r + 1, c, n, maze, current_path, all_paths);
            current_path.pop_back();
        }
        // Left
        if (c - 1 >= 0 && maze[r][c - 1] == 1) {
            current_path.push_back('L');
            solve(r, c - 1, n, maze, current_path, all_paths);
            current_path.pop_back();
        }
        // Right
        if (c + 1 < n && maze[r][c + 1] == 1) {
            current_path.push_back('R');
            solve(r, c + 1, n, maze, current_path, all_paths);
            current_path.pop_back();
        }
        // Up
        if (r - 1 >= 0 && maze[r - 1][c] == 1) {
            current_path.push_back('U');
            solve(r - 1, c, n, maze, current_path, all_paths);
            current_path.pop_back();
        }

        maze[r][c] = 1; // Unmark
    }

public:
    static std::vector<std::string> find_paths(std::vector<std::vector<int>> maze) {
        int n = maze.size();
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) return {};

        std::vector<std::string> all_paths;
        std::string current_path = "";
        solve(0, 0, n, maze, current_path, all_paths);
        std::sort(all_paths.begin(), all_paths.end());
        return all_paths;
    }
};

int main() {
    std::vector<std::vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    auto paths = RatInMaze::find_paths(maze);
    assert(paths.size() == 2);
    assert(paths[0] == "DDRDRR");
    assert(paths[1] == "DRDDRR");

    std::cout << "rat_in_a_maze tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "tug_of_war_partition.cpp",
        "algorithm": "Tug of War (Equal-Size Partition with Minimum Difference)",
        "purpose": "Partitions an array into two subsets of size floor(N/2) and ceil(N/2) minimizing the absolute sum difference.",
        "time_complexity": "O(2^N) with branch-and-bound pruning",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Array length >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <cassert>

// Algorithm: Tug of War (Equal-Size Partition with Minimum Difference)
// Purpose: Partitions an array into two subsets of size floor(N/2) and ceil(N/2) minimizing the absolute sum difference.
// Time Complexity: O(2^N) with branch-and-bound pruning
// Space Complexity: O(N) auxiliary space
// Preconditions: Array length >= 2.

class TugOfWar {
private:
    static void dfs(int idx, int chosen_count, long long current_sum,
                    const std::vector<long long>& a, int required,
                    long long total_sum, long long& min_diff, std::vector<bool>& cur_sol,
                    std::vector<bool>& best_sol) {
        if (chosen_count == required) {
            long long other_sum = total_sum - current_sum;
            long long diff = std::abs(current_sum - other_sum);
            if (diff < min_diff) {
                min_diff = diff;
                best_sol = cur_sol;
            }
            return;
        }
        if (idx == (int)a.size()) return;

        // Choice 1: include a[idx]
        cur_sol[idx] = true;
        dfs(idx + 1, chosen_count + 1, current_sum + a[idx], a, required, total_sum, min_diff, cur_sol, best_sol);
        cur_sol[idx] = false;

        // Choice 2: exclude a[idx] (if remaining elements are enough)
        if ((int)a.size() - (idx + 1) >= required - chosen_count) {
            dfs(idx + 1, chosen_count, current_sum, a, required, total_sum, min_diff, cur_sol, best_sol);
        }
    }

public:
    static long long find_min_difference(const std::vector<long long>& a) {
        int n = a.size();
        long long total_sum = std::accumulate(a.begin(), a.end(), 0LL);
        long long min_diff = 2e18;

        std::vector<bool> cur_sol(n, false), best_sol(n, false);
        dfs(0, 0, 0, a, n / 2, total_sum, min_diff, cur_sol, best_sol);
        return min_diff;
    }
};

int main() {
    std::vector<long long> a = {3, 4, 5, -3, 100, 1, 89, 54, 23, 20};
    long long diff = TugOfWar::find_min_difference(a);
    assert(diff == 0); // Sets sum to 98 and 98

    std::cout << "tug_of_war_partition tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "letter_combinations_phone_number.cpp",
        "algorithm": "Letter Combinations of a Phone Number",
        "purpose": "Generates all possible letter combinations that a given phone digit string (2-9) can represent.",
        "time_complexity": "O(4^N * N) time",
        "space_complexity": "O(N) recursion depth",
        "preconditions": "String digits contains characters from '2' to '9'.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "generate_parentheses.cpp",
        "algorithm": "Generate Parentheses",
        "purpose": "Generates all unique well-formed combinations of N pairs of valid matching parentheses in Catalan(N) time.",
        "time_complexity": "O(4^N / sqrt(N)) Catalan number bound",
        "space_complexity": "O(2*N) recursion depth",
        "preconditions": "1 <= N <= 12.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "expression_add_operators.cpp",
        "algorithm": "Expression Add Operators",
        "purpose": "Adds binary operators (+, -, *) between digits of num string so that expression evaluates to target.",
        "time_complexity": "O(4^N) time",
        "space_complexity": "O(N) recursion stack",
        "preconditions": "String num contains digits '0'-'9'.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "target_sum_ways.cpp",
        "algorithm": "Target Sum (+ and - Assignments)",
        "purpose": "Calculates number of ways to assign + and - to array elements so that they sum to target.",
        "time_complexity": "O(2^N) time recursion, O(N * Sum) with memoization",
        "space_complexity": "O(N) recursion depth",
        "preconditions": "Array elements non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Target Sum (+ and - Assignments)
// Purpose: Calculates number of ways to assign + and - to array elements so that they sum to target.
// Time Complexity: O(2^N) time recursion, O(N * Sum) with memoization
// Space Complexity: O(N) recursion depth
// Preconditions: Array elements non-negative.

class TargetSumWays {
private:
    static int dfs(int idx, long long current_sum, long long target, const std::vector<int>& nums) {
        if (idx == (int)nums.size()) {
            return current_sum == target ? 1 : 0;
        }
        return dfs(idx + 1, current_sum + nums[idx], target, nums) +
               dfs(idx + 1, current_sum - nums[idx], target, nums);
    }

public:
    static int find_target_sum_ways(const std::vector<int>& nums, long long target) {
        return dfs(0, 0, target, nums);
    }
};

int main() {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    assert(TargetSumWays::find_target_sum_ways(nums, 3) == 5);

    std::vector<int> nums2 = {1};
    assert(TargetSumWays::find_target_sum_ways(nums2, 1) == 1);

    std::cout << "target_sum_ways tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "restore_ip_addresses.cpp",
        "algorithm": "Restore IP Addresses",
        "purpose": "Restores all possible valid IPv4 address strings by placing dots into a raw digit string.",
        "time_complexity": "O(3^4) = O(1) bounded time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "String of digits.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Restore IP Addresses
// Purpose: Restores all possible valid IPv4 address strings by placing dots into a raw digit string.
// Time Complexity: O(3^4) = O(1) bounded time
// Space Complexity: O(1) auxiliary space
// Preconditions: String of digits.

class RestoreIPAddresses {
private:
    static bool is_valid_part(const std::string& s) {
        if (s.empty() || s.size() > 3) return false;
        if (s.size() > 1 && s[0] == '0') return false;
        int val = std::stoi(s);
        return val >= 0 && val <= 255;
    }

    static void dfs(int idx, int parts, const std::string& s, std::string cur,
                    std::vector<std::string>& res) {
        if (parts == 4) {
            if (idx == (int)s.size()) res.push_back(cur);
            return;
        }

        for (int len = 1; len <= 3 && idx + len <= (int)s.size(); ++len) {
            std::string sub = s.substr(idx, len);
            if (is_valid_part(sub)) {
                dfs(idx + len, parts + 1, s, cur + (parts == 0 ? "" : ".") + sub, res);
            }
        }
    }

public:
    static std::vector<std::string> restore_ip(const std::string& s) {
        std::vector<std::string> res;
        dfs(0, 0, s, "", res);
        return res;
    }
};

int main() {
    auto res = RestoreIPAddresses::restore_ip("25525511135");
    assert(res.size() == 2);
    assert(res[0] == "255.255.11.135");
    assert(res[1] == "255.255.111.35");

    std::cout << "restore_ip_addresses tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "matchsticks_to_square.cpp",
        "algorithm": "Matchsticks to Square",
        "purpose": "Determines whether an array of matchstick lengths can form a square with 4 equal sides.",
        "time_complexity": "O(4^N) time with sorted pruning",
        "space_complexity": "O(N) recursion stack",
        "preconditions": "Matchstick lengths are positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Matchsticks to Square
// Purpose: Determines whether an array of matchstick lengths can form a square with 4 equal sides.
// Time Complexity: O(4^N) time with sorted pruning
// Space Complexity: O(N) recursion stack
// Preconditions: Matchstick lengths are positive.

class MatchsticksToSquare {
private:
    static bool dfs(int idx, const std::vector<int>& matchsticks, int target, int sides[4]) {
        if (idx == (int)matchsticks.size()) {
            return sides[0] == target && sides[1] == target && sides[2] == target && sides[3] == target;
        }

        for (int i = 0; i < 4; ++i) {
            if (sides[i] + matchsticks[idx] > target) continue;
            // Prune duplicate side values
            int j = i - 1;
            while (j >= 0 && sides[i] != sides[j]) j--;
            if (j >= 0) continue;

            sides[i] += matchsticks[idx];
            if (dfs(idx + 1, matchsticks, target, sides)) return true;
            sides[i] -= matchsticks[idx];
        }
        return false;
    }

public:
    static bool makesquare(std::vector<int> matchsticks) {
        if (matchsticks.size() < 4) return false;
        long long total = std::accumulate(matchsticks.begin(), matchsticks.end(), 0LL);
        if (total % 4 != 0) return false;
        int target = total / 4;

        std::sort(matchsticks.rbegin(), matchsticks.rend());
        if (matchsticks[0] > target) return false;

        int sides[4] = {0, 0, 0, 0};
        return dfs(0, matchsticks, target, sides);
    }
};

int main() {
    std::vector<int> m1 = {1, 1, 2, 2, 2};
    assert(MatchsticksToSquare::makesquare(m1) == true);

    std::vector<int> m2 = {3, 3, 3, 3, 4};
    assert(MatchsticksToSquare::makesquare(m2) == false);

    std::cout << "matchsticks_to_square tests passed successfully.\n";
    return 0;
}
"""
    }
]

def main():
    TARGET_DIR.mkdir(parents=True, exist_ok=True)
    count = 0
    for item in FILES:
        path = TARGET_DIR / item["filename"]
        path.write_text(item["code"].strip() + "\n", encoding="utf-8")
        count += 1
        print(f"Wrote [{count}/{len(FILES)}]: {item['filename']}")
    print(f"\nBatch 5 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
