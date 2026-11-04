#ifndef ACADPULSE_HEAP_BINOMIAL_HPP
#define ACADPULSE_HEAP_BINOMIAL_HPP

#include <cstddef>
#include "core/metrics.hpp"

namespace dsa {

/**
 * Binomial Tree Node
 */
template <typename T>
struct BinomialNode {
    T data;
    std::size_t degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(const T& val) 
        : data(val), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

/**
 * Binomial Heap ADT (Min-Heap variant).
 * Covers Syllabus: Unit 5 (Binomial Heaps, Union, Extract-Min)
 * 
 * Supports:
 * - Insert: O(log N) worst-case, O(1) amortized
 * - Union: O(log N)
 * - Extract-Min: O(log N)
 * - Find-Min: O(log N) or O(1)
 */
template <typename T>
class BinomialHeap {
private:
    BinomialNode<T>* head_;
    std::size_t size_;

    static BinomialNode<T>* link_trees(BinomialNode<T>* y, BinomialNode<T>* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
        return z;
    }

    static BinomialNode<T>* merge_roots(BinomialNode<T>* h1, BinomialNode<T>* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        BinomialNode<T>* head = nullptr;
        BinomialNode<T>** tail = &head;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *tail = h1;
                h1 = h1->sibling;
            } else {
                *tail = h2;
                h2 = h2->sibling;
            }
            tail = &((*tail)->sibling);
        }
        *tail = (h1) ? h1 : h2;
        return head;
    }

    static BinomialNode<T>* union_heaps_internal(BinomialNode<T>* h1, BinomialNode<T>* h2, OpMetrics* metrics) {
        BinomialNode<T>* new_head = merge_roots(h1, h2);
        if (!new_head) return nullptr;

        BinomialNode<T>* prev = nullptr;
        BinomialNode<T>* curr = new_head;
        BinomialNode<T>* next = curr->sibling;

        while (next) {
            if (metrics) metrics->comparisons++;
            if ((curr->degree != next->degree) || 
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->data <= next->data) {
                    curr->sibling = next->sibling;
                    link_trees(next, curr);
                } else {
                    if (!prev) {
                        new_head = next;
                    } else {
                        prev->sibling = next;
                    }
                    link_trees(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
        return new_head;
    }

    void free_tree(BinomialNode<T>* node) {
        if (!node) return;
        BinomialNode<T>* child = node->child;
        while (child) {
            BinomialNode<T>* next_child = child->sibling;
            free_tree(child);
            child = next_child;
        }
        delete node;
    }

public:
    BinomialHeap() : head_(nullptr), size_(0) {}

    ~BinomialHeap() {
        BinomialNode<T>* curr = head_;
        while (curr) {
            BinomialNode<T>* next = curr->sibling;
            free_tree(curr);
            curr = next;
        }
    }

    void insert(const T& val, OpMetrics* metrics = nullptr) {
        BinomialNode<T>* node = new BinomialNode<T>(val);
        head_ = union_heaps_internal(head_, node, metrics);
        ++size_;
    }

    bool peek(T& out_min) const {
        if (!head_) return false;
        BinomialNode<T>* min_node = head_;
        BinomialNode<T>* curr = head_->sibling;
        while (curr) {
            if (curr->data < min_node->data) {
                min_node = curr;
            }
            curr = curr->sibling;
        }
        out_min = min_node->data;
        return true;
    }

    bool extract_min(T& out_min, OpMetrics* metrics = nullptr) {
        if (!head_) return false;

        // Find min root
        BinomialNode<T>* min_prev = nullptr;
        BinomialNode<T>* min_node = head_;
        BinomialNode<T>* prev = head_;
        BinomialNode<T>* curr = head_->sibling;

        while (curr) {
            if (metrics) metrics->comparisons++;
            if (curr->data < min_node->data) {
                min_node = curr;
                min_prev = prev;
            }
            prev = curr;
            curr = curr->sibling;
        }

        // Remove min_node from root list
        if (!min_prev) {
            head_ = min_node->sibling;
        } else {
            min_prev->sibling = min_node->sibling;
        }

        out_min = min_node->data;

        // Reverse children of min_node to form a new root list
        BinomialNode<T>* child_head = nullptr;
        BinomialNode<T>* child = min_node->child;
        while (child) {
            BinomialNode<T>* next_child = child->sibling;
            child->sibling = child_head;
            child->parent = nullptr;
            child_head = child;
            child = next_child;
        }

        delete min_node;
        head_ = union_heaps_internal(head_, child_head, metrics);
        --size_;
        return true;
    }

    void merge(BinomialHeap& other, OpMetrics* metrics = nullptr) {
        if (this == &other) return;
        head_ = union_heaps_internal(head_, other.head_, metrics);
        size_ += other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
};

} // namespace dsa

#endif // ACADPULSE_HEAP_BINOMIAL_HPP

