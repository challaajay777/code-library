import os

DIR = "Dynamic Programming"
os.makedirs(DIR, exist_ok=True)

implementations = [
    {
        "filename": "count_palindromic_subsequences_modulo.cpp",
        "algorithm": "Count Distinct Palindromic Subsequences Modulo 10^9+7",
        "purpose": "Computes the total number of non-empty palindromic subsequences modulo 10^9+7.",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "String of printable ASCII characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

long long count_palindromic_subsequences(const std::string& s) {
    static const int MOD = 1000000007;
    int n = s.size();
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) dp[i][i] = 1;

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
            } else {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::string s = "abcb";
    // Palindromic subsequences: "a", "b", "c", "b", "bcb", "bb" -> 6
    assert(count_palindromic_subsequences(s) == 6);
    return 0;
}
"""
    },
    {
        "filename": "longest_repeating_subsequence.cpp",
        "algorithm": "Longest Repeating Subsequence DP",
        "purpose": "Finds the length of the longest subsequence that appears at least twice without using the same indices.",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "String of characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int longest_repeating_subsequence(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

int main() {
    std::string s = "AABEBCDD";
    // Repeating subsequence: "ABD" of length 3
    assert(longest_repeating_subsequence(s) == 3);
    return 0;
}
"""
    },
    {
        "filename": "longest_arithmetic_subsequence.cpp",
        "algorithm": "Longest Arithmetic Subsequence DP",
        "purpose": "Finds the maximum length arithmetic progression subsequence in an arbitrary array.",
        "time": "O(N^2)",
        "space": "O(N^2)",
        "preconditions": "Array of integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>

int longest_arithmetic_subsequence(const std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) return n;

    std::vector<std::unordered_map<int, int>> dp(n);
    int ans = 2;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int diff = nums[i] - nums[j];
            int prev_len = dp[j].count(diff) ? dp[j][diff] : 1;
            dp[i][diff] = prev_len + 1;
            ans = std::max(ans, dp[i][diff]);
        }
    }
    return ans;
}

int main() {
    std::vector<int> nums = {3, 6, 9, 12};
    assert(longest_arithmetic_subsequence(nums) == 4);
    std::vector<int> nums2 = {9, 4, 7, 2, 10};
    assert(longest_arithmetic_subsequence(nums2) == 3); // {4, 7, 10}
    return 0;
}
"""
    },
    {
        "filename": "longest_arithmetic_subsequence_given_diff.cpp",
        "algorithm": "Longest Arithmetic Subsequence with Fixed Difference",
        "purpose": "Finds the length of the longest arithmetic subsequence with a fixed common difference d in linear time.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Array of integers, difference d.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>

int longest_subsequence_fixed_diff(const std::vector<int>& arr, int difference) {
    std::unordered_map<int, int> dp;
    int max_len = 0;
    for (int x : arr) {
        int prev = x - difference;
        int len = (dp.count(prev) ? dp[prev] : 0) + 1;
        dp[x] = len;
        max_len = std::max(max_len, len);
    }
    return max_len;
}

int main() {
    std::vector<int> arr = {1, 5, 7, 8, 5, 3, 4, 2, 1};
    assert(longest_subsequence_fixed_diff(arr, -2) == 4); // 7, 5, 3, 1
    return 0;
}
"""
    },
    {
        "filename": "maximum_sum_increasing_subsequence.cpp",
        "algorithm": "Maximum Sum Increasing Subsequence (MSIS) DP",
        "purpose": "Finds a strictly increasing subsequence that has the maximum sum of its elements.",
        "time": "O(N^2)",
        "space": "O(N)",
        "preconditions": "Array of positive integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long max_sum_increasing_subsequence(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    std::vector<long long> dp(n);
    for (int i = 0; i < n; ++i) dp[i] = nums[i];

    long long max_sum = dp[0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = std::max(dp[i], dp[j] + nums[i]);
            }
        }
        max_sum = std::max(max_sum, dp[i]);
    }
    return max_sum;
}

