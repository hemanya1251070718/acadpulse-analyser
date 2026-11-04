#ifndef ACADPULSE_HEAP_FIBONACCI_HPP
#define ACADPULSE_HEAP_FIBONACCI_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/metrics.hpp"

namespace dsa {

template <typename T>
struct FibNode {
    T data;
    std::size_t degree;
    bool marked;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;

    FibNode(const T& val)
        : data(val), degree(0), marked(false), parent(nullptr), child(nullptr), left(this), right(this) {}
};

/**
 * Fibonacci Heap ADT (Min-Heap variant).
 * Covers Syllabus: Unit 5 (Fibonacci Heaps, Amortized O(1) Decrease-Key, Cascading Cuts)
 */
template <typename T>
class FibonacciHeap {
private:
    FibNode<T>* min_node_;
    std::size_t size_;

    void insert_into_root_list(FibNode<T>* node) {
        if (!min_node_) {
            min_node_ = node;
            node->left = node;
            node->right = node;
        } else {
            node->right = min_node_->right;
            node->left = min_node_;
            min_node_->right->left = node;
            min_node_->right = node;
            if (node->data < min_node_->data) {
                min_node_ = node;
            }
        }
    }

    void remove_from_root_list(FibNode<T>* node) {
        if (node->right == node) {
            min_node_ = nullptr;
        } else {
            node->left->right = node->right;
            node->right->left = node->left;
            if (min_node_ == node) {
                min_node_ = node->right;
            }
        }
    }

    void link_trees(FibNode<T>* y, FibNode<T>* x) {
        // remove y from root list
        y->left->right = y->right;
        y->right->left = y->left;

        // make y a child of x
        y->parent = x;
        if (!x->child) {
            x->child = y;
            y->left = y;
            y->right = y;
        } else {
            y->right = x->child->right;
            y->left = x->child;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->marked = false;
    }

    void consolidate(OpMetrics* metrics) {
        std::size_t max_deg = 45; // sufficient for > 10^9 nodes
        Vector<FibNode<T>*> A(max_deg, nullptr);

        if (!min_node_) return;

        // Collect root list nodes
        Vector<FibNode<T>*> roots;
        FibNode<T>* curr = min_node_;
        if (curr) {
            do {
                roots.push_back(curr);
                curr = curr->right;
            } while (curr != min_node_);
        }

        for (std::size_t i = 0; i < roots.size(); ++i) {
            FibNode<T>* x = roots[i];
            std::size_t d = x->degree;
            while (d < max_deg && A[d]) {
                FibNode<T>* y = A[d];
                if (metrics) metrics->comparisons++;
                if (y->data < x->data) {
                    FibNode<T>* tmp = x;
                    x = y;
                    y = tmp;
                }
                link_trees(y, x);
                A[d] = nullptr;
                d++;
            }
            if (d < max_deg) {
                A[d] = x;
            }
        }

        min_node_ = nullptr;
        for (std::size_t i = 0; i < max_deg; ++i) {
            if (A[i]) {
                if (!min_node_) {
                    min_node_ = A[i];
                    min_node_->left = min_node_;
                    min_node_->right = min_node_;
                } else {
                    insert_into_root_list(A[i]);
                }
            }
        }
    }

    void cut(FibNode<T>* x, FibNode<T>* y) {
        // remove x from child list of y
        if (x->right == x) {
            y->child = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) {
                y->child = x->right;
            }
        }
        y->degree--;

        // add x to root list
        insert_into_root_list(x);
        x->parent = nullptr;
        x->marked = false;
    }

    void cascading_cut(FibNode<T>* y) {
        FibNode<T>* z = y->parent;
        if (z) {
            if (!y->marked) {
                y->marked = true;
            } else {
                cut(y, z);
                cascading_cut(z);
            }
        }
    }

    void free_subtree(FibNode<T>* node) {
        if (!node) return;
        FibNode<T>* curr = node;
        do {
            FibNode<T>* next = curr->right;
            if (curr->child) free_subtree(curr->child);
            delete curr;
            curr = next;
        } while (curr != node);
    }

public:
    FibonacciHeap() : min_node_(nullptr), size_(0) {}

    ~FibonacciHeap() {
        if (min_node_) {
            free_subtree(min_node_);
        }
    }

    FibNode<T>* insert(const T& val) {
        FibNode<T>* node = new FibNode<T>(val);
        insert_into_root_list(node);
        ++size_;
        return node;
    }

    bool peek(T& out_min) const {
        if (!min_node_) return false;
        out_min = min_node_->data;
        return true;
    }

    bool extract_min(T& out_min, OpMetrics* metrics = nullptr) {
        FibNode<T>* z = min_node_;
        if (!z) return false;

        out_min = z->data;

        // Add children of z to root list
        if (z->child) {
            FibNode<T>* child = z->child;
            FibNode<T>* start = child;
            do {
                FibNode<T>* next = child->right;
                insert_into_root_list(child);
                child->parent = nullptr;
                child = next;
            } while (child != start);
        }

        remove_from_root_list(z);
        delete z;
        --size_;

        if (size_ == 0) {
            min_node_ = nullptr;
        } else {
            consolidate(metrics);
        }
        return true;
    }

    void decrease_key(FibNode<T>* x, const T& new_val) {
        if (x->data < new_val) return; // only decrease
        x->data = new_val;
        FibNode<T>* y = x->parent;
        if (y && x->data < y->data) {
            cut(x, y);
            cascading_cut(y);
        }
        if (x->data < min_node_->data) {
            min_node_ = x;
        }
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
};

} // namespace dsa

#endif // ACADPULSE_HEAP_FIBONACCI_HPP

