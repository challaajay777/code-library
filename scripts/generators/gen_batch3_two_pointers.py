#!/usr/bin/env python3
"""
Batch 3 Generator: Two Pointers and Sliding Window (25 implementations)
Target Directory: Two Pointers and Sliding Window
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Two Pointers and Sliding Window"

FILES = [
    {
        "filename": "two_sum_sorted.cpp",
        "algorithm": "Two Sum (Sorted Array Two Pointers)",
        "purpose": "Finds two indices in a 1-indexed sorted array that add up to target in O(N) time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array sorted in non-decreasing order.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Two Sum (Sorted Array Two Pointers)
// Purpose: Finds two indices in a 1-indexed sorted array that add up to target in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array sorted in non-decreasing order.

class TwoSumSorted {
public:
    static std::pair<int, int> two_sum(const std::vector<int>& numbers, int target) {
        int left = 0, right = (int)numbers.size() - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1}; // 1-based indexing
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {-1, -1};
    }
};

int main() {
    std::vector<int> a = {2, 7, 11, 15};
    auto [i, j] = TwoSumSorted::two_sum(a, 9);
    assert(i == 1 && j == 2);

    std::vector<int> b = {2, 3, 4};
    auto [i2, j2] = TwoSumSorted::two_sum(b, 6);
    assert(i2 == 1 && j2 == 3);

    std::cout << "two_sum_sorted tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "three_sum_two_pointers.cpp",
        "algorithm": "3-Sum (Two Pointers)",
        "purpose": "Finds all unique triplets [a, b, c] such that a + b + c = 0 in O(N^2) time and O(1) extra space.",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(1) auxiliary space beyond output",
        "preconditions": "General array of integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 3-Sum (Two Pointers)
// Purpose: Finds all unique triplets [a, b, c] such that a + b + c = 0 in O(N^2) time and O(1) extra space.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space beyond output
// Preconditions: General array of integers.

class ThreeSumTwoPointers {
public:
    static std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> res;

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {-1, 0, 1, 2, -1, -4};
    auto trips = ThreeSumTwoPointers::three_sum(a);
    assert(trips.size() == 2);
    assert(trips[0] == std::vector<int>({-1, -1, 2}));
    assert(trips[1] == std::vector<int>({-1, 0, 1}));

    std::cout << "three_sum_two_pointers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "three_sum_closest.cpp",
        "algorithm": "3-Sum Closest",
        "purpose": "Finds three integers in array whose sum is closest to a target integer in O(N^2) time.",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(1) auxiliary space beyond sorting",
        "preconditions": "Array length >= 3.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: 3-Sum Closest
// Purpose: Finds three integers in array whose sum is closest to a target integer in O(N^2) time.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space beyond sorting
// Preconditions: Array length >= 3.

class ThreeSumClosest {
public:
    static int three_sum_closest(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        assert(n >= 3);
        int closest_sum = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (std::abs(sum - target) < std::abs(closest_sum - target)) {
                    closest_sum = sum;
                }
                if (sum < target) {
                    left++;
                } else if (sum > target) {
                    right--;
                } else {
                    return target;
                }
            }
        }
        return closest_sum;
    }
};

int main() {
    std::vector<int> a = {-1, 2, 1, -4};
    assert(ThreeSumClosest::three_sum_closest(a, 1) == 2); // (-1 + 2 + 1 = 2)

    std::vector<int> b = {0, 0, 0};
    assert(ThreeSumClosest::three_sum_closest(b, 1) == 0);

    std::cout << "three_sum_closest tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "four_sum_two_pointers.cpp",
        "algorithm": "4-Sum (Two Pointers)",
        "purpose": "Finds all unique quadruplets summing to target value in O(N^3) time and O(1) auxiliary space.",
        "time_complexity": "O(N^3) time",
        "space_complexity": "O(1) auxiliary space beyond output",
        "preconditions": "64-bit integer sum calculations.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 4-Sum (Two Pointers)
// Purpose: Finds all unique quadruplets summing to target value in O(N^3) time and O(1) auxiliary space.
// Time Complexity: O(N^3) time
// Space Complexity: O(1) auxiliary space beyond output
// Preconditions: 64-bit integer sum calculations.

class FourSumTwoPointers {
public:
    static std::vector<std::vector<int>> four_sum(std::vector<int>& nums, long long target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> res;

        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int left = j + 1, right = n - 1;
                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 0, -1, 0, -2, 2};
    auto quad = FourSumTwoPointers::four_sum(a, 0);
    assert(quad.size() == 3);

    std::cout << "four_sum_two_pointers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "container_with_most_water.cpp",
        "algorithm": "Container with Most Water",
        "purpose": "Finds two vertical lines that together with the x-axis form a container holding the maximum water in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Heights are non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Container with Most Water
// Purpose: Finds two vertical lines that together with the x-axis form a container holding the maximum water in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Heights are non-negative.

class ContainerWithMostWater {
public:
    static long long max_area(const std::vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        long long max_water = 0;

        while (left < right) {
            long long h = std::min(height[left], height[right]);
            max_water = std::max(max_water, h * (right - left));

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return max_water;
    }
};

int main() {
    std::vector<int> h = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    assert(ContainerWithMostWater::max_area(h) == 49);

    std::vector<int> h2 = {1, 1};
    assert(ContainerWithMostWater::max_area(h2) == 1);

    std::cout << "container_with_most_water tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "trapping_rainwater_two_pointers.cpp",
        "algorithm": "Trapping Rainwater (Two Pointers)",
        "purpose": "Computes total rainwater trapped between elevation bars in O(N) time using O(1) extra space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Elevation heights are non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Trapping Rainwater (Two Pointers)
// Purpose: Computes total rainwater trapped between elevation bars in O(N) time using O(1) extra space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elevation heights are non-negative.

class TrappingRainwaterTwoPointers {
public:
    static long long trap(const std::vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int left_max = 0, right_max = 0;
        long long water = 0;

        while (left < right) {
            if (height[left] <= height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    water += left_max - height[left];
                }
                left++;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    water += right_max - height[right];
                }
                right--;
            }
        }
        return water;
    }
};

int main() {
    std::vector<int> h = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(TrappingRainwaterTwoPointers::trap(h) == 6);

    std::vector<int> h2 = {4, 2, 0, 3, 2, 5};
    assert(TrappingRainwaterTwoPointers::trap(h2) == 9);

    std::cout << "trapping_rainwater_two_pointers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "min_window_substring.cpp",
        "algorithm": "Minimum Window Substring",
        "purpose": "Finds the minimum length substring of S that contains all characters of pattern T in O(|S| + |T|).",
        "time_complexity": "O(|S| + |T|) time",
        "space_complexity": "O(Sigma) space for character frequency table",
        "preconditions": "String characters in ASCII range.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Minimum Window Substring
// Purpose: Finds the minimum length substring of S that contains all characters of pattern T in O(|S| + |T|).
// Time Complexity: O(|S| + |T|) time
// Space Complexity: O(Sigma) space for character frequency table
// Preconditions: String characters in ASCII range.

class MinimumWindowSubstring {
public:
    static std::string min_window(const std::string& s, const std::string& t) {
        if (s.empty() || t.empty() || s.size() < t.size()) return "";

        std::vector<int> need(128, 0);
        for (char c : t) need[(unsigned char)c]++;

        int remaining = t.size();
        int left = 0, min_start = 0, min_len = 1e9;

        for (int right = 0; right < (int)s.size(); ++right) {
            if (need[(unsigned char)s[right]] > 0) {
                remaining--;
            }
            need[(unsigned char)s[right]]--;

            while (remaining == 0) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    min_start = left;
                }
                need[(unsigned char)s[left]]++;
                if (need[(unsigned char)s[left]] > 0) {
                    remaining++;
                }
                left++;
            }
        }
        return (min_len == 1e9) ? "" : s.substr(min_start, min_len);
    }
};

int main() {
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";
    assert(MinimumWindowSubstring::min_window(s, t) == "BANC");

    assert(MinimumWindowSubstring::min_window("a", "a") == "a");
    assert(MinimumWindowSubstring::min_window("a", "aa") == "");

    std::cout << "min_window_substring tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_substring_without_repeating_characters.cpp",
        "algorithm": "Longest Substring Without Repeating Characters",
        "purpose": "Finds the length of the longest contiguous substring containing all distinct characters in O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(Sigma) auxiliary space",
        "preconditions": "String characters in ASCII range.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Substring Without Repeating Characters
// Purpose: Finds the length of the longest contiguous substring containing all distinct characters in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(Sigma) auxiliary space
// Preconditions: String characters in ASCII range.

class LongestSubstringDistinct {
public:
    static int length_of_longest_substring(const std::string& s) {
        std::vector<int> last_pos(256, -1);
        int max_len = 0;
        int left = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char c = s[right];
            if (last_pos[c] >= left) {
                left = last_pos[c] + 1;
            }
            last_pos[c] = right;
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    assert(LongestSubstringDistinct::length_of_longest_substring("abcabcbb") == 3);
    assert(LongestSubstringDistinct::length_of_longest_substring("bbbbb") == 1);
    assert(LongestSubstringDistinct::length_of_longest_substring("pwwkew") == 3);

    std::cout << "longest_substring_without_repeating_characters tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_substring_k_distinct.cpp",
        "algorithm": "Longest Substring with At Most K Distinct Characters",
        "purpose": "Finds maximum length of a substring containing at most K unique characters in O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(Sigma) space",
        "preconditions": "K >= 0.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Substring with At Most K Distinct Characters
// Purpose: Finds maximum length of a substring containing at most K unique characters in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(Sigma) space
// Preconditions: K >= 0.

class LongestSubstringKDistinct {
public:
    static int length_of_longest_k_distinct(const std::string& s, int k) {
        if (k == 0) return 0;
        std::vector<int> freq(256, 0);
        int distinct = 0;
        int left = 0;
        int max_len = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char c = s[right];
            if (freq[c] == 0) distinct++;
            freq[c]++;

            while (distinct > k) {
                unsigned char lc = s[left];
                freq[lc]--;
                if (freq[lc] == 0) distinct--;
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    std::string s = "eceba";
    assert(LongestSubstringKDistinct::length_of_longest_k_distinct(s, 2) == 3); // "ece"

    std::string s2 = "aa";
    assert(LongestSubstringKDistinct::length_of_longest_k_distinct(s2, 1) == 2);

    std::cout << "longest_substring_k_distinct tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_substring_exact_k_distinct.cpp",
        "algorithm": "Subarrays with Exactly K Distinct Characters",
        "purpose": "Counts total contiguous subarrays/substrings containing exactly K distinct elements in O(N) via atMost(K) - atMost(K - 1).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(Sigma) auxiliary space",
        "preconditions": "K >= 1.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "subarray_product_less_than_k.cpp",
        "algorithm": "Subarray Product Less Than K",
        "purpose": "Counts contiguous subarrays whose product is strictly less than K in an array of positive integers in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "All elements positive integers; K >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarray Product Less Than K
// Purpose: Counts contiguous subarrays whose product is strictly less than K in an array of positive integers in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements positive integers; K >= 0.

class SubarrayProductLessThanK {
public:
    static long long num_subarray_product_less_than_k(const std::vector<int>& nums, int k) {
        if (k <= 1) return 0;
        long long prod = 1;
        long long count = 0;
        int left = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            prod *= nums[right];
            while (prod >= k && left <= right) {
                prod /= nums[left++];
            }
            count += (right - left + 1);
        }
        return count;
    }
};

int main() {
    std::vector<int> a = {10, 5, 2, 6};
    // For k=100: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6] -> 8
    assert(SubarrayProductLessThanK::num_subarray_product_less_than_k(a, 100) == 8);

    std::vector<int> b = {1, 2, 3};
    assert(SubarrayProductLessThanK::num_subarray_product_less_than_k(b, 0) == 0);

    std::cout << "subarray_product_less_than_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_size_subarray_sum.cpp",
        "algorithm": "Minimum Size Subarray Sum",
        "purpose": "Finds minimal length of contiguous subarray with sum >= target in an array of positive integers in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Elements are positive integers; target > 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Size Subarray Sum
// Purpose: Finds minimal length of contiguous subarray with sum >= target in an array of positive integers in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements are positive integers; target > 0.

class MinSizeSubarraySum {
public:
    static int min_sub_array_len(int target, const std::vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        long long sum = 0;
        int min_len = 1e9;

        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                min_len = std::min(min_len, right - left + 1);
                sum -= nums[left++];
            }
        }
        return (min_len == 1e9) ? 0 : min_len;
    }
};

int main() {
    std::vector<int> a = {2, 3, 1, 2, 4, 3};
    assert(MinSizeSubarraySum::min_sub_array_len(7, a) == 2); // [4, 3]

    std::vector<int> b = {1, 4, 4};
    assert(MinSizeSubarraySum::min_sub_array_len(4, b) == 1);

    std::cout << "minimum_size_subarray_sum tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "fruit_into_baskets.cpp",
        "algorithm": "Fruit Into Baskets (Sliding Window At Most 2 Types)",
        "purpose": "Finds length of the longest contiguous subarray containing at most two distinct values in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Non-empty vector of tree fruit types.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

// Algorithm: Fruit Into Baskets (Sliding Window At Most 2 Types)
// Purpose: Finds length of the longest contiguous subarray containing at most two distinct values in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-empty vector of tree fruit types.

class FruitIntoBaskets {
public:
    static int total_fruit(const std::vector<int>& fruits) {
        std::unordered_map<int, int> count;
        int left = 0;
        int max_picked = 0;

        for (int right = 0; right < (int)fruits.size(); ++right) {
            count[fruits[right]]++;
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0) {
                    count.erase(fruits[left]);
                }
                left++;
            }
            max_picked = std::max(max_picked, right - left + 1);
        }
        return max_picked;
    }
};

int main() {
    std::vector<int> f1 = {1, 2, 1};
    assert(FruitIntoBaskets::total_fruit(f1) == 3);

    std::vector<int> f2 = {0, 1, 2, 2};
    assert(FruitIntoBaskets::total_fruit(f2) == 3); // [1, 2, 2]

    std::vector<int> f3 = {1, 2, 3, 2, 2};
    assert(FruitIntoBaskets::total_fruit(f3) == 4); // [2, 3, 2, 2]

    std::cout << "fruit_into_baskets tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_repeating_character_replacement.cpp",
        "algorithm": "Longest Repeating Character Replacement",
        "purpose": "Finds the length of the longest substring containing identical letters after changing at most K letters in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(26) space",
        "preconditions": "String consists of uppercase English letters; K >= 0.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Repeating Character Replacement
// Purpose: Finds the length of the longest substring containing identical letters after changing at most K letters in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(26) space
// Preconditions: String consists of uppercase English letters; K >= 0.

class CharacterReplacement {
public:
    static int character_replacement(const std::string& s, int k) {
        std::vector<int> count(26, 0);
        int max_freq = 0;
        int left = 0;
        int max_len = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            count[s[right] - 'A']++;
            max_freq = std::max(max_freq, count[s[right] - 'A']);

            // If remaining characters to change exceeds k, shrink window
            while ((right - left + 1) - max_freq > k) {
                count[s[left] - 'A']--;
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    assert(CharacterReplacement::character_replacement("ABAB", 2) == 4);
    assert(CharacterReplacement::character_replacement("AABABBA", 1) == 4);

    std::cout << "longest_repeating_character_replacement tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "permutation_in_string.cpp",
        "algorithm": "Permutation in String (Sliding Window Frequency Match)",
        "purpose": "Determines whether string s2 contains a contiguous permutation of string s1 in O(|s2|) time.",
        "time_complexity": "O(|s2|) time",
        "space_complexity": "O(26) space",
        "preconditions": "Strings consist of lowercase English letters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Permutation in String (Sliding Window Frequency Match)
// Purpose: Determines whether string s2 contains a contiguous permutation of string s1 in O(|s2|) time.
// Time Complexity: O(|s2|) time
// Space Complexity: O(26) space
// Preconditions: Strings consist of lowercase English letters.

class PermutationInString {
public:
    static bool check_inclusion(const std::string& s1, const std::string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n1 > n2) return false;

        std::vector<int> count1(26, 0), count2(26, 0);
        for (int i = 0; i < n1; ++i) {
            count1[s1[i] - 'a']++;
            count2[s2[i] - 'a']++;
        }

        int matches = 0;
        for (int i = 0; i < 26; ++i) {
            if (count1[i] == count2[i]) matches++;
        }

        for (int i = 0; i < n2 - n1; ++i) {
            if (matches == 26) return true;

            int right = s2[i + n1] - 'a';
            int left = s2[i] - 'a';

            count2[right]++;
            if (count2[right] == count1[right]) matches++;
            else if (count2[right] == count1[right] + 1) matches--;

            count2[left]--;
            if (count2[left] == count1[left]) matches++;
            else if (count2[left] == count1[left] - 1) matches--;
        }
        return matches == 26;
    }
};

int main() {
    assert(PermutationInString::check_inclusion("ab", "eidbaooo") == true);
    assert(PermutationInString::check_inclusion("ab", "eidboaoo") == false);

    std::cout << "permutation_in_string tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_all_anagrams_in_string.cpp",
        "algorithm": "Find All Anagrams in a String",
        "purpose": "Finds all start indices of anagrams of pattern P in string S in O(|S|) time using sliding window.",
        "time_complexity": "O(|S|) time",
        "space_complexity": "O(26) space",
        "preconditions": "Strings consist of lowercase English letters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Find All Anagrams in a String
// Purpose: Finds all start indices of anagrams of pattern P in string S in O(|S|) time using sliding window.
// Time Complexity: O(|S|) time
// Space Complexity: O(26) space
// Preconditions: Strings consist of lowercase English letters.

class FindAllAnagrams {
public:
    static std::vector<int> find_anagrams(const std::string& s, const std::string& p) {
        int ns = s.size(), np = p.size();
        if (ns < np) return {};

        std::vector<int> p_count(26, 0), s_count(26, 0);
        for (int i = 0; i < np; ++i) {
            p_count[p[i] - 'a']++;
            s_count[s[i] - 'a']++;
        }

        std::vector<int> result;
        if (p_count == s_count) result.push_back(0);

        for (int i = np; i < ns; ++i) {
            s_count[s[i] - 'a']++;
            s_count[s[i - np] - 'a']--;
            if (s_count == p_count) {
                result.push_back(i - np + 1);
            }
        }
        return result;
    }
};

int main() {
    std::string s = "cbaebabacd";
    std::string p = "abc";
    auto idxs = FindAllAnagrams::find_anagrams(s, p);
    std::vector<int> expected = {0, 6};
    assert(idxs == expected);

    std::cout << "find_all_anagrams_in_string tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "max_consecutive_ones_iii.cpp",
        "algorithm": "Max Consecutive Ones III (Two Pointers)",
        "purpose": "Computes maximum consecutive 1s after flipping at most K zeros using standard two-pointer sliding window.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Binary array; K >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Max Consecutive Ones III (Two Pointers)
// Purpose: Computes maximum consecutive 1s after flipping at most K zeros using standard two-pointer sliding window.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Binary array; K >= 0.

class MaxConsecutiveOnesIII {
public:
    static int longest_ones(const std::vector<int>& nums, int k) {
        int left = 0;
        int zeros = 0;
        int max_len = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            if (nums[right] == 0) zeros++;
            while (zeros > k) {
                if (nums[left] == 0) zeros--;
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    std::vector<int> a = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    assert(MaxConsecutiveOnesIII::longest_ones(a, 2) == 6);

    std::cout << "max_consecutive_ones_iii tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "remove_duplicates_sorted_array.cpp",
        "algorithm": "Remove Duplicates from Sorted Array (In-Place)",
        "purpose": "Removes duplicate elements in-place from a sorted array such that each unique element appears once.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Remove Duplicates from Sorted Array (In-Place)
// Purpose: Removes duplicate elements in-place from a sorted array such that each unique element appears once.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class RemoveDuplicatesSorted {
public:
    static int remove_duplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        int insert_pos = 1;

        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[insert_pos++] = nums[i];
            }
        }
        return insert_pos;
    }
};

int main() {
    std::vector<int> a = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int len = RemoveDuplicatesSorted::remove_duplicates(a);
    assert(len == 5);
    for (int i = 0; i < len; ++i) {
        assert(a[i] == i);
    }

    std::cout << "remove_duplicates_sorted_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "remove_duplicates_sorted_array_ii.cpp",
        "algorithm": "Remove Duplicates from Sorted Array II (At Most Twice)",
        "purpose": "Removes duplicates in-place such that each unique element appears at most twice in O(N) time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Remove Duplicates from Sorted Array II (At Most Twice)
// Purpose: Removes duplicates in-place such that each unique element appears at most twice in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class RemoveDuplicatesAtMostTwice {
public:
    static int remove_duplicates(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;

        int insert_pos = 2;
        for (int i = 2; i < n; ++i) {
            if (nums[i] != nums[insert_pos - 2]) {
                nums[insert_pos++] = nums[i];
            }
        }
        return insert_pos;
    }
};

int main() {
    std::vector<int> a = {1, 1, 1, 2, 2, 3};
    int len = RemoveDuplicatesAtMostTwice::remove_duplicates(a);
    assert(len == 5);
    std::vector<int> expected = {1, 1, 2, 2, 3};
    for (int i = 0; i < len; ++i) {
        assert(a[i] == expected[i]);
    }

    std::cout << "remove_duplicates_sorted_array_ii tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "move_zeroes.cpp",
        "algorithm": "Move Zeroes to End",
        "purpose": "Moves all 0s to the end of the array while maintaining the relative order of the non-zero elements in O(N).",
        "time_complexity": "O(N) time with minimal writes",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Arbitrary integer array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Move Zeroes to End
// Purpose: Moves all 0s to the end of the array while maintaining the relative order of the non-zero elements in O(N).
// Time Complexity: O(N) time with minimal writes
// Space Complexity: O(1) auxiliary space
// Preconditions: Arbitrary integer array.

class MoveZeroes {
public:
    static void move_zeroes(std::vector<int>& nums) {
        int last_non_zero = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                std::swap(nums[last_non_zero++], nums[i]);
            }
        }
    }
};

int main() {
    std::vector<int> a = {0, 1, 0, 3, 12};
    MoveZeroes::move_zeroes(a);
    std::vector<int> expected = {1, 3, 12, 0, 0};
    assert(a == expected);

    std::cout << "move_zeroes tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "sort_colors.cpp",
        "algorithm": "Sort Colors (0, 1, 2 In-Place)",
        "purpose": "Sorts an array of 0s, 1s, and 2s in-place in a single pass using two pointers (Dutch National Flag).",
        "time_complexity": "O(N) time with one pass",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Elements strictly in {0, 1, 2}.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Sort Colors (0, 1, 2 In-Place)
// Purpose: Sorts an array of 0s, 1s, and 2s in-place in a single pass using two pointers (Dutch National Flag).
// Time Complexity: O(N) time with one pass
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements strictly in {0, 1, 2}.

class SortColors {
public:
    static void sort_colors(std::vector<int>& nums) {
        int low = 0, mid = 0, high = (int)nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                std::swap(nums[low++], nums[mid++]);
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                std::swap(nums[mid], nums[high--]);
            }
        }
    }
};

int main() {
    std::vector<int> a = {2, 0, 2, 1, 1, 0};
    SortColors::sort_colors(a);
    std::vector<int> expected = {0, 0, 1, 1, 2, 2};
    assert(a == expected);

    std::cout << "sort_colors tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "partition_labels.cpp",
        "algorithm": "Partition Labels",
        "purpose": "Partitions a string into as many parts as possible so that each letter appears in at most one part in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(26) space",
        "preconditions": "String of lowercase English letters.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Partition Labels
// Purpose: Partitions a string into as many parts as possible so that each letter appears in at most one part in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(26) space
// Preconditions: String of lowercase English letters.

class PartitionLabels {
public:
    static std::vector<int> partition_labels(const std::string& s) {
        std::vector<int> last(26, 0);
        for (int i = 0; i < (int)s.size(); ++i) {
            last[s[i] - 'a'] = i;
        }

        std::vector<int> partitions;
        int anchor = 0, end = 0;

        for (int i = 0; i < (int)s.size(); ++i) {
            end = std::max(end, last[s[i] - 'a']);
            if (i == end) {
                partitions.push_back(i - anchor + 1);
                anchor = i + 1;
            }
        }
        return partitions;
    }
};

int main() {
    std::string s = "ababcbacadefegdehijhklij";
    auto parts = PartitionLabels::partition_labels(s);
    std::vector<int> expected = {9, 7, 8};
    assert(parts == expected);

    std::cout << "partition_labels tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "interval_list_intersections.cpp",
        "algorithm": "Interval List Intersections",
        "purpose": "Computes the intersection of two disjoint, sorted lists of closed intervals in O(N + M) time using two pointers.",
        "time_complexity": "O(N + M) time",
        "space_complexity": "O(1) auxiliary space beyond result",
        "preconditions": "Intervals in both lists pairwise disjoint and sorted by start time.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Interval List Intersections
// Purpose: Computes the intersection of two disjoint, sorted lists of closed intervals in O(N + M) time using two pointers.
// Time Complexity: O(N + M) time
// Space Complexity: O(1) auxiliary space beyond result
// Preconditions: Intervals in both lists pairwise disjoint and sorted by start time.

class IntervalIntersections {
public:
    static std::vector<std::pair<int, int>> interval_intersection(
        const std::vector<std::pair<int, int>>& first_list,
        const std::vector<std::pair<int, int>>& second_list) {

        std::vector<std::pair<int, int>> res;
        int i = 0, j = 0;
        int n1 = first_list.size(), n2 = second_list.size();

        while (i < n1 && j < n2) {
            int start = std::max(first_list[i].first, second_list[j].first);
            int end = std::min(first_list[i].second, second_list[j].second);

            if (start <= end) {
                res.push_back({start, end});
            }

            if (first_list[i].second < second_list[j].second) {
                i++;
            } else {
                j++;
            }
        }
        return res;
    }
};

int main() {
    std::vector<std::pair<int, int>> l1 = {{0, 2}, {5, 10}, {13, 23}, {24, 25}};
    std::vector<std::pair<int, int>> l2 = {{1, 5}, {8, 12}, {15, 24}, {25, 26}};
    auto inter = IntervalIntersections::interval_intersection(l1, l2);
    std::vector<std::pair<int, int>> expected = {{1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}};
    assert(inter == expected);

    std::cout << "interval_list_intersections tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "backspace_string_compare.cpp",
        "algorithm": "Backspace String Compare (Two Pointers Reverse)",
        "purpose": "Compares two typed strings containing backspaces '#' in O(N + M) time and O(1) auxiliary space.",
        "time_complexity": "O(N + M) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Strings containing lowercase letters and '#'.",
        "code": r"""#include <iostream>