int main() {
    std::vector<int> nums = {1, 101, 2, 3, 100, 4, 5};
    // Increasing subsequence {1, 2, 3, 100} sums to 106
    assert(max_sum_increasing_subsequence(nums) == 106);
    return 0;
}
"""
    },
    {
        "filename": "building_bridges_problem.cpp",
        "algorithm": "Building Bridges Problem via LIS",
        "purpose": "Finds the maximum number of non-crossing bridges between two river banks.",
        "time": "O(N log N)",
        "space": "O(N)",
        "preconditions": "Pairs of north and south bank coordinates.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Bridge {
    int north, south;
};

int max_non_crossing_bridges(std::vector<Bridge>& bridges) {
    std::sort(bridges.begin(), bridges.end(), [](const Bridge& a, const Bridge& b) {
        if (a.north != b.north) return a.north < b.north;
        return a.south < b.south;
    });

    std::vector<int> tails;
    for (const auto& b : bridges) {
        auto it = std::lower_bound(tails.begin(), tails.end(), b.south);
        if (it == tails.end()) {
            tails.push_back(b.south);
        } else {
            *it = b.south;
        }
    }
    return tails.size();
}

int main() {
    std::vector<Bridge> bridges = {{6, 2}, {4, 3}, {2, 6}, {1, 5}};
    assert(max_non_crossing_bridges(bridges) == 2);
    return 0;
}
"""
    },
    {
        "filename": "maximum_length_chain_of_pairs.cpp",
        "algorithm": "Maximum Length Chain of Pairs DP",
        "purpose": "Finds the longest chain of pairs (a, b) such that pair[i].b < pair[i+1].a.",
        "time": "O(N log N)",
        "space": "O(N)",
        "preconditions": "Pairs with first < second.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int find_longest_chain(std::vector<std::pair<int, int>>& pairs) {
    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });

    int count = 0;
    int cur_end = -1e9;
    for (const auto& p : pairs) {
        if (p.first > cur_end) {
            count++;
            cur_end = p.second;
        }
    }
    return count;
}

int main() {
    std::vector<std::pair<int, int>> pairs = {{1, 2}, {2, 3}, {3, 4}};
    assert(find_longest_chain(pairs) == 2); // {1, 2} and {3, 4}
    return 0;
}
"""
    },
    {
        "filename": "russian_doll_envelopes.cpp",
        "algorithm": "Russian Doll Envelopes 2D LIS",
        "purpose": "Finds maximum number of envelopes that can fit inside one another (w1 < w2 and h1 < h2).",
        "time": "O(N log N)",
        "space": "O(N)",
        "preconditions": "List of (width, height) pairs.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_envelopes(std::vector<std::pair<int, int>>& envs) {
    std::sort(envs.begin(), envs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second; // descending on height to avoid picking same width
    });

    std::vector<int> tails;
    for (const auto& p : envs) {
        int h = p.second;
        auto it = std::lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) tails.push_back(h);
        else *it = h;
    }
    return tails.size();
}

int main() {
    std::vector<std::pair<int, int>> envs = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    assert(max_envelopes(envs) == 3); // [2,3] => [5,4] => [6,7]
    return 0;
}
"""
    },
    {
        "filename": "longest_valid_parentheses_dp.cpp",
        "algorithm": "Longest Valid Parentheses Substring DP",
        "purpose": "Finds the length of the longest valid (well-formed) parentheses substring.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "String of '(' and ')' characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

int longest_valid_parentheses(const std::string& s) {
    int n = s.size();
    std::vector<int> dp(n, 0);
    int max_len = 0;

    for (int i = 1; i < n; ++i) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + ((i - dp[i - 1] >= 2) ? dp[i - dp[i - 1] - 2] : 0) + 2;
            }
            max_len = std::max(max_len, dp[i]);
        }
    }
    return max_len;
}

int main() {
    assert(longest_valid_parentheses(")()())") == 4);
    assert(longest_valid_parentheses("(()") == 2);
    assert(longest_valid_parentheses("") == 0);
    return 0;
}
"""
    },
    {
        "filename": "decode_ways_dp.cpp",
        "algorithm": "Decode Ways DP (Letter Mappings)",
        "purpose": "Calculates number of ways to decode a digit string into characters 'A'-'Z'.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "Digit string s containing characters '0'-'9'.",
        "code": r"""#include <iostream>
#include <string>
#include <cassert>

int num_decodings(const std::string& s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    int prev2 = 1, prev1 = 1;

    for (int i = 1; i < n; ++i) {
        int cur = 0;
        if (s[i] != '0') cur += prev1;
        int two_digit = (s[i - 1] - '0') * 10 + (s[i] - '0');
        if (two_digit >= 10 && two_digit <= 26) cur += prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    assert(num_decodings("12") == 2); // "AB" (1 2) or "L" (12)
    assert(num_decodings("226") == 3); // "BZ", "VF", "BBF"
    assert(num_decodings("06") == 0);
    return 0;
}
"""
    },
    {
        "filename": "distinct_subsequences_count.cpp",
        "algorithm": "Distinct Subsequences Matching Count DP",
        "purpose": "Counts the number of distinct subsequences of string S that equal target string T.",
        "time": "O(N * M)",
        "space": "O(M)",
        "preconditions": "Strings s and t.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

long long num_distinct_subsequences(const std::string& s, const std::string& t) {
    int m = t.size();
    std::vector<unsigned long long> dp(m + 1, 0);
    dp[0] = 1;

    for (char c : s) {
        for (int j = m; j >= 1; --j) {
            if (c == t[j - 1]) {
                dp[j] += dp[j - 1];
            }
        }
    }
    return dp[m];
}

int main() {
    assert(num_distinct_subsequences("rabbbit", "rabbit") == 3);
    assert(num_distinct_subsequences("babgbag", "bag") == 5);
    return 0;
}
"""
    },
    {
        "filename": "dungeon_game_reverse_dp.cpp",
        "algorithm": "Dungeon Game Reverse DP",
        "purpose": "Determines the knight's minimum initial health required to reach bottom-right corner alive.",
        "time": "O(R * C)",
        "space": "O(C)",
        "preconditions": "2D grid of health bonuses/losses.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int calculate_minimum_hp(const std::vector<std::vector<int>>& dungeon) {
    int r = dungeon.size(), c = dungeon[0].size();
    const int INF = 1e9;
    std::vector<int> dp(c + 1, INF);
    dp[c - 1] = 1;

    for (int i = r - 1; i >= 0; --i) {
        for (int j = c - 1; j >= 0; --j) {
            int min_hp_exit = std::min(dp[j], dp[j + 1]);
            dp[j] = std::max(1, min_hp_exit - dungeon[i][j]);
        }
        dp[c] = INF;
    }
    return dp[0];
}

