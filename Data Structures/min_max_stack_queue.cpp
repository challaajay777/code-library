// Algorithm: Min Stack & Min Queue
// Supports: Push, pop, top/front, get_min in O(1) time
// Indexing: Standard LIFO (stack) and FIFO (queue)
// Complexity: O(1) worst-case for MinStack, O(1) amortized for MinQueue, O(n) memory
// Preconditions: Stack/queue is non-empty when calling top/front/pop/get_min

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct MinStack {
    stack<pair<T, T>> st; // {value, current_min}

    void push(T val) {
        T new_min = st.empty() ? val : min(val, st.top().second);
        st.push({val, new_min});
    }

    void pop() {
        assert(!st.empty());
        st.pop();
    }

    T top() const {
        assert(!st.empty());
        return st.top().first;
    }

    T get_min() const {
        assert(!st.empty());
        return st.top().second;
    }

    bool empty() const { return st.empty(); }
    size_t size() const { return st.size(); }
};

template <typename T>
struct MinQueue {
    MinStack<T> in_stack, out_stack;

    void push(T val) {
        in_stack.push(val);
    }

    void pop() {
        assert(!empty());
        if (out_stack.empty()) {
            while (!in_stack.empty()) {
                out_stack.push(in_stack.top());
                in_stack.pop();
            }
        }
        out_stack.pop();
    }

    T front() {
        assert(!empty());
        if (out_stack.empty()) {
            while (!in_stack.empty()) {
                out_stack.push(in_stack.top());
                in_stack.pop();
            }
        }
        return out_stack.top();
    }

    T get_min() const {
        assert(!empty());
        if (in_stack.empty()) return out_stack.get_min();
        if (out_stack.empty()) return in_stack.get_min();
        return min(in_stack.get_min(), out_stack.get_min());
    }

    bool empty() const { return in_stack.empty() && out_stack.empty(); }
    size_t size() const { return in_stack.size() + out_stack.size(); }
};
