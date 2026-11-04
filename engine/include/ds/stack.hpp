#ifndef ACADPULSE_STACK_HPP
#define ACADPULSE_STACK_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "ds/linked_lists.hpp"

namespace dsa {

/**
 * Array-based Stack ADT.
 * Covers Syllabus: Unit 3 (Stack: representation and implementation using array)
 * Time Complexity: O(1) push, pop, top
 */
template <typename T>
class ArrayStack {
private:
    Vector<T> data_;

public:
    ArrayStack() {}

    void push(const T& val) {
        data_.push_back(val);
    }

    void push(T&& val) {
        data_.push_back(static_cast<T&&>(val));
    }

    bool pop(T& out_val) {
        if (data_.empty()) return false;
        out_val = data_.back();
        data_.pop_back();
        return true;
    }

    bool top(T& out_val) const {
        if (data_.empty()) return false;
        out_val = data_.back();
        return true;
    }

    std::size_t size() const noexcept { return data_.size(); }
    bool empty() const noexcept { return data_.empty(); }
    void clear() { data_.clear(); }
};

/**
 * Linked-list based Stack ADT.
 * Covers Syllabus: Unit 3 (Stack: representation and implementation using linked list)
 * Time Complexity: O(1) push, pop, top
 */
template <typename T>
class LinkedStack {
private:
    SNode<T>* top_node_;
    std::size_t size_;

public:
    LinkedStack() : top_node_(nullptr), size_(0) {}

    ~LinkedStack() {
        clear();
    }

    void clear() {
        while (top_node_) {
            SNode<T>* next = top_node_->next;
            delete top_node_;
            top_node_ = next;
        }
        size_ = 0;
    }

    void push(const T& val) {
        SNode<T>* node = new SNode<T>(val);
        node->next = top_node_;
        top_node_ = node;
        ++size_;
    }

    bool pop(T& out_val) {
        if (!top_node_) return false;
        SNode<T>* temp = top_node_;
        out_val = temp->data;
        top_node_ = top_node_->next;
        delete temp;
        --size_;
        return true;
    }

    bool top(T& out_val) const {
        if (!top_node_) return false;
        out_val = top_node_->data;
        return true;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
};

} // namespace dsa

#endif // ACADPULSE_STACK_HPP