int main() {
    std::vector<std::vector<int>> dungeon = {
        {-2, -3,  3},
        {-5, -10, 1},
        {10,  30, -5}
    };
    assert(calculate_minimum_hp(dungeon) == 7);
    return 0;
}
"""
    },
    {
        "filename": "maximal_square_dp.cpp",
        "algorithm": "Maximal Square in Binary Matrix DP",
        "purpose": "Finds the largest square containing only 1s and returns its area.",
        "time": "O(R * C)",
        "space": "O(C)",
        "preconditions": "Grid of characters '0' and '1'.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int maximal_square(const std::vector<std::vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int r = matrix.size(), c = matrix[0].size();
    std::vector<int> dp(c + 1, 0);
    int max_side = 0, prev = 0;

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            int temp = dp[j];
            if (matrix[i - 1][j - 1] == '1') {
                dp[j] = std::min({dp[j], dp[j - 1], prev}) + 1;
                max_side = std::max(max_side, dp[j]);
            } else {
                dp[j] = 0;
            }
            prev = temp;
        }
    }
    return max_side * max_side;
}

int main() {
    std::vector<std::vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    assert(maximal_square(matrix) == 4);
    return 0;
}
"""
    },
    {
        "filename": "maximal_rectangle_histogram_dp.cpp",
        "algorithm": "Maximal Rectangle in Binary Matrix via Histogram DP",
        "purpose": "Finds the largest rectangle of 1s in a 2D binary matrix in O(R * C) time.",
        "time": "O(R * C)",
        "space": "O(C)",
        "preconditions": "2D binary grid of characters '0' and '1'.",
        "code": r"""#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>

int largest_rectangle_in_histogram(const std::vector<int>& heights) {
    std::stack<int> s;
    int max_area = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        int h = (i == n ? 0 : heights[i]);
        while (!s.empty() && heights[s.top()] > h) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            max_area = std::max(max_area, height * width);
        }
        s.push(i);
    }
    return max_area;
}

int maximal_rectangle(const std::vector<std::vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int r = matrix.size(), c = matrix[0].size();
    std::vector<int> heights(c, 0);
    int max_area = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == '1') heights[j]++;
            else heights[j] = 0;
        }
        max_area = std::max(max_area, largest_rectangle_in_histogram(heights));
    }
    return max_area;
}

int main() {
    std::vector<std::vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    assert(maximal_rectangle(matrix) == 6);
    return 0;
}
"""
    },
    {
        "filename": "count_square_submatrices_all_ones.cpp",
        "algorithm": "Count Square Submatrices with All Ones DP",
        "purpose": "Counts total number of all-1s square submatrices of any dimension.",
        "time": "O(R * C)",
        "space": "O(R * C)",
        "preconditions": "Grid of 0s and 1s.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int count_squares(std::vector<std::vector<int>>& matrix) {
    int r = matrix.size(), c = matrix[0].size();
    int count = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == 1 && i > 0 && j > 0) {
                matrix[i][j] = std::min({matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]}) + 1;
            }
            count += matrix[i][j];
        }
    }
    return count;
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 1}
    };
    assert(count_squares(matrix) == 15);
    return 0;
}
"""
    },
    {
        "filename": "frog_jump_k_steps.cpp",
        "algorithm": "Frog Jump with K Steps DP",
        "purpose": "Finds minimum cost to reach stone N where each jump can be between 1 and K stones.",
        "time": "O(N * K)",
        "space": "O(N)",
        "preconditions": "Array of stone heights, jump limit k >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

int frog_jump_k(const std::vector<int>& heights, int k) {
    int n = heights.size();
    const int INF = 1e9;
    std::vector<int> dp(n, INF);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= k && i + j < n; ++j) {
            dp[i + j] = std::min(dp[i + j], dp[i] + std::abs(heights[i] - heights[i + j]));
        }
    }
    return dp[n - 1];
}

int main() {
    std::vector<int> heights = {10, 30, 40, 50, 20};
    assert(frog_jump_k(heights, 3) == 30); // 10 -> 40 -> 20 = |10-40| + |40-20| = 30 + 20? No: 10 -> 30 -> 20 = 20 + 10 = 30
    return 0;
}
"""
    },
    {
        "filename": "jump_game_min_jumps.cpp",
        "algorithm": "Jump Game Minimum Jumps DP/Greedy",
        "purpose": "Finds minimum number of jumps to reach the last index from the first index.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "Array of non-negative integers where nums[i] is max jump length from i.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int jump_min_steps(const std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    int jumps = 0, cur_end = 0, farthest = 0;

    for (int i = 0; i < n - 1; ++i) {
        farthest = std::max(farthest, i + nums[i]);
        if (i == cur_end) {
            jumps++;
            cur_end = farthest;
            if (cur_end >= n - 1) break;
        }
    }
    return jumps;
}

int main() {
    std::vector<int> nums = {2, 3, 1, 1, 4};
    assert(jump_min_steps(nums) == 2); // 0 -> 1 -> 4
    return 0;
}
"""
    },
    {
        "filename": "house_robber_circular_dp.cpp",
        "algorithm": "House Robber Circular Street DP",
        "purpose": "Computes max money robbed when houses are arranged along a circle (first and last are neighbors).",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "Array of non-negative money values.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long rob_linear(const std::vector<int>& nums, int start, int end) {
    long long prev2 = 0, prev1 = 0;
    for (int i = start; i <= end; ++i) {
        long long cur = std::max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

long long rob_circular(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return std::max(rob_linear(nums, 0, n - 2), rob_linear(nums, 1, n - 1));
}

int main() {
    std::vector<int> nums = {2, 3, 2};
    assert(rob_circular(nums) == 3);
    std::vector<int> nums2 = {1, 2, 3, 1};
    assert(rob_circular(nums2) == 4); // rob 1 + 3 = 4
    return 0;
}
"""
    },
    {
        "filename": "house_robber_binary_tree.cpp",
        "algorithm": "House Robber on Binary Tree DP",
        "purpose": "Finds max amount robbed on binary tree where no two directly connected nodes can be robbed.",
        "time": "O(N)",
        "space": "O(H) recursion stack",
        "preconditions": "Binary tree node structure with values.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

struct RobResult {
    int rob_cur;
    int not_rob_cur;
};

RobResult dfs_tree(TreeNode* root) {
    if (!root) return {0, 0};
    RobResult l = dfs_tree(root->left);
    RobResult r = dfs_tree(root->right);

    int rob = root->val + l.not_rob_cur + r.not_rob_cur;
    int not_rob = std::max(l.rob_cur, l.not_rob_cur) + std::max(r.rob_cur, r.not_rob_cur);
    return {rob, not_rob};
}

int rob_tree(TreeNode* root) {
    auto res = dfs_tree(root);
    return std::max(res.rob_cur, res.not_rob_cur);
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);

    // Rob 3 (root) + 3 (left->right) + 1 (right->right) = 7
    assert(rob_tree(root) == 7);
    return 0;
}
"""
    },
    {
        "filename": "paint_house_colors_dp.cpp",
        "algorithm": "Paint House with K Colors DP",
        "purpose": "Finds the minimum cost to paint N houses with K colors such that no two adjacent houses have same color.",
        "time": "O(N * K)",
        "space": "O(K)",
        "preconditions": "N x K matrix of non-negative costs.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <climits>

int min_cost_paint_houses(const std::vector<std::vector<int>>& costs) {
    if (costs.empty()) return 0;
    int n = costs.size(), k = costs[0].size();
    if (k == 0) return 0;
    if (k == 1) return (n == 1) ? costs[0][0] : -1;

    std::vector<int> prev_cost = costs[0];

    for (int i = 1; i < n; ++i) {
        int min1 = INT_MAX, min2 = INT_MAX, min_idx = -1;
        for (int c = 0; c < k; ++c) {
            if (prev_cost[c] < min1) {
                min2 = min1;
                min1 = prev_cost[c];
                min_idx = c;
            } else if (prev_cost[c] < min2) {
                min2 = prev_cost[c];
            }
        }

        std::vector<int> cur_cost(k);
        for (int c = 0; c < k; ++c) {
            cur_cost[c] = costs[i][c] + (c == min_idx ? min2 : min1);
        }
        prev_cost = cur_cost;
    }

    int ans = INT_MAX;
    for (int c : prev_cost) ans = std::min(ans, c);
    return ans;
}

int main() {
    std::vector<std::vector<int>> costs = {
        {1, 5, 3},
        {2, 9, 4}
    };
    // House 0 color 0 (cost 1), House 1 color 2 (cost 4) -> 5
    assert(min_cost_paint_houses(costs) == 5);
    return 0;
}
"""
    },
    {
        "filename": "paint_fence_dp.cpp",
        "algorithm": "Paint Fence DP (At Most Two Adjacent Same)",
        "purpose": "Calculates number of ways to paint fence of n posts with k colors with at most two consecutive posts same.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "n >= 1, k >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

long long num_ways_paint_fence(int n, int k) {
    if (n == 0 || k == 0) return 0;
    if (n == 1) return k;
    long long same = k;
    long long diff = 1LL * k * (k - 1);

    for (int i = 3; i <= n; ++i) {
        long long prev_diff = diff;
        diff = (same + diff) * (k - 1);
        same = prev_diff;
    }
    return same + diff;
}

int main() {
    assert(num_ways_paint_fence(3, 2) == 6);
    return 0;
}
"""
    },
    {
        "filename": "tiling_with_dominoes_3xn.cpp",
        "algorithm": "3xN Domino Tiling DP",
        "purpose": "Finds number of ways to completely tile a 3 x N grid with 2x1 dominoes.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

long long count_3xn_domino_tilings(int n) {
    if (n % 2 != 0) return 0;
    if (n == 0) return 1;

    std::vector<long long> A(n + 1, 0); // completely filled
    std::vector<long long> B(n + 1, 0); // one corner missing

    A[0] = 1; A[1] = 0;
    B[0] = 0; B[1] = 1;

    for (int i = 2; i <= n; ++i) {
        A[i] = A[i - 2] + 2 * B[i - 1];
        B[i] = A[i - 1] + B[i - 2];
    }
    return A[n];
}

int main() {
    assert(count_3xn_domino_tilings(2) == 3);
    assert(count_3xn_domino_tilings(4) == 11);
    assert(count_3xn_domino_tilings(3) == 0);
    return 0;
}
"""
    },
    {
        "filename": "tiling_trominoes_dp.cpp",
        "algorithm": "Domino and Tromino Tiling 2xN DP",
        "purpose": "Finds number of ways to tile a 2 x N board with dominoes and L-shaped trominoes modulo 10^9+7.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "N >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

long long domino_tromino_tiling(int n) {
    static const int MOD = 1000000007;
    if (n <= 1) return 1;
    if (n == 2) return 2;

    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1; dp[1] = 1; dp[2] = 2;

    for (int i = 3; i <= n; ++i) {
        // dp[i] = 2 * dp[i-1] + dp[i-3]
        dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
    }
    return dp[n];
}

int main() {
    assert(domino_tromino_tiling(3) == 5);
    assert(domino_tromino_tiling(1) == 1);
    return 0;
}
"""
    },
    {
        "filename": "count_derangements_dp.cpp",
        "algorithm": "Count Derangements DP",
        "purpose": "Calculates number of permutations of N elements where no element appears in its original position.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <cassert>

long long count_derangements(int n) {
    static const int MOD = 1000000007;
    if (n <= 1) return 0;
    if (n == 2) return 1;

    long long prev2 = 0; // D(1)
    long long prev1 = 1; // D(2)

    for (int i = 3; i <= n; ++i) {
        long long cur = (1LL * (i - 1) * (prev1 + prev2)) % MOD;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    assert(count_derangements(1) == 0);
    assert(count_derangements(2) == 1);
    assert(count_derangements(3) == 2);
    assert(count_derangements(4) == 9);
    return 0;
}
"""
    },
    {
        "filename": "partition_k_subsets_equal_sum.cpp",
        "algorithm": "Partition Array into K Subsets of Equal Sum DP",
        "purpose": "Determines whether an array can be partitioned into K subsets each having equal sum via bitmask DP.",
        "time": "O(K * 2^N)",
        "space": "O(2^N)",
        "preconditions": "1 <= K <= N <= 16.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

bool can_partition_k_subsets(const std::vector<int>& nums, int k) {
    int total = std::accumulate(nums.begin(), nums.end(), 0);
    if (total % k != 0) return false;
    int target = total / k;
    int n = nums.size();

    int total_states = 1 << n;
    std::vector<int> dp(total_states, -1);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == -1) continue;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) && dp[mask] + nums[i] <= target) {
                dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target;
            }
        }
    }
    return dp[total_states - 1] == 0;
}