#include <string>
#include <cassert>

// Algorithm: Backspace String Compare (Two Pointers Reverse)
// Purpose: Compares two typed strings containing backspaces '#' in O(N + M) time and O(1) auxiliary space.
// Time Complexity: O(N + M) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Strings containing lowercase letters and '#'.

class BackspaceStringCompare {
private:
    static int get_next_valid_char_index(const std::string& str, int index) {
        int backspaces = 0;
        while (index >= 0) {
            if (str[index] == '#') {
                backspaces++;
            } else if (backspaces > 0) {
                backspaces--;
            } else {
                break;
            }
            index--;
        }
        return index;
    }

public:
    static bool backspace_compare(const std::string& s, const std::string& t) {
        int i = s.size() - 1;
        int j = t.size() - 1;

        while (i >= 0 || j >= 0) {
            i = get_next_valid_char_index(s, i);
            j = get_next_valid_char_index(t, j);

            if (i >= 0 && j >= 0 && s[i] != t[j]) {
                return false;
            }
            if ((i >= 0) != (j >= 0)) {
                return false;
            }
            i--;
            j--;
        }
        return true;
    }
};

int main() {
    assert(BackspaceStringCompare::backspace_compare("ab#c", "ad#c") == true);
    assert(BackspaceStringCompare::backspace_compare("ab##", "c#d#") == true);
    assert(BackspaceStringCompare::backspace_compare("a#c", "b") == false);

    std::cout << "backspace_string_compare tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "boats_to_save_people.cpp",
        "algorithm": "Boats to Save People (Two Pointers Greedy)",
        "purpose": "Finds minimum rescue boats needed where each boat carries at most 2 people and total weight <= limit.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "People weights <= limit; boat capacity = 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Boats to Save People (Two Pointers Greedy)
// Purpose: Finds minimum rescue boats needed where each boat carries at most 2 people and total weight <= limit.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: People weights <= limit; boat capacity = 2.

class BoatsToSavePeople {
public:
    static int num_rescue_boats(std::vector<int>& people, int limit) {
        std::sort(people.begin(), people.end());
        int left = 0, right = (int)people.size() - 1;
        int boats = 0;

        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                left++;
            }
            right--;
            boats++;
        }
        return boats;
    }
};

int main() {
    std::vector<int> p1 = {1, 2};
    assert(BoatsToSavePeople::num_rescue_boats(p1, 3) == 1);

    std::vector<int> p2 = {3, 2, 2, 1};
    assert(BoatsToSavePeople::num_rescue_boats(p2, 3) == 3);

    std::vector<int> p3 = {3, 5, 3, 4};
    assert(BoatsToSavePeople::num_rescue_boats(p3, 5) == 4);

    std::cout << "boats_to_save_people tests passed successfully.\n";
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
    print(f"\nBatch 3 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
