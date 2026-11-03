// Algorithm: Contest Template
// Supports: Fast I/O, common type aliases, utility macros, debug print placeholders
// Complexity: O(1) setup
// Preconditions: GNU C++17 or higher

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int INF = 1e9 + 7;
const ll INF64 = 1e18 + 9;
const int MOD = 1e9 + 7; // or 998244353

void set_io(const string& name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!name.empty()) {
        (void)!freopen((name + ".in").c_str(), "r", stdin);
        (void)!freopen((name + ".out").c_str(), "w", stdout);
    }
}

void solve() {
    // Solves a single testcase
}

int main() {
    set_io();
    int t = 1;
    // if multiple test cases: cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