int main() {
    std::vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    assert(can_partition_k_subsets(nums, 4));
    assert(!can_partition_k_subsets({1, 2, 3, 4}, 3));
    return 0;
}
"""
    },
    {
        "filename": "matchsticks_to_square_bitmask.cpp",
        "algorithm": "Matchsticks to Square Bitmask DP",
        "purpose": "Determines whether all matchsticks can be assembled into a perimeter of a square.",
        "time": "O(2^N)",
        "space": "O(2^N)",
        "preconditions": "Matchsticks array of positive lengths.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

bool makesquare(const std::vector<int>& matchsticks) {
    int n = matchsticks.size();
    if (n < 4) return false;
    int perimeter = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
    if (perimeter % 4 != 0) return false;
    int side = perimeter / 4;

    int total_states = 1 << n;
    std::vector<int> dp(total_states, -1);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == -1) continue;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) && dp[mask] + matchsticks[i] <= side) {
                dp[mask | (1 << i)] = (dp[mask] + matchsticks[i]) % side;
            }
        }
    }
    return dp[total_states - 1] == 0;
}

int main() {
    assert(makesquare({1, 1, 2, 2, 2}));
    assert(!makesquare({3, 3, 3, 3, 4}));
    return 0;
}
"""
    },
    {
        "filename": "maximum_students_taking_exam.cpp",
        "algorithm": "Maximum Students Taking Exam Profile DP",
        "purpose": "Finds max students seated in classroom without cheating diagonally or horizontally.",
        "time": "O(R * 2^C * 2^C)",
        "space": "O(2^C)",
        "preconditions": "Classroom grid with '.' (available) and '#' (broken).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_students(const std::vector<std::vector<char>>& seats) {
    int r = seats.size(), c = seats[0].size();
    std::vector<int> valid_seats(r, 0);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (seats[i][j] == '.') {
                valid_seats[i] |= (1 << j);
            }
        }
    }

    int total_masks = 1 << c;
    std::vector<int> dp(total_masks, -1);
    dp[0] = 0;

    for (int i = 0; i < r; ++i) {
        std::vector<int> next_dp(total_masks, -1);
        for (int mask = 0; mask < total_masks; ++mask) {
            if ((mask & valid_seats[i]) != mask) continue;
            if (mask & (mask >> 1)) continue; // no adjacent seats in same row

            int count = __builtin_popcount(mask);
            for (int prev_mask = 0; prev_mask < total_masks; ++prev_mask) {
                if (dp[prev_mask] == -1) continue;
                if ((mask & (prev_mask >> 1)) || (mask & (prev_mask << 1))) continue; // diagonal cheat
                next_dp[mask] = std::max(next_dp[mask], dp[prev_mask] + count);
            }
        }
        dp = next_dp;
    }

    int ans = 0;
    for (int val : dp) ans = std::max(ans, val);
    return ans;
}

