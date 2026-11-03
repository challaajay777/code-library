// Algorithm: Binary Search Utilities
// Supports: First-true predicate search, last-true predicate search, safe integer square root
// Indexing: Inclusive interval [low, high]
// Complexity: O(log(high - low)) predicate evaluations
// Preconditions: Predicate is monotonic over [low, high]

#include <bits/stdc++.h>
using namespace std;

// Finds the smallest x in [low, high] such that pred(x) is true.
// Assumes pred is false then true (0 0 ... 0 1 1 ... 1).
// Returns high + 1 if no element satisfies pred.
template <typename T, typename Pred>
T first_true(T low, T high, Pred pred) {
    T ans = high + 1;
    while (low <= high) {
        T mid = low + (high - low) / 2;
        if (pred(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

// Finds the largest x in [low, high] such that pred(x) is true.
// Assumes pred is true then false (1 1 ... 1 0 0 ... 0).
// Returns low - 1 if no element satisfies pred.
template <typename T, typename Pred>
T last_true(T low, T high, Pred pred) {
    T ans = low - 1;
    while (low <= high) {
        T mid = low + (high - low) / 2;
        if (pred(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// Computes floor(sqrt(n)) using binary search with no floating point inaccuracies
unsigned long long integer_sqrt(unsigned long long n) {
    unsigned long long low = 0, high = 3037000499ULL; // ~ 3 * 10^9, since high*high <= 2^64-1
    if (high > n) high = n;
    return last_true(low, high, [&](unsigned long long x) {
        return x * x <= n;
    });
}
