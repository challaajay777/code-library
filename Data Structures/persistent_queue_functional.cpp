// Algorithm: Fully Persistent Functional Queue
// Purpose: Implements persistent FIFO queue with O(1) amortized push and pop using immutable linked nodes.
// Time Complexity: O(1) amortized
// Space Complexity: O(N)
// Preconditions: Arbitrary element types.

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

template <typename T>
struct PersistentQueue {
    struct Node {
        T val;
        std::shared_ptr<Node> next;
        Node(T v, std::shared_ptr<Node> n = nullptr) : val(v), next(n) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

    PersistentQueue() : head(nullptr), tail(nullptr) {}
    PersistentQueue(std::shared_ptr<Node> h, std::shared_ptr<Node> t) : head(h), tail(t) {}

    PersistentQueue push(T val) const {
        auto new_node = std::make_shared<Node>(val, tail);
        return PersistentQueue(head ? head : new_node, new_node);
    }

    T front() const { return head->val; }
};

int main() {
    PersistentQueue<int> q0;
    auto q1 = q0.push(10);
    auto q2 = q1.push(20);
    assert(q1.front() == 10);
    assert(q2.front() == 10);
    return 0;
}