int main() {
    std::vector<std::vector<char>> seats = {
        {'#', '.', '#', '#', '.', '#'},
        {'.', '#', '#', '#', '#', '.'},
        {'#', '.', '#', '#', '.', '#'}
    };
    assert(max_students(seats) == 4);
    return 0;
}
"""
    },
    {
        "filename": "shortest_hamiltonian_cycle_metric.cpp",
        "algorithm": "Metric TSP Shortest Hamiltonian Cycle DP",
        "purpose": "Calculates minimum Hamiltonian cycle cost starting and returning to node 0.",
        "time": "O(N^2 * 2^N)",
        "space": "O(N * 2^N)",
        "preconditions": "Adjacency cost matrix of N vertices (N <= 18).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

int shortest_hamiltonian_cycle(int n, const std::vector<std::vector<int>>& dist) {
    int total = 1 << n;
    std::vector<std::vector<int>> dp(total, std::vector<int>(n, INF));
    dp[1][0] = 0;

    for (int mask = 1; mask < total; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v))) {
                    dp[mask | (1 << v)][v] = std::min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
    }

    int ans = INF;
    int full = total - 1;
    for (int u = 1; u < n; ++u) {
        ans = std::min(ans, dp[full][u] + dist[u][0]);
    }
    return ans;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    assert(shortest_hamiltonian_cycle(n, dist) == 80);
    return 0;
}
"""
    },
    {
        "filename": "number_of_paths_exact_k_steps_dag.cpp",
        "algorithm": "Count Paths of Exact Length K in DAG DP",
        "purpose": "Counts the number of paths between source and destination of length exactly K edges.",
        "time": "O(K * (V + E))",
        "space": "O(V)",
        "preconditions": "Directed graph, step count K >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

long long count_paths_k_steps(int n, const std::vector<std::vector<int>>& adj, int src, int dst, int k) {
    std::vector<long long> dp(n, 0);
    dp[src] = 1;

    for (int step = 0; step < k; ++step) {
        std::vector<long long> next_dp(n, 0);
        for (int u = 0; u < n; ++u) {
            if (dp[u] == 0) continue;
            for (int v : adj[u]) {
                next_dp[v] += dp[u];
            }
        }
        dp = next_dp;
    }
    return dp[dst];
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);

    // From 0 to 3 of length 2: (0->1->3) and (0->2->3) -> 2 paths
    assert(count_paths_k_steps(n, adj, 0, 3, 2) == 2);
    return 0;
}
"""
    },
    {
        "filename": "dice_roll_simulation_consecutive_limit.cpp",
        "algorithm": "Dice Roll Simulation with Consecutive Face Limits DP",
        "purpose": "Counts distinct sequences of n dice rolls where face i cannot appear more than rollMax[i] consecutive times.",
        "time": "O(N * 6 * MaxRoll)",
        "space": "O(6 * MaxRoll)",
        "preconditions": "n >= 1, rollMax has length 6.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

int die_simulator(int n, const std::vector<int>& rollMax) {
    static const int MOD = 1000000007;
    // dp[face][consecutive_count]
    std::vector<std::vector<int>> dp(6, std::vector<int>(16, 0));
    for (int f = 0; f < 6; ++f) dp[f][1] = 1;

    for (int step = 2; step <= n; ++step) {
        std::vector<std::vector<int>> next_dp(6, std::vector<int>(16, 0));
        for (int f = 0; f < 6; ++f) {
            for (int prev_f = 0; prev_f < 6; ++prev_f) {
                if (f != prev_f) {
                    for (int k = 1; k <= rollMax[prev_f]; ++k) {
                        next_dp[f][1] = (next_dp[f][1] + dp[prev_f][k]) % MOD;
                    }
                } else {
                    for (int k = 1; k < rollMax[f]; ++k) {
                        next_dp[f][k + 1] = (next_dp[f][k + 1] + dp[f][k]) % MOD;
                    }
                }
            }
        }
        dp = next_dp;
    }

    long long total = 0;
    for (int f = 0; f < 6; ++f) {
        for (int k = 1; k <= rollMax[f]; ++k) {
            total = (total + dp[f][k]) % MOD;
        }
    }
    return total;
}

int main() {
    std::vector<int> rollMax = {1, 1, 2, 2, 2, 3};
    assert(die_simulator(2, rollMax) == 34); // 36 - 2 invalid ("11", "22")
    return 0;
}
"""
    },
    {
        "filename": "knight_dialer_phone_keypad.cpp",
        "algorithm": "Knight Dialer Distinct Numbers DP",
        "purpose": "Calculates number of distinct phone numbers of length n dialed by valid chess knight moves.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

int knight_dialer(int n) {
    static const int MOD = 1000000007;
    std::vector<std::vector<int>> moves = {
        {4, 6},    // 0
        {6, 8},    // 1
        {7, 9},    // 2
        {4, 8},    // 3
        {0, 3, 9}, // 4
        {},        // 5
        {0, 1, 7}, // 6
        {2, 6},    // 7
        {1, 3},    // 8
        {2, 4}     // 9
    };

    std::vector<long long> dp(10, 1);

    for (int step = 2; step <= n; ++step) {
        std::vector<long long> next_dp(10, 0);
        for (int digit = 0; digit < 10; ++digit) {
            for (int neighbor : moves[digit]) {
                next_dp[neighbor] = (next_dp[neighbor] + dp[digit]) % MOD;
            }
        }
        dp = next_dp;
    }

    long long sum = 0;
    for (long long x : dp) sum = (sum + x) % MOD;
    return sum;
}

int main() {
    assert(knight_dialer(1) == 10);
    assert(knight_dialer(2) == 20);
    assert(knight_dialer(3) == 46);
    return 0;
}
"""
    },
    {
        "filename": "count_vowel_permutation_graph_dp.cpp",
        "algorithm": "Count Vowel Permutation Graph DP",
        "purpose": "Counts strings of length n made of vowels obeying specific transition rules modulo 10^9+7.",
        "time": "O(N)",
        "space": "O(1)",
        "preconditions": "n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

int count_vowel_permutation(int n) {
    static const int MOD = 1000000007;
    long long a = 1, e = 1, i = 1, o = 1, u = 1;

    for (int step = 2; step <= n; ++step) {
        long long next_a = (e + i + u) % MOD;
        long long next_e = (a + i) % MOD;
        long long next_i = (e + o) % MOD;
        long long next_o = i % MOD;
        long long next_u = (i + o) % MOD;

        a = next_a; e = next_e; i = next_i; o = next_o; u = next_u;
    }
    return (a + e + i + o + u) % MOD;
}

int main() {
    assert(count_vowel_permutation(1) == 5);
    assert(count_vowel_permutation(2) == 10);
    assert(count_vowel_permutation(5) == 68);
    return 0;
}
"""
    },
    {
        "filename": "regular_expression_matching_nfa_dp.cpp",
        "algorithm": "Regular Expression Matching NFA DP",
        "purpose": "Matches string against regular expression with '.' and '*' characters via 2D DP.",
        "time": "O(N * M)",
        "space": "O(N * M)",
        "preconditions": "String s and regex pattern p.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

bool is_regex_match(const std::string& s, const std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= m; ++j) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2]; // zero occurrences of previous char
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }
    return dp[n][m];
}

