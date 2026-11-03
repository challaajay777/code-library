// Algorithm: Sliding Window Minimum / Maximum (Monotone Deque)
// Supports: Querying min/max over sliding window of fixed length k
// Indexing: 0-based array indices
// Complexity: O(n) total time (each index pushed and popped at most once), O(k) memory
// Preconditions: 1 <= k <= n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
vector<T> sliding_window_minimum(const vector<T>& a, int k) {
    int n = (int)a.size();
    assert(1 <= k && k <= n);
    deque<int> dq; // stores indices, maintains increasing values of a[idx]
    vector<T> res;
    res.reserve(n - k + 1);

    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && a[dq.back()] >= a[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            res.push_back(a[dq.front()]);
        }
    }
    return res;
}

template <typename T>
vector<T> sliding_window_maximum(const vector<T>& a, int k) {
    int n = (int)a.size();
    assert(1 <= k && k <= n);
    deque<int> dq; // stores indices, maintains decreasing values of a[idx]
    vector<T> res;
    res.reserve(n - k + 1);

    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && a[dq.back()] <= a[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            res.push_back(a[dq.front()]);
        }
    }
    return res;
}
