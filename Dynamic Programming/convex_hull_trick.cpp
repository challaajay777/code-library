// Algorithm: Convex Hull Trick (Dynamic Line Container)
// Supports: Adding lines y = k*x + m, querying max(k*x + m) for arbitrary x
// Indexing: Continuous line equations
// Complexity: O(log n) amortized per line insertion, O(log n) per query, O(n) memory
// Preconditions: For minimum query, insert lines (-k, -m) and negate query result

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Line {
    mutable long long k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(long long x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // Computes floor(a / b) for integers
    static constexpr long long INF_COORD = 1e18;

    long long div_floor(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    // Updates x-intersection point between x and y
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = INF_COORD;
            return false;
        }
        if (x->k == y->k) {
            x->p = (x->m > y->m ? INF_COORD : -INF_COORD);
        } else {
            x->p = div_floor(y->m - x->m, x->k - y->k);
        }
        return x->p >= y->p;
    }

    // Inserts line y = k*x + m
    void add_line(long long k, long long m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }

    // Queries maximum value of k*x + m at x
    long long query_max(long long x) const {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