int main() {
    assert(is_regex_match("aa", "a*"));
    assert(is_regex_match("ab", ".*"));
    assert(!is_regex_match("mississippi", "mis*is*p*."));
    return 0;
}
"""
    },
    {
        "filename": "ugly_numbers_ii_three_pointers.cpp",
        "algorithm": "N-th Ugly Number Three-Pointer DP",
        "purpose": "Finds the n-th positive integer whose prime factors are limited to 2, 3, and 5.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long nth_ugly_number(int n) {
    std::vector<long long> dp(n);
    dp[0] = 1;
    int p2 = 0, p3 = 0, p5 = 0;

    for (int i = 1; i < n; ++i) {
        long long next2 = dp[p2] * 2;
        long long next3 = dp[p3] * 3;
        long long next5 = dp[p5] * 5;

        long long next_ugly = std::min({next2, next3, next5});
        dp[i] = next_ugly;

        if (next_ugly == next2) p2++;
        if (next_ugly == next3) p3++;
        if (next_ugly == next5) p5++;
    }
    return dp[n - 1];
}

int main() {
    assert(nth_ugly_number(1) == 1);
    assert(nth_ugly_number(10) == 12); // [1, 2, 3, 4, 5, 6, 8, 9, 10, 12]
    return 0;
}
"""
    },
    {
        "filename": "super_ugly_numbers_primes_dp.cpp",
        "algorithm": "Super Ugly Numbers Multi-Prime DP",
        "purpose": "Finds the n-th positive integer whose prime factors are all in a given prime list.",
        "time": "O(N * K)",
        "space": "O(N + K)",
        "preconditions": "n >= 1, primes is a sorted array of distinct primes.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <climits>

long long nth_super_ugly_number(int n, const std::vector<int>& primes) {
    int k = primes.size();
    std::vector<long long> dp(n);
    dp[0] = 1;
    std::vector<int> ptr(k, 0);

    for (int i = 1; i < n; ++i) {
        long long next_val = LLONG_MAX;
        for (int j = 0; j < k; ++j) {
            next_val = std::min(next_val, dp[ptr[j]] * primes[j]);
        }
        dp[i] = next_val;
        for (int j = 0; j < k; ++j) {
            if (dp[ptr[j]] * primes[j] == next_val) {
                ptr[j]++;
            }
        }
    }
    return dp[n - 1];
}

int main() {
    std::vector<int> primes = {2, 7, 13, 19};
    assert(nth_super_ugly_number(12, primes) == 32);
    return 0;
}
"""
    },
    {
        "filename": "perfect_squares_sum_dp.cpp",
        "algorithm": "Minimum Perfect Squares Sum DP",
        "purpose": "Finds least number of perfect square numbers which sum to n (Lagrange's 4-square theorem bounded).",
        "time": "O(N * sqrt(N))",
        "space": "O(N)",
        "preconditions": "n >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int num_squares(int n) {
    std::vector<int> dp(n + 1, 1e9);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            dp[i] = std::min(dp[i], dp[i - j * j] + 1);
        }
    }
    return dp[n];
}

int main() {
    assert(num_squares(12) == 3); // 4 + 4 + 4
    assert(num_squares(13) == 2); // 4 + 9
    return 0;
}
"""
    },
    {
        "filename": "integer_break_product_maximization.cpp",
        "algorithm": "Integer Break Product Maximization DP",
        "purpose": "Breaks integer n into sum of at least two positive integers maximizing their product.",
        "time": "O(N^2)",
        "space": "O(N)",
        "preconditions": "n >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long integer_break(int n) {
    std::vector<long long> dp(n + 1, 0);
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            dp[i] = std::max({dp[i], 1LL * j * (i - j), 1LL * j * dp[i - j]});
        }
    }
    return dp[n];
}

int main() {
    assert(integer_break(2) == 1);
    assert(integer_break(10) == 36); // 3 + 3 + 4 -> 3 * 3 * 4 = 36
    return 0;
}
"""
    }
]

for idx, item in enumerate(implementations, 1):
    path = os.path.join(DIR, item["filename"])
    header = f"""// Algorithm: {item["algorithm"]}
// Purpose: {item["purpose"]}
// Time Complexity: {item["time"]}
// Space Complexity: {item["space"]}
// Preconditions: {item["preconditions"]}

"""
    with open(path, "w", encoding="utf-8") as f:
        f.write(header + item["code"].strip() + "\n")
    print(f"Wrote [{idx}/{len(implementations)}]: {item['filename']}")

print(f"\nBatch 10b (Dynamic Programming) completed: {len(implementations)} implementations written.")
