// Algorithm: Misra-Gries Heavy Hitters / Boyer-Moore Majority Element
// Supports: Finding all elements appearing > n / k times in a stream with O(k) space
// Indexing: 0-based vector input
// Complexity: O(n * k) time for stream pass, O(n) verification pass, O(k) memory
// Preconditions: k >= 2

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Boyer-Moore Majority Element (k = 2, threshold > n / 2)
// Returns pair<bool, T>: {true, majority_element} if exists, {false, default} otherwise
template <typename T>
pair<bool, T> boyer_moore_majority(const vector<T>& a) {
    if (a.empty()) return {false, T()};
    T candidate = a[0];
    int count = 0;
    for (const auto& x : a) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }

    // Verification step
    int occ = 0;
    for (const auto& x : a) {
        if (x == candidate) occ++;
    }
    if (occ > (int)a.size() / 2) {
        return {true, candidate};
    }
    return {false, T()};
}

// Misra-Gries Algorithm: finds all candidates with frequency > n / k
template <typename T>
vector<T> misra_gries(const vector<T>& a, int k) {
    assert(k >= 2);
    if (a.empty()) return {};

    unordered_map<T, int> counts;
    for (const auto& x : a) {
        if (counts.count(x)) {
            counts[x]++;
        } else if ((int)counts.size() < k - 1) {
            counts[x] = 1;
        } else {
            // Decrement all active counters
            for (auto it = counts.begin(); it != counts.end(); ) {
                it->second--;
                if (it->second == 0) {
                    it = counts.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    // Exact frequency verification pass
    unordered_map<T, int> actual;
    for (const auto& x : a) {
        if (counts.count(x)) {
            actual[x]++;
        }
    }

    vector<T> result;
    int threshold = (int)a.size() / k;
    for (const auto& entry : actual) {
        if (entry.second > threshold) {
            result.push_back(entry.first);
        }
    }
    return result;
}
