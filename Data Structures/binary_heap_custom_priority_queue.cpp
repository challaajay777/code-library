// Algorithm: Custom Binary Max-Heap
// Purpose: Implements binary heap with push, pop, and top using explicit sift-up and sift-down operations.
// Time Complexity: O(log N) push/pop, O(1) top
// Space Complexity: O(N)
// Preconditions: Comparable elements.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

template <typename T>
class BinaryMaxHeap {
    std::vector<T> data;

    void sift_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[p] < data[i]) {
                std::swap(data[p], data[i]);
                i = p;
            } else break;
        }
    }

    void sift_down(int i) {
        int n = data.size();
        while (2 * i + 1 < n) {
            int left = 2 * i + 1, right = 2 * i + 2;
            int largest = i;
            if (left < n && data[largest] < data[left]) largest = left;
            if (right < n && data[largest] < data[right]) largest = right;
            if (largest != i) {
                std::swap(data[i], data[largest]);
                i = largest;
            } else break;
        }
    }

public:
    void push(T val) {
        data.push_back(val);
        sift_up(data.size() - 1);
    }

    void pop() {
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) sift_down(0);
    }

    T top() const { return data[0]; }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

int main() {
    BinaryMaxHeap<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    heap.push(5);

    assert(heap.top() == 30);
    heap.pop();
    assert(heap.top() == 20);
    return 0;
}
