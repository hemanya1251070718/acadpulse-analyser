#ifndef ACADPULSE_HEAP_LEFTIST_HPP
#define ACADPULSE_HEAP_LEFTIST_HPP

#include <cstddef>
#include "core/metrics.hpp"

namespace dsa {

/**
 * Leftist Heap Node
 */
template <typename T>
struct LeftistNode {
    T data;
    LeftistNode* left;
    LeftistNode* right;
    int npl; // Null Path Length

    LeftistNode(const T& val) : data(val), left(nullptr), right(nullptr), npl(0) {}
};

/**
 * Leftist Heap ADT (Min-Heap variant).
 * Covers Syllabus: Unit 5 (Leftist Heap, O(log N) Merge)
 * 
 * Properties:
 * - npl(node) = 1 + npl(node->right)
 * - npl(left) >= npl(right)
 * - Merge operation runs in O(log N) time.
 * - Used to merge independent course / division exam queues in O(log N).
 */
template <typename T>
class LeftistHeap {
private:
    LeftistNode<T>* root_;
    std::size_t size_;

    void free_subtree(LeftistNode<T>* node) {
        if (!node) return;
        free_subtree(node->left);
        free_subtree(node->right);
        delete node;
    }

    LeftistNode<T>* merge_trees(LeftistNode<T>* h1, LeftistNode<T>* h2, OpMetrics* metrics) {
        if (!h1) return h2;
        if (!h2) return h1;

        if (metrics) metrics->comparisons++;
        if (h2->data < h1->data) {
            LeftistNode<T>* tmp = h1;
            h1 = h2;
            h2 = tmp;
        }

        h1->right = merge_trees(h1->right, h2, metrics);

        if (!h1->left || (h1->right && h1->left->npl < h1->right->npl)) {
            LeftistNode<T>* tmp = h1->left;
            h1->left = h1->right;
            h1->right = tmp;
            if (metrics) metrics->swaps++;
        }

        h1->npl = (h1->right) ? h1->right->npl + 1 : 0;
        return h1;
    }

public:
    LeftistHeap() : root_(nullptr), size_(0) {}

    ~LeftistHeap() {
        free_subtree(root_);
    }

    void insert(const T& val, OpMetrics* metrics = nullptr) {
        LeftistNode<T>* new_node = new LeftistNode<T>(val);
        root_ = merge_trees(root_, new_node, metrics);
        ++size_;
    }

    bool extract_min(T& out_min, OpMetrics* metrics = nullptr) {
        if (!root_) return false;
        out_min = root_->data;
        LeftistNode<T>* old_root = root_;
        root_ = merge_trees(root_->left, root_->right, metrics);
        delete old_root;
        --size_;
        return true;
    }

    void merge(LeftistHeap& other, OpMetrics* metrics = nullptr) {
        if (this == &other) return;
        root_ = merge_trees(root_, other.root_, metrics);
        size_ += other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
    }

    bool peek(T& out_min) const {
        if (!root_) return false;
        out_min = root_->data;
        return true;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
};

} // namespace dsa

#endif // ACADPULSE_HEAP_LEFTIST_HPP

