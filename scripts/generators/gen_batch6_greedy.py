#!/usr/bin/env python3
"""
Batch 6 Generator: Greedy Algorithms (35 implementations)
Target Directory: Greedy Algorithms
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Greedy Algorithms"

FILES = [
    {
        "filename": "activity_selection.cpp",
        "algorithm": "Activity Selection (Interval Scheduling)",
        "purpose": "Selects maximum number of mutually non-overlapping activities by sorting by finish time in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Start and finish times valid (start <= finish).",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Activity Selection (Interval Scheduling)
// Purpose: Selects maximum number of mutually non-overlapping activities by sorting by finish time in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Start and finish times valid (start <= finish).

struct Activity {
    int start;
    int finish;
    bool operator<(const Activity& other) const {
        return finish < other.finish;
    }
};

class ActivitySelection {
public:
    static int max_activities(std::vector<Activity>& acts) {
        if (acts.empty()) return 0;
        std::sort(acts.begin(), acts.end());
        int count = 1;
        int last_finish = acts[0].finish;

        for (size_t i = 1; i < acts.size(); ++i) {
            if (acts[i].start >= last_finish) {
                count++;
                last_finish = acts[i].finish;
            }
        }
        return count;
    }
};

int main() {
    std::vector<Activity> acts = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
    assert(ActivitySelection::max_activities(acts) == 4);

    std::cout << "activity_selection tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "fractional_knapsack.cpp",
        "algorithm": "Fractional Knapsack",
        "purpose": "Maximizes total value achievable in knapsack of capacity W allowing fractional quantities of items.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Values and weights non-negative; capacity >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: Fractional Knapsack
// Purpose: Maximizes total value achievable in knapsack of capacity W allowing fractional quantities of items.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Values and weights non-negative; capacity >= 0.

struct KnapsackItem {
    double value;
    double weight;
};

class FractionalKnapsack {
public:
    static double get_max_value(double capacity, std::vector<KnapsackItem>& items) {
        std::sort(items.begin(), items.end(), [](const KnapsackItem& a, const KnapsackItem& b) {
            return (a.value / a.weight) > (b.value / b.weight);
        });

        double total_val = 0.0;
        double rem_cap = capacity;

        for (const auto& item : items) {
            if (rem_cap <= 0.0) break;
            if (item.weight <= rem_cap) {
                total_val += item.value;
                rem_cap -= item.weight;
            } else {
                total_val += item.value * (rem_cap / item.weight);
                rem_cap = 0.0;
            }
        }
        return total_val;
    }
};

int main() {
    std::vector<KnapsackItem> items = {{60, 10}, {100, 20}, {120, 30}};
    double val = FractionalKnapsack::get_max_value(50, items);
    // Takes item 1 (60), item 2 (100), and 2/3 of item 3 (80) -> 240
    assert(std::abs(val - 240.0) < 1e-6);

    std::cout << "fractional_knapsack tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "huffman_coding_tree.cpp",
        "algorithm": "Huffman Coding Tree",
        "purpose": "Constructs optimal prefix-free variable length binary codes for character frequencies using min-heap in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) tree node storage",
        "preconditions": "Frequencies positive; alphabet size N >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <cassert>

// Algorithm: Huffman Coding Tree
// Purpose: Constructs optimal prefix-free variable length binary codes for character frequencies using min-heap in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) tree node storage
// Preconditions: Frequencies positive; alphabet size N >= 1.

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r) : ch('$'), freq(f), left(l), right(r) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

class HuffmanCoding {
private:
    static void generate_codes(HuffmanNode* root, const std::string& prefix, std::map<char, std::string>& codes) {
        if (!root) return;
        if (!root->left && !root->right) {
            codes[root->ch] = prefix.empty() ? "0" : prefix;
            return;
        }
        generate_codes(root->left, prefix + "0", codes);
        generate_codes(root->right, prefix + "1", codes);
    }

    static void free_tree(HuffmanNode* root) {
        if (!root) return;
        free_tree(root->left);
        free_tree(root->right);
        delete root;
    }

public:
    static std::map<char, std::string> build_codes(const std::vector<std::pair<char, int>>& freqs) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> pq;
        for (const auto& p : freqs) {
            pq.push(new HuffmanNode(p.first, p.second));
        }

        while (pq.size() > 1) {
            HuffmanNode* l = pq.top(); pq.pop();
            HuffmanNode* r = pq.top(); pq.pop();
            HuffmanNode* parent = new HuffmanNode(l->freq + r->freq, l, r);
            pq.push(parent);
        }

        HuffmanNode* root = pq.top();
        std::map<char, std::string> codes;
        generate_codes(root, "", codes);
        free_tree(root);
        return codes;
    }
};

int main() {
    std::vector<std::pair<char, int>> freqs = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    auto codes = HuffmanCoding::build_codes(freqs);
    assert(codes.size() == 6);
    // 'f' has highest frequency, so code length must be minimal
    assert(codes['f'].size() == 1 || codes['f'].size() == 2);

    std::cout << "huffman_coding_tree tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "job_sequencing_deadline_profit.cpp",
        "algorithm": "Job Sequencing with Deadlines and Profits (DSU)",
        "purpose": "Schedules unit-time jobs to maximize total profit within deadlines in O(N log N) using Disjoint Set Union.",
        "time_complexity": "O(N log N + N * alpha(max_deadline)) time",
        "space_complexity": "O(max_deadline) space for DSU",
        "preconditions": "Deadlines >= 1; profits >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

// Algorithm: Job Sequencing with Deadlines and Profits (DSU)
// Purpose: Schedules unit-time jobs to maximize total profit within deadlines in O(N log N) using Disjoint Set Union.
// Time Complexity: O(N log N + N * alpha(max_deadline)) time
// Space Complexity: O(max_deadline) space for DSU
// Preconditions: Deadlines >= 1; profits >= 0.

struct Job {
    int id;
    int deadline;
    int profit;
};

class JobSequencingDSU {
private:
    struct DSU {
        std::vector<int> parent;
        explicit DSU(int n) : parent(n + 1) {
            std::iota(parent.begin(), parent.end(), 0);
        }
        int find(int i) {
            return parent[i] == i ? i : (parent[i] = find(parent[i]));
        }
        void unite(int u, int v) {
            parent[u] = v;
        }
    };

public:
    static std::pair<int, int> schedule(std::vector<Job>& jobs) {
        std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.profit > b.profit;
        });

        int max_deadline = 0;
        for (const auto& j : jobs) max_deadline = std::max(max_deadline, j.deadline);

        DSU dsu(max_deadline);
        int job_count = 0;
        int total_profit = 0;

        for (const auto& j : jobs) {
            int available_slot = dsu.find(j.deadline);
            if (available_slot > 0) {
                job_count++;
                total_profit += j.profit;
                dsu.unite(available_slot, dsu.find(available_slot - 1));
            }
        }
        return {job_count, total_profit};
    }
};

int main() {
    std::vector<Job> jobs = {{1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30}};
    auto [cnt, prof] = JobSequencingDSU::schedule(jobs);
    assert(cnt == 2 && prof == 60); // Job 3 (profit 40) + Job 1 (profit 20)

    std::cout << "job_sequencing_deadline_profit tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "gas_station_circular_tour.cpp",
        "algorithm": "Gas Station Circular Tour",
        "purpose": "Finds unique starting gas station index from which a car can complete a full clockwise circuit in O(N) time and O(1) space.",
        "time_complexity": "O(N) time single pass",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Non-negative gas and cost values.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Gas Station Circular Tour
// Purpose: Finds unique starting gas station index from which a car can complete a full clockwise circuit in O(N) time and O(1) space.
// Time Complexity: O(N) time single pass
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-negative gas and cost values.

class GasStationTour {
public:
    static int can_complete_circuit(const std::vector<int>& gas, const std::vector<int>& cost) {
        int total_tank = 0;
        int curr_tank = 0;
        int starting_station = 0;

        for (size_t i = 0; i < gas.size(); ++i) {
            int balance = gas[i] - cost[i];
            total_tank += balance;
            curr_tank += balance;

            if (curr_tank < 0) {
                starting_station = i + 1;
                curr_tank = 0;
            }
        }
        return total_tank >= 0 ? starting_station : -1;
    }
};

int main() {
    std::vector<int> gas = {1, 2, 3, 4, 5};
    std::vector<int> cost = {3, 4, 5, 1, 2};
    assert(GasStationTour::can_complete_circuit(gas, cost) == 3);

    std::vector<int> gas2 = {2, 3, 4};
    std::vector<int> cost2 = {3, 4, 3};
    assert(GasStationTour::can_complete_circuit(gas2, cost2) == -1);

    std::cout << "gas_station_circular_tour tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "jump_game_reachability.cpp",
        "algorithm": "Jump Game (Reachability)",
        "purpose": "Determines whether the last index of an array is reachable from index 0 in O(N) time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Elements represent maximum forward jump lengths.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Jump Game (Reachability)
// Purpose: Determines whether the last index of an array is reachable from index 0 in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements represent maximum forward jump lengths.

class JumpGameReachability {
public:
    static bool can_jump(const std::vector<int>& nums) {
        int max_reach = 0;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if (i > max_reach) return false;
            max_reach = std::max(max_reach, i + nums[i]);
            if (max_reach >= n - 1) return true;
        }
        return true;
    }
};

int main() {
    std::vector<int> a = {2, 3, 1, 1, 4};
    assert(JumpGameReachability::can_jump(a) == true);

    std::vector<int> b = {3, 2, 1, 0, 4};
    assert(JumpGameReachability::can_jump(b) == false);

    std::cout << "jump_game_reachability tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "jump_game_min_jumps.cpp",
        "algorithm": "Jump Game II (Minimum Jumps)",
        "purpose": "Finds the minimum number of jumps to reach the last index in O(N) time using BFS-like greedy frontiers.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array length >= 1; last index is reachable.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Jump Game II (Minimum Jumps)
// Purpose: Finds the minimum number of jumps to reach the last index in O(N) time using BFS-like greedy frontiers.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1; last index is reachable.

class JumpGameMinJumps {
public:
    static int jump(const std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int jumps = 0;
        int current_end = 0;
        int farthest = 0;

        for (int i = 0; i < n - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);
            if (i == current_end) {
                jumps++;
                current_end = farthest;
                if (current_end >= n - 1) break;
            }
        }
        return jumps;
    }
};

int main() {
    std::vector<int> a = {2, 3, 1, 1, 4};
    assert(JumpGameMinJumps::jump(a) == 2); // 0 -> 1 -> 4

    std::vector<int> b = {2, 3, 0, 1, 4};
    assert(JumpGameMinJumps::jump(b) == 2);

    std::cout << "jump_game_min_jumps tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "candy_distribution.cpp",
        "algorithm": "Candy Distribution Problem",
        "purpose": "Computes minimum candies required to distribute to children such that children with higher rating get more candies than neighbors.",
        "time_complexity": "O(N) time with two passes",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Non-empty ratings array.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Candy Distribution Problem
// Purpose: Computes minimum candies required to distribute to children such that children with higher rating get more candies than neighbors.
// Time Complexity: O(N) time with two passes
// Space Complexity: O(N) auxiliary space
// Preconditions: Non-empty ratings array.

class CandyDistribution {
public:
    static int candy(const std::vector<int>& ratings) {
        int n = ratings.size();
        std::vector<int> candies(n, 1);

        // Left-to-right pass
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Right-to-left pass
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }
        }

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    std::vector<int> r1 = {1, 0, 2};
    assert(CandyDistribution::candy(r1) == 5); // [2, 1, 2]

    std::vector<int> r2 = {1, 2, 2};
    assert(CandyDistribution::candy(r2) == 4); // [1, 2, 1]

    std::cout << "candy_distribution tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_platforms_trains.cpp",
        "algorithm": "Minimum Railway Platforms Required",
        "purpose": "Finds minimum number of railway platforms required given train arrival and departure times in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Arrival and departure times in consistent time units.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Railway Platforms Required
// Purpose: Finds minimum number of railway platforms required given train arrival and departure times in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Arrival and departure times in consistent time units.

class MinimumPlatforms {
public:
    static int find_platform(std::vector<int>& arr, std::vector<int>& dep) {
        int n = arr.size();
        std::sort(arr.begin(), arr.end());
        std::sort(dep.begin(), dep.end());

        int plat_needed = 1, max_plat = 1;
        int i = 1, j = 0;

        while (i < n && j < n) {
            if (arr[i] <= dep[j]) {
                plat_needed++;
                i++;
            } else {
                plat_needed--;
                j++;
            }
            max_plat = std::max(max_plat, plat_needed);
        }
        return max_plat;
    }
};

int main() {
    std::vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    std::vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    assert(MinimumPlatforms::find_platform(arr, dep) == 3);

    std::cout << "minimum_platforms_trains tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "reorganize_string_greedy.cpp",
        "algorithm": "Reorganize String (No Adjacent Identical Characters)",
        "purpose": "Rearranges characters of a string so that no two adjacent characters are identical using max-heap in O(N log Sigma).",
        "time_complexity": "O(N log 26) time",
        "space_complexity": "O(26) space",
        "preconditions": "String of lowercase English letters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "largest_number_custom_comparator.cpp",
        "algorithm": "Largest Number Concatenation",
        "purpose": "Arranges a list of non-negative integers such that their concatenation forms the largest possible number in O(N log N).",
        "time_complexity": "O(N log N * L) time where L is average number of digits",
        "space_complexity": "O(N * L) space",
        "preconditions": "Array of non-negative integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// Algorithm: Largest Number Concatenation
// Purpose: Arranges a list of non-negative integers such that their concatenation forms the largest possible number in O(N log N).
// Time Complexity: O(N log N * L) time where L is average number of digits
// Space Complexity: O(N * L) space
// Preconditions: Array of non-negative integers.

class LargestNumber {
public:
    static std::string form_largest(std::vector<int>& nums) {
        std::vector<std::string> str_nums;
        for (int x : nums) str_nums.push_back(std::to_string(x));

        std::sort(str_nums.begin(), str_nums.end(), [](const std::string& a, const std::string& b) {
            return (a + b) > (b + a);
        });

        if (str_nums[0] == "0") return "0";

        std::string result = "";
        for (const auto& s : str_nums) result += s;
        return result;
    }
};

int main() {
    std::vector<int> nums = {10, 2};
    assert(LargestNumber::form_largest(nums) == "210");

    std::vector<int> nums2 = {3, 30, 34, 5, 9};
    assert(LargestNumber::form_largest(nums2) == "9534330");

    std::cout << "largest_number_custom_comparator tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "optimal_merge_patterns.cpp",
        "algorithm": "Optimal Merge Patterns",
        "purpose": "Finds the minimum total cost to merge N files into one file using a min-heap in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space for priority queue",
        "preconditions": "File sizes are positive integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Optimal Merge Patterns
// Purpose: Finds the minimum total cost to merge N files into one file using a min-heap in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for priority queue
// Preconditions: File sizes are positive integers.

class OptimalMergePatterns {
public:
    static long long min_computation_cost(const std::vector<long long>& files) {
        if (files.size() <= 1) return 0;
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq(files.begin(), files.end());
        long long total_cost = 0;

        while (pq.size() > 1) {
            long long a = pq.top(); pq.pop();
            long long b = pq.top(); pq.pop();
            long long sum = a + b;
            total_cost += sum;
            pq.push(sum);
        }
        return total_cost;
    }
};

int main() {
    std::vector<long long> files = {2, 3, 4, 5, 6, 7};
    // Merges: 2+3=5, 4+5=9, 5+6=11, 7+9=16, 11+16=27 -> total cost = 5 + 9 + 11 + 16 + 27 = 68
    assert(OptimalMergePatterns::min_computation_cost(files) == 68);

    std::cout << "optimal_merge_patterns tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "task_scheduler_cooldown.cpp",
        "algorithm": "Task Scheduler with Cooldown",
        "purpose": "Computes the minimum total CPU intervals required to complete all tasks given a mandatory cooldown period N.",
        "time_complexity": "O(Tasks) time",
        "space_complexity": "O(26) space",
        "preconditions": "Tasks represented as uppercase characters; cooldown N >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Task Scheduler with Cooldown
// Purpose: Computes the minimum total CPU intervals required to complete all tasks given a mandatory cooldown period N.
// Time Complexity: O(Tasks) time
// Space Complexity: O(26) space
// Preconditions: Tasks represented as uppercase characters; cooldown N >= 0.

class TaskScheduler {
public:
    static int least_interval(const std::vector<char>& tasks, int n) {
        std::vector<int> counts(26, 0);
        for (char c : tasks) counts[c - 'A']++;

        int max_freq = *std::max_element(counts.begin(), counts.end());
        int max_count = 0;
        for (int f : counts) {
            if (f == max_freq) max_count++;
        }

        int empty_slots = (max_freq - 1) * (n - (max_count - 1));
        int available_tasks = tasks.size() - max_freq * max_count;
        int idles = std::max(0, empty_slots - available_tasks);

        return tasks.size() + idles;
    }
};

int main() {
    std::vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    assert(TaskScheduler::least_interval(tasks, 2) == 8); // A -> B -> idle -> A -> B -> idle -> A -> B

    assert(TaskScheduler::least_interval(tasks, 0) == 6);

    std::cout << "task_scheduler_cooldown tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "assign_cookies.cpp",
        "algorithm": "Assign Cookies (Greedy Child Satisfaction)",
        "purpose": "Maximizes the number of children whose greed factors are satisfied by available cookie sizes.",
        "time_complexity": "O(N log N + M log M) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Greed factors and cookie sizes positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Assign Cookies (Greedy Child Satisfaction)
// Purpose: Maximizes the number of children whose greed factors are satisfied by available cookie sizes.
// Time Complexity: O(N log N + M log M) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Greed factors and cookie sizes positive.

class AssignCookies {
public:
    static int find_content_children(std::vector<int>& g, std::vector<int>& s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());

        int child = 0, cookie = 0;
        while (child < (int)g.size() && cookie < (int)s.size()) {
            if (s[cookie] >= g[child]) {
                child++;
            }
            cookie++;
        }
        return child;
    }
};

int main() {
    std::vector<int> g = {1, 2, 3};
    std::vector<int> s = {1, 1};
    assert(AssignCookies::find_content_children(g, s) == 1);

    std::vector<int> g2 = {1, 2};
    std::vector<int> s2 = {1, 2, 3};
    assert(AssignCookies::find_content_children(g2, s2) == 2);

    std::cout << "assign_cookies tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "lemonade_change.cpp",
        "algorithm": "Lemonade Change",
        "purpose": "Determines whether correct change ($5, $10) can be provided to every customer paying with $5, $10, or $20.",
        "time_complexity": "O(N) time single pass",
        "space_complexity": "O(1) space",
        "preconditions": "Bills in {5, 10, 20}.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Lemonade Change
// Purpose: Determines whether correct change ($5, $10) can be provided to every customer paying with $5, $10, or $20.
// Time Complexity: O(N) time single pass
// Space Complexity: O(1) space
// Preconditions: Bills in {5, 10, 20}.

class LemonadeChange {
public:
    static bool lemonade_change(const std::vector<int>& bills) {
        int five = 0, ten = 0;

        for (int bill : bills) {
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            } else { // bill == 20
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    assert(LemonadeChange::lemonade_change({5, 5, 5, 10, 20}) == true);
    assert(LemonadeChange::lemonade_change({5, 5, 10, 10, 20}) == false);

    std::cout << "lemonade_change tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_arrows_burst_balloons.cpp",
        "algorithm": "Minimum Arrows to Burst Balloons (Interval Covering)",
        "purpose": "Finds minimum number of vertical arrows required to shoot all horizontal balloon intervals in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Points formatted as [start, end] with start <= end.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Arrows to Burst Balloons (Interval Covering)
// Purpose: Finds minimum number of vertical arrows required to shoot all horizontal balloon intervals in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Points formatted as [start, end] with start <= end.

class MinimumArrowsBurstBalloons {
public:
    static int find_min_arrow_shots(std::vector<std::pair<int, int>>& points) {
        if (points.empty()) return 0;
        std::sort(points.begin(), points.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });

        int arrows = 1;
        int end = points[0].second;

        for (size_t i = 1; i < points.size(); ++i) {
            if (points[i].first > end) {
                arrows++;
                end = points[i].second;
            }
        }
        return arrows;
    }
};

int main() {
    std::vector<std::pair<int, int>> p = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    assert(MinimumArrowsBurstBalloons::find_min_arrow_shots(p) == 2);

    std::cout << "minimum_arrows_burst_balloons tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "non_overlapping_intervals_erase.cpp",
        "algorithm": "Non-Overlapping Intervals (Minimum Removals)",
        "purpose": "Finds minimum number of intervals to remove to make the remainder non-overlapping in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Intervals valid (start <= end).",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Non-Overlapping Intervals (Minimum Removals)
// Purpose: Finds minimum number of intervals to remove to make the remainder non-overlapping in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Intervals valid (start <= end).

class NonOverlappingIntervals {
public:
    static int erase_overlap_intervals(std::vector<std::pair<int, int>>& intervals) {
        if (intervals.empty()) return 0;
        std::sort(intervals.begin(), intervals.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });

        int non_overlap = 1;
        int last_end = intervals[0].second;

        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i].first >= last_end) {
                non_overlap++;
                last_end = intervals[i].second;
            }
        }
        return intervals.size() - non_overlap;
    }
};

int main() {
    std::vector<std::pair<int, int>> invs = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    assert(NonOverlappingIntervals::erase_overlap_intervals(invs) == 1);

    std::vector<std::pair<int, int>> invs2 = {{1, 2}, {1, 2}, {1, 2}};
    assert(NonOverlappingIntervals::erase_overlap_intervals(invs2) == 2);

    std::cout << "non_overlapping_intervals_erase tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "queue_reconstruction_by_height.cpp",
        "algorithm": "Queue Reconstruction by Height",
        "purpose": "Reconstructs queue of people [h, k] where h is height and k is number of people taller or equal in front in O(N^2).",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(N) space",
        "preconditions": "Valid people descriptions with h >= 0, k >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Queue Reconstruction by Height
// Purpose: Reconstructs queue of people [h, k] where h is height and k is number of people taller or equal in front in O(N^2).
// Time Complexity: O(N^2) time
// Space Complexity: O(N) space
// Preconditions: Valid people descriptions with h >= 0, k >= 0.

class QueueReconstruction {
public:
    static std::vector<std::pair<int, int>> reconstruct_queue(std::vector<std::pair<int, int>>& people) {
        // Sort descending by height; if equal height, sort ascending by k
        std::sort(people.begin(), people.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });

        std::vector<std::pair<int, int>> queue;
        for (const auto& p : people) {
            queue.insert(queue.begin() + p.second, p);
        }
        return queue;
    }
};

int main() {
    std::vector<std::pair<int, int>> people = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
    auto res = QueueReconstruction::reconstruct_queue(people);
    std::vector<std::pair<int, int>> expected = {{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}};
    assert(res == expected);

    std::cout << "queue_reconstruction_by_height tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_cost_ropes_connect.cpp",
        "algorithm": "Minimum Cost of Connecting Ropes",
        "purpose": "Finds minimum cost to connect N ropes where the cost of connecting two ropes is the sum of their lengths in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space for min-heap",
        "preconditions": "Rope lengths positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Minimum Cost of Connecting Ropes
// Purpose: Finds minimum cost to connect N ropes where the cost of connecting two ropes is the sum of their lengths in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for min-heap
// Preconditions: Rope lengths positive.

class ConnectRopesMinCost {
public:
    static long long min_cost(const std::vector<long long>& ropes) {
        if (ropes.size() <= 1) return 0;
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq(ropes.begin(), ropes.end());
        long long total = 0;

        while (pq.size() > 1) {
            long long a = pq.top(); pq.pop();
            long long b = pq.top(); pq.pop();
            long long cost = a + b;
            total += cost;
            pq.push(cost);
        }
        return total;
    }
};

int main() {
    std::vector<long long> r = {4, 3, 2, 6};
    // 2+3=5 (cost 5), 4+5=9 (cost 9), 6+9=15 (cost 15) -> total = 29
    assert(ConnectRopesMinCost::min_cost(r) == 29);

    std::cout << "minimum_cost_ropes_connect tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "maximum_units_on_truck.cpp",
        "algorithm": "Maximum Units on a Truck",
        "purpose": "Maximizes total units loaded onto a truck of box capacity B in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Box types formatted as [number_of_boxes, units_per_box].",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum Units on a Truck
// Purpose: Maximizes total units loaded onto a truck of box capacity B in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Box types formatted as [number_of_boxes, units_per_box].

class MaximumUnitsOnTruck {
public:
    static int maximum_units(std::vector<std::pair<int, int>>& box_types, int truck_size) {
        std::sort(box_types.begin(), box_types.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        });

        int units = 0;
        for (const auto& b : box_types) {
            int take = std::min(truck_size, b.first);
            units += take * b.second;
            truck_size -= take;
            if (truck_size == 0) break;
        }
        return units;
    }
};

int main() {
    std::vector<std::pair<int, int>> boxes = {{1, 3}, {2, 2}, {3, 1}};
    assert(MaximumUnitsOnTruck::maximum_units(boxes, 4) == 8);

    std::cout << "maximum_units_on_truck tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_operations_reduce_x_to_zero.cpp",
        "algorithm": "Minimum Operations to Reduce X to Zero",
        "purpose": "Finds minimum operations to reduce X to 0 by removing leftmost or rightmost elements via max subarray sum in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "All elements positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Operations to Reduce X to Zero
// Purpose: Finds minimum operations to reduce X to 0 by removing leftmost or rightmost elements via max subarray sum in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements positive.

class ReduceXToZero {
public:
    static int min_operations(const std::vector<int>& nums, int x) {
        long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
        long long target = total - x;
        if (target < 0) return -1;
        if (target == 0) return nums.size();

        int max_len = -1;
        long long cur_sum = 0;
        int left = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            cur_sum += nums[right];
            while (cur_sum > target && left <= right) {
                cur_sum -= nums[left++];
            }
            if (cur_sum == target) {
                max_len = std::max(max_len, right - left + 1);
            }
        }
        return max_len == -1 ? -1 : (int)nums.size() - max_len;
    }
};

int main() {
    std::vector<int> a = {1, 1, 4, 2, 3};
    assert(ReduceXToZero::min_operations(a, 5) == 2); // 2 and 3 from right

    std::vector<int> b = {5, 6, 7, 8, 9};
    assert(ReduceXToZero::min_operations(b, 4) == -1);

    std::cout << "minimum_operations_reduce_x_to_zero tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "patching_array.cpp",
        "algorithm": "Patching Array (Greedy Range Expansion)",
        "purpose": "Finds minimum number of patches added to sorted array nums so that any number in [1, N] can be formed by subset sum.",
        "time_complexity": "O(M + log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Nums sorted in non-decreasing order.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Patching Array (Greedy Range Expansion)
// Purpose: Finds minimum number of patches added to sorted array nums so that any number in [1, N] can be formed by subset sum.
// Time Complexity: O(M + log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Nums sorted in non-decreasing order.

class PatchingArray {
public:
    static int min_patches(const std::vector<int>& nums, long long n) {
        long long miss = 1;
        int patches = 0;
        size_t i = 0;

        while (miss <= n) {
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i++];
            } else {
                miss += miss;
                patches++;
            }
        }
        return patches;
    }
};

int main() {
    std::vector<int> nums = {1, 3};
    assert(PatchingArray::min_patches(nums, 6) == 1); // add 2 -> miss becomes 7

    std::vector<int> nums2 = {1, 5, 10};
    assert(PatchingArray::min_patches(nums2, 20) == 2);

    std::cout << "patching_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "split_array_consecutive_subsequences.cpp",
        "algorithm": "Split Array into Consecutive Subsequences",
        "purpose": "Determines if sorted array can be partitioned into consecutive subsequences of length 3 or more in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space for frequency hash tables",
        "preconditions": "Array sorted in non-decreasing order.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Split Array into Consecutive Subsequences
// Purpose: Determines if sorted array can be partitioned into consecutive subsequences of length 3 or more in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space for frequency hash tables
// Preconditions: Array sorted in non-decreasing order.

class SplitConsecutiveSubsequences {
public:
    static bool is_possible(const std::vector<int>& nums) {
        std::unordered_map<int, int> count, need;
        for (int x : nums) count[x]++;

        for (int x : nums) {
            if (count[x] == 0) continue;
            count[x]--;

            if (need[x] > 0) {
                need[x]--;
                need[x + 1]++;
            } else if (count[x + 1] > 0 && count[x + 2] > 0) {
                count[x + 1]--;
                count[x + 2]--;
                need[x + 3]++;
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 3, 4, 5};
    assert(SplitConsecutiveSubsequences::is_possible(a) == true);

    std::vector<int> b = {1, 2, 3, 4, 4, 5};
    assert(SplitConsecutiveSubsequences::is_possible(b) == false);

    std::cout << "split_array_consecutive_subsequences tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "monotone_increasing_digits.cpp",
        "algorithm": "Monotone Increasing Digits",
        "purpose": "Finds the largest integer less than or equal to N with monotone non-decreasing digits in O(digits) time.",
        "time_complexity": "O(digits) time",
        "space_complexity": "O(digits) space",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <string>
#include <cassert>

// Algorithm: Monotone Increasing Digits
// Purpose: Finds the largest integer less than or equal to N with monotone non-decreasing digits in O(digits) time.
// Time Complexity: O(digits) time
// Space Complexity: O(digits) space
// Preconditions: N >= 0.

class MonotoneIncreasingDigits {
public:
    static int monotone_digits(int n) {
        std::string s = std::to_string(n);
        int marker = s.size();

        for (int i = (int)s.size() - 1; i > 0; --i) {
            if (s[i - 1] > s[i]) {
                marker = i;
                s[i - 1]--;
            }
        }

        for (size_t i = marker; i < s.size(); ++i) {
            s[i] = '9';
        }
        return std::stoi(s);
    }
};

int main() {
    assert(MonotoneIncreasingDigits::monotone_digits(10) == 9);
    assert(MonotoneIncreasingDigits::monotone_digits(1234) == 1234);
    assert(MonotoneIncreasingDigits::monotone_digits(332) == 299);

    std::cout << "monotone_increasing_digits tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "dijkstra_greedy_tree.cpp",
        "algorithm": "Greedy Maximum Bottleneck Path",
        "purpose": "Finds path between source and target that maximizes the minimum edge capacity (widest path) using modified Dijkstra in O(M log N).",
        "time_complexity": "O(M log N) time",
        "space_complexity": "O(N + M) space",
        "preconditions": "Edge capacities non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

// Algorithm: Greedy Maximum Bottleneck Path
// Purpose: Finds path between source and target that maximizes the minimum edge capacity (widest path) using modified Dijkstra in O(M log N).
// Time Complexity: O(M log N) time
// Space Complexity: O(N + M) space
// Preconditions: Edge capacities non-negative.

struct BottleneckEdge {
    int to;
    long long cap;
};

class WidestPathDijkstra {
public:
    static long long max_bottleneck(int n, const std::vector<std::vector<BottleneckEdge>>& adj, int s, int t) {
        std::vector<long long> max_cap(n, 0);
        max_cap[s] = 2e18;

        std::priority_queue<std::pair<long long, int>> pq;
        pq.push({max_cap[s], s});

        while (!pq.empty()) {
            auto [cap, u] = pq.top(); pq.pop();
            if (cap < max_cap[u]) continue;
            if (u == t) return cap;

            for (const auto& edge : adj[u]) {
                long long bottleneck = std::min(cap, edge.cap);
                if (bottleneck > max_cap[edge.to]) {
                    max_cap[edge.to] = bottleneck;
                    pq.push({bottleneck, edge.to});
                }
            }
        }
        return max_cap[t];
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<BottleneckEdge>> adj(n);
    adj[0].push_back({1, 10});
    adj[1].push_back({3, 10});
    adj[0].push_back({2, 5});
    adj[2].push_back({3, 100});

    // Path 0->1->3 has bottleneck 10; Path 0->2->3 has bottleneck 5. Max bottleneck = 10
    assert(WidestPathDijkstra::max_bottleneck(n, adj, 0, 3) == 10);

    std::cout << "dijkstra_greedy_tree tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "egyptian_fraction.cpp",
        "algorithm": "Egyptian Fraction (Greedy Algorithm)",
        "purpose": "Represents any positive rational fraction P/Q as a sum of distinct unit fractions 1/d in greedy fashion.",
        "time_complexity": "O(terms) steps",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "1 <= P < Q.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Egyptian Fraction (Greedy Algorithm)
// Purpose: Represents any positive rational fraction P/Q as a sum of distinct unit fractions 1/d in greedy fashion.
// Time Complexity: O(terms) steps
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= P < Q.

class EgyptianFraction {
public:
    static std::vector<long long> get_unit_denominators(long long p, long long q) {
        assert(p > 0 && q > 0);
        std::vector<long long> denominators;

        while (p != 0) {
            long long d = (q + p - 1) / p; // ceil(q / p)
            denominators.push_back(d);

            p = p * d - q;
            q = q * d;
            long long g = std::gcd(p, q);
            p /= g;
            q /= g;
        }
        return denominators;
    }
};

int main() {
    auto denoms = EgyptianFraction::get_unit_denominators(2, 3);
    // 2/3 = 1/2 + 1/6
    assert(denoms.size() == 2);
    assert(denoms[0] == 2 && denoms[1] == 6);

    std::cout << "egyptian_fraction tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kth_largest_element_stream.cpp",
        "algorithm": "K-th Largest Element in a Stream",
        "purpose": "Maintains the k-th largest element seen so far in a continuous stream of numbers using a min-heap in O(log K).",
        "time_complexity": "O(log K) per added element",
        "space_complexity": "O(K) space",
        "preconditions": "K >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: K-th Largest Element in a Stream
// Purpose: Maintains the k-th largest element seen so far in a continuous stream of numbers using a min-heap in O(log K).
// Time Complexity: O(log K) per added element
// Space Complexity: O(K) space
// Preconditions: K >= 1.

class KthLargestStream {
private:
    int k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

public:
    KthLargestStream(int k_val, const std::vector<int>& nums) : k(k_val) {
        for (int x : nums) {
            add(x);
        }
    }

    int add(int val) {
        if ((int)min_heap.size() < k) {
            min_heap.push(val);
        } else if (val > min_heap.top()) {
            min_heap.pop();
            min_heap.push(val);
        }
        return min_heap.top();
    }
};

int main() {
    KthLargestStream stream(3, {4, 5, 8, 2});
    assert(stream.add(3) == 4);
    assert(stream.add(5) == 5);
    assert(stream.add(10) == 5);
    assert(stream.add(9) == 8);
    assert(stream.add(4) == 8);

    std::cout << "kth_largest_element_stream tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_number_of_refueling_stops.cpp",
        "algorithm": "Minimum Refueling Stops",
        "purpose": "Finds minimum fuel stops to reach target distance using greedy max-heap choice of passed fuel stations.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space for priority queue",
        "preconditions": "Stations sorted by position; start_fuel >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Minimum Refueling Stops
// Purpose: Finds minimum fuel stops to reach target distance using greedy max-heap choice of passed fuel stations.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for priority queue
// Preconditions: Stations sorted by position; start_fuel >= 0.

class MinRefuelingStops {
public:
    static int min_refuel_stops(int target, int start_fuel, const std::vector<std::vector<int>>& stations) {
        std::priority_queue<int> max_heap;
        long long cur_fuel = start_fuel;
        int stops = 0;
        size_t i = 0;

        while (cur_fuel < target) {
            while (i < stations.size() && stations[i][0] <= cur_fuel) {
                max_heap.push(stations[i][1]);
                i++;
            }
            if (max_heap.empty()) return -1;
            cur_fuel += max_heap.top();
            max_heap.pop();
            stops++;
        }
        return stops;
    }
};

int main() {
    std::vector<std::vector<int>> stations = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    assert(MinRefuelingStops::min_refuel_stops(100, 10, stations) == 2);

    assert(MinRefuelingStops::min_refuel_stops(100, 1, {}) == -1);

    std::cout << "minimum_number_of_refueling_stops tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "two_city_scheduling.cpp",
        "algorithm": "Two City Scheduling",
        "purpose": "Finds minimum travel cost to send exactly N people to city A and N to city B in O(2N log 2N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Costs vector has even length 2*N.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Two City Scheduling
// Purpose: Finds minimum travel cost to send exactly N people to city A and N to city B in O(2N log 2N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Costs vector has even length 2*N.

class TwoCityScheduling {
public:
    static int two_city_sched_cost(std::vector<std::vector<int>>& costs) {
        // Sort by the refund / gain of sending to city A vs B (costA - costB)
        std::sort(costs.begin(), costs.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return (a[0] - a[1]) < (b[0] - b[1]);
        });

        int total = 0;
        int n = costs.size() / 2;
        for (int i = 0; i < n; ++i) {
            total += costs[i][0]; // Send first n to city A
        }
        for (int i = n; i < 2 * n; ++i) {
            total += costs[i][1]; // Send remaining n to city B
        }
        return total;
    }
};

int main() {
    std::vector<std::vector<int>> costs = {{10, 20}, {30, 200}, {400, 50}, {30, 20}};
    assert(TwoCityScheduling::two_city_sched_cost(costs) == 110);

    std::cout << "two_city_scheduling tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "remove_k_digits_smallest_number.cpp",
        "algorithm": "Remove K Digits (Smallest Number Monotonic Stack)",
        "purpose": "Removes K digits from number string to form the smallest possible numerical value in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "String num contains digits; 0 <= K <= |num|.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Remove K Digits (Smallest Number Monotonic Stack)
// Purpose: Removes K digits from number string to form the smallest possible numerical value in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: String num contains digits; 0 <= K <= |num|.

class RemoveKDigits {
public:
    static std::string remove_kdigits(const std::string& num, int k) {
        std::string st = "";
        for (char c : num) {
            while (!st.empty() && k > 0 && st.back() > c) {
                st.pop_back();
                k--;
            }
            st.push_back(c);
        }

        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }

        // Strip leading zeros
        size_t start = 0;
        while (start < st.size() && st[start] == '0') {
            start++;
        }
        std::string res = st.substr(start);
        return res.empty() ? "0" : res;
    }
};

int main() {
    assert(RemoveKDigits::remove_kdigits("1432219", 3) == "1219");
    assert(RemoveKDigits::remove_kdigits("10200", 1) == "200");
    assert(RemoveKDigits::remove_kdigits("10", 2) == "0");

    std::cout << "remove_k_digits_smallest_number tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "create_maximum_number.cpp",
        "algorithm": "Create Maximum Number",
        "purpose": "Creates the maximum number of length K from two digit arrays maintaining relative order within each in O((N+M)^3).",
        "time_complexity": "O(K * (N + M)^2) time",
        "space_complexity": "O(K) auxiliary space",
        "preconditions": "0 <= K <= N + M.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Create Maximum Number
// Purpose: Creates the maximum number of length K from two digit arrays maintaining relative order within each in O((N+M)^3).
// Time Complexity: O(K * (N + M)^2) time
// Space Complexity: O(K) auxiliary space
// Preconditions: 0 <= K <= N + M.

class CreateMaxNumber {
private:
    static std::vector<int> max_subsequence(const std::vector<int>& nums, int k) {
        std::vector<int> res;
        int drop = nums.size() - k;
        for (int x : nums) {
            while (!res.empty() && drop > 0 && res.back() < x) {
                res.pop_back();
                drop--;
            }
            res.push_back(x);
        }
        res.resize(k);
        return res;
    }

    static std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> res;
        auto it1 = a.begin(), it2 = b.begin();
        while (it1 != a.end() || it2 != b.end()) {
            if (std::lexicographical_compare(it1, a.end(), it2, b.end())) {
                res.push_back(*it2++);
            } else {
                res.push_back(*it1++);
            }
        }
        return res;
    }

public:
    static std::vector<int> max_number(const std::vector<int>& nums1, const std::vector<int>& nums2, int k) {
        std::vector<int> best;
        int n1 = nums1.size(), n2 = nums2.size();

        for (int i = std::max(0, k - n2); i <= std::min(k, n1); ++i) {
            auto s1 = max_subsequence(nums1, i);
            auto s2 = max_subsequence(nums2, k - i);
            auto candidate = merge(s1, s2);
            if (candidate > best) {
                best = candidate;
            }
        }
        return best;
    }
};

int main() {
    std::vector<int> n1 = {3, 4, 6, 5};
    std::vector<int> n2 = {9, 1, 2, 5, 8, 3};
    auto max_num = CreateMaxNumber::max_number(n1, n2, 5);
    std::vector<int> expected = {9, 8, 6, 5, 3};
    assert(max_num == expected);

    std::cout << "create_maximum_number tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "course_schedule_iii.cpp",
        "algorithm": "Course Schedule III (Max Courses via Max-Heap)",
        "purpose": "Finds the maximum number of courses that can be completed given [duration, lastDay] for each course in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space for max-heap",
        "preconditions": "Course durations and deadlines positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

// Algorithm: Course Schedule III (Max Courses via Max-Heap)
// Purpose: Finds the maximum number of courses that can be completed given [duration, lastDay] for each course in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for max-heap
// Preconditions: Course durations and deadlines positive.

class CourseScheduleIII {
public:
    static int schedule_course(std::vector<std::vector<int>>& courses) {
        std::sort(courses.begin(), courses.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] < b[1];
        });

        std::priority_queue<int> max_heap;
        int current_time = 0;

        for (const auto& c : courses) {
            int duration = c[0];
            int last_day = c[1];

            if (current_time + duration <= last_day) {
                current_time += duration;
                max_heap.push(duration);
            } else if (!max_heap.empty() && max_heap.top() > duration) {
                current_time -= max_heap.top();
                max_heap.pop();
                current_time += duration;
                max_heap.push(duration);
            }
        }
        return max_heap.size();
    }
};

int main() {
    std::vector<std::vector<int>> c = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    assert(CourseScheduleIII::schedule_course(c) == 3);

    std::cout << "course_schedule_iii tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "furthest_building_ladders_bricks.cpp",
        "algorithm": "Furthest Building Reachable",
        "purpose": "Finds the furthest building index reachable using available bricks and ladders greedily using a min-heap in O(N log K).",
        "time_complexity": "O(N log ladders) time",
        "space_complexity": "O(ladders) space",
        "preconditions": "Heights non-negative; bricks >= 0, ladders >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Furthest Building Reachable
// Purpose: Finds the furthest building index reachable using available bricks and ladders greedily using a min-heap in O(N log K).
// Time Complexity: O(N log ladders) time
// Space Complexity: O(ladders) space
// Preconditions: Heights non-negative; bricks >= 0, ladders >= 0.

class FurthestBuilding {
public:
    static int furthest_building(const std::vector<int>& heights, int bricks, int ladders) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        for (size_t i = 0; i + 1 < heights.size(); ++i) {
            int diff = heights[i + 1] - heights[i];
            if (diff > 0) {
                min_heap.push(diff);
                if ((int)min_heap.size() > ladders) {
                    bricks -= min_heap.top();
                    min_heap.pop();
                    if (bricks < 0) return i;
                }
            }
        }
        return heights.size() - 1;
    }
};

int main() {
    std::vector<int> h = {4, 2, 7, 6, 9, 14, 12};
    assert(FurthestBuilding::furthest_building(h, 5, 1) == 4);

    std::cout << "furthest_building_ladders_bricks tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "ipo_maximize_capital.cpp",
        "algorithm": "IPO (Maximize Capital with K Projects)",
        "purpose": "Maximizes capital after selecting up to K distinct investment projects using min-heap for capital and max-heap for profit.",
        "time_complexity": "O(N log N + K log N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Profits and capital requirements non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

// Algorithm: IPO (Maximize Capital with K Projects)
// Purpose: Maximizes capital after selecting up to K distinct investment projects using min-heap for capital and max-heap for profit.
// Time Complexity: O(N log N + K log N) time
// Space Complexity: O(N) space
// Preconditions: Profits and capital requirements non-negative.

class IPOCapitalMaximizer {
public:
    static int find_maximized_capital(int k, int w, const std::vector<int>& profits, const std::vector<int>& capital) {
        int n = profits.size();
        std::vector<std::pair<int, int>> projects(n);
        for (int i = 0; i < n; ++i) {
            projects[i] = {capital[i], profits[i]};
        }
        std::sort(projects.begin(), projects.end());

        std::priority_queue<int> max_profits;
        int idx = 0;

        for (int step = 0; step < k; ++step) {
            while (idx < n && projects[idx].first <= w) {
                max_profits.push(projects[idx].second);
                idx++;
            }
            if (max_profits.empty()) break;
            w += max_profits.top();
            max_profits.pop();
        }
        return w;
    }
};

int main() {
    std::vector<int> prof = {1, 2, 3};
    std::vector<int> cap = {0, 1, 1};
    assert(IPOCapitalMaximizer::find_maximized_capital(2, 0, prof, cap) == 4);

    std::cout << "ipo_maximize_capital tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "maximum_swap_largest_number.cpp",
        "algorithm": "Maximum Swap (Largest Number Single Swap)",
        "purpose": "Finds the maximum integer achievable by swapping two digits at most once in O(digits) time.",
        "time_complexity": "O(digits) time",
        "space_complexity": "O(1) space",
        "preconditions": "Integer num >= 0.",
        "code": r"""#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum Swap (Largest Number Single Swap)
// Purpose: Finds the maximum integer achievable by swapping two digits at most once in O(digits) time.
// Time Complexity: O(digits) time
// Space Complexity: O(1) space
// Preconditions: Integer num >= 0.

class MaximumSwap {
public:
    static int maximum_swap(int num) {
        std::string s = std::to_string(num);
        std::vector<int> last(10, -1);
        for (int i = 0; i < (int)s.size(); ++i) {
            last[s[i] - '0'] = i;
        }

        for (int i = 0; i < (int)s.size(); ++i) {
            for (int d = 9; d > s[i] - '0'; --d) {
                if (last[d] > i) {
                    std::swap(s[i], s[last[d]]);
                    return std::stoi(s);
                }
            }
        }
        return num;
    }
};

int main() {
    assert(MaximumSwap::maximum_swap(2736) == 7236);
    assert(MaximumSwap::maximum_swap(9973) == 9973);

    std::cout << "maximum_swap_largest_number tests passed successfully.\n";
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
    print(f"\nBatch 6 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
