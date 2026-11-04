// Algorithm: Branch and Bound Exact 0/1 Knapsack
// Purpose: Finds optimal 0/1 knapsack solution pruning branches via fractional relaxation upper bound.
// Time Complexity: O(2^N) worst-case, fast on typical instances
// Space Complexity: O(N)
// Preconditions: Positive integer weights and values.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

struct Item {
    int weight, value;
    double density() const { return (double)value / weight; }
};

struct Node {
    int level, profit, weight;
    double bound;
    bool operator<(const Node& o) const { return bound < o.bound; }
};

double bound_calc(Node u, int n, int W, const std::vector<Item>& items) {
    if (u.weight >= W) return 0;
    double profit_bound = u.profit;
    int j = u.level + 1;
    int total_w = u.weight;

    while (j < n && total_w + items[j].weight <= W) {
        total_w += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }
    if (j < n) profit_bound += (W - total_w) * items[j].density();
    return profit_bound;
}

int knapsack_bnb(int W, std::vector<Item> items) {
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.density() > b.density();
    });

    int n = items.size();
    std::priority_queue<Node> q;
    Node u, v;
    u.level = -1; u.profit = u.weight = 0;
    u.bound = bound_calc(u, n, W, items);
    q.push(u);

    int max_profit = 0;

    while (!q.empty()) {
        u = q.top();
        q.pop();

        if (u.bound <= max_profit) continue;
        v.level = u.level + 1;
        if (v.level >= n) continue;

        // Take item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        if (v.weight <= W && v.profit > max_profit) max_profit = v.profit;
        v.bound = bound_calc(v, n, W, items);
        if (v.bound > max_profit) q.push(v);

        // Do not take item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound_calc(v, n, W, items);
        if (v.bound > max_profit) q.push(v);
    }
    return max_profit;
}

int main() {
    std::vector<Item> items = {{2, 40}, {3, 50}, {1, 100}, {5, 95}, {3, 30}};
    assert(knapsack_bnb(10, items) == 255);
    return 0;
}
