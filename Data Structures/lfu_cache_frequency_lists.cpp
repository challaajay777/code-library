// Algorithm: LFU Cache (Least Frequently Used O(1))
// Purpose: Maintains least frequently used items with O(1) get and put via frequency doubly-linked lists.
// Time Complexity: O(1) get and put
// Space Complexity: O(Capacity)
// Preconditions: Capacity >= 1.

#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>

class LFUCache {
    struct Node {
        int key, val, freq;
    };
    int cap, min_freq;
    std::unordered_map<int, std::list<Node>::iterator> key_map;
    std::unordered_map<int, std::list<Node>> freq_map;

public:
    LFUCache(int capacity) : cap(capacity), min_freq(0) {}

    int get(int key) {
        if (!key_map.count(key)) return -1;
        auto it = key_map[key];
        int val = it->val;
        int freq = it->freq;
        freq_map[freq].erase(it);

        if (freq_map[freq].empty() && min_freq == freq) min_freq++;

        freq_map[freq + 1].push_front({key, val, freq + 1});
        key_map[key] = freq_map[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        if (cap <= 0) return;
        if (get(key) != -1) {
            key_map[key]->val = value;
            return;
        }
        if ((int)key_map.size() >= cap) {
            auto it = freq_map[min_freq].back();
            key_map.erase(it.key);
            freq_map[min_freq].pop_back();
        }
        min_freq = 1;
        freq_map[1].push_front({key, value, 1});
        key_map[key] = freq_map[1].begin();
    }
};

int main() {
    LFUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1); // freq 1 becomes 2
    cache.put(3, 3); // evicts key 2
    assert(cache.get(2) == -1);
    assert(cache.get(3) == 3);
    return 0;
}
