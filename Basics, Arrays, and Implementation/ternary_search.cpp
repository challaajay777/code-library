// Algorithm: Ternary Search
// Supports: Finding minimum/maximum of unimodal function over integer or floating-point domain
// Indexing: Continuous [low, high] or discrete integer range
// Complexity: O(log(range)) function evaluations
// Preconditions: Function f(x) is strictly unimodal (strictly decreasing then strictly increasing for min)

#include <bits/stdc++.h>
using namespace std;

// Discrete integer ternary search for minimum of unimodal f(x) on [low, high]
template <typename T, typename Func>
T ternary_search_int_min(T low, T high, Func f) {
    while (high - low >= 3) {
        T m1 = low + (high - low) / 3;
        T m2 = high - (high - low) / 3;
        if (f(m1) < f(m2)) {
            high = m2;
        } else {
            low = m1;
        }
    }
    T best_x = low;
    auto best_val = f(low);
    for (T x = low + 1; x <= high; ++x) {
        auto val = f(x);
        if (val < best_val) {
            best_val = val;
            best_x = x;
        }
    }
    return best_x;
}

// Continuous floating-point ternary search for minimum of unimodal f(x) on [low, high]
template <typename Func>
double ternary_search_float_min(double low, double high, Func f, int iterations = 100) {
    for (int iter = 0; iter < iterations; ++iter) {
        double m1 = low + (high - low) / 3.0;
        double m2 = high - (high - low) / 3.0;
        if (f(m1) < f(m2)) {
            high = m2;
        } else {
            low = m1;
        }
    }
    return (low + high) / 2.0;
}
