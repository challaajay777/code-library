// Algorithm: LRU Cache (Hash Map + Doubly Linked List)
// Purpose: Least Recently Used cache supporting O(1) get and put eviction operations.
// Time Complexity: O(1) get and put
// Space Complexity: O(Capacity)
// Preconditions: Capacity >= 1.

#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>

class LRUCache {
    int cap;
    std::list<std::pair<int, int>> dll;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (!map.count(key)) return -1;
        dll.splice(dll.begin(), dll, map[key]);
        return map[key]->second;
    }

    void put(int key, int value) {
        if (map.count(key)) {
            dll.splice(dll.begin(), dll, map[key]);
            map[key]->second = value;
            return;
        }
        if ((int)dll.size() == cap) {
            int old_key = dll.back().first;
            dll.pop_back();
            map.erase(old_key);
        }
        dll.emplace_front(key, value);
        map[key] = dll.begin();
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1);
    cache.put(3, 3); // evicts key 2
    assert(cache.get(2) == -1);
    return 0;
}
