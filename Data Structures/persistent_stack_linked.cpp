// Algorithm: Persistent Stack via Linked Nodes
// Purpose: Persistent LIFO stack with O(1) time and space per push/pop preserving all versions.
// Time Complexity: O(1) push and pop
// Space Complexity: O(1) per operation
// Preconditions: Arbitrary data elements.

#include <iostream>
#include <memory>
#include <cassert>

template <typename T>
struct PersistentStack {
    struct Node {
        T val;
        std::shared_ptr<Node> next;
        Node(T v, std::shared_ptr<Node> n) : val(v), next(n) {}
    };

    std::shared_ptr<Node> top_node;
    PersistentStack(std::shared_ptr<Node> top = nullptr) : top_node(top) {}

    PersistentStack push(T val) const {
        return PersistentStack(std::make_shared<Node>(val, top_node));
    }

    PersistentStack pop() const {
        return PersistentStack(top_node ? top_node->next : nullptr);
    }

    T top() const { return top_node->val; }
    bool empty() const { return top_node == nullptr; }
};

int main() {
    PersistentStack<int> s0;
    auto s1 = s0.push(1);
    auto s2 = s1.push(2);
    auto s3 = s2.pop();

    assert(s2.top() == 2);
    assert(s3.top() == 1);
    assert(s1.top() == 1);
    return 0;
}
