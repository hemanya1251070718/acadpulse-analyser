#ifndef ACADPULSE_BST_HPP
#define ACADPULSE_BST_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/pair.hpp"
#include "core/metrics.hpp"
#include "ds/binary_tree.hpp"

namespace dsa {

/**
 * Binary Search Tree (BST) ADT.
 * Covers Syllabus: Unit 4 (Binary Search trees (BST), 3-Case Deletion, Range Query, Balancing)
 */
template <typename K, typename V>
struct BSTNode {
    K key;
    V value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

template <typename K, typename V>
class BinarySearchTree {
private:
    BSTNode<K, V>* root_;
    std::size_t size_;

    void free_subtree(BSTNode<K, V>* node) {
        if (!node) return;
        free_subtree(node->left);
        free_subtree(node->right);
        delete node;
    }

    BSTNode<K, V>* insert_rec(BSTNode<K, V>* node, const K& key, const V& val, OpMetrics* metrics) {
        if (!node) {
            ++size_;
            return new BSTNode<K, V>(key, val);
        }
        if (metrics) metrics->comparisons++;
        if (key < node->key) {
            node->left = insert_rec(node->left, key, val, metrics);
        } else if (node->key < key) {
            node->right = insert_rec(node->right, key, val, metrics);
        } else {
            node->value = val; // update
        }
        return node;
    }

    BSTNode<K, V>* find_min(BSTNode<K, V>* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    /**
     * 3-Case BST Deletion
     */
    BSTNode<K, V>* delete_rec(BSTNode<K, V>* node, const K& key, bool& deleted, OpMetrics* metrics) {
        if (!node) return nullptr;

        if (metrics) metrics->comparisons++;
        if (key < node->key) {
            node->left = delete_rec(node->left, key, deleted, metrics);
        } else if (node->key < key) {
            node->right = delete_rec(node->right, key, deleted, metrics);
        } else {
            // Node found!
            deleted = true;
            --size_;

            // Case 1: Leaf node (No child)
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            if (!node->left) {
                BSTNode<K, V>* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode<K, V>* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            // Replace with In-order Successor (smallest in right subtree)
            BSTNode<K, V>* succ = find_min(node->right);
            node->key = succ->key;
            node->value = succ->value;
            // Delete successor from right subtree
            bool dummy = false;
            node->right = delete_rec(node->right, succ->key, dummy, metrics);
            ++size_; // restore count since recursive call decremented it
        }
        return node;
    }

    void inorder_rec(BSTNode<K, V>* node, Vector<Pair<K, V>>& out) const {
        if (!node) return;
        inorder_rec(node->left, out);
        out.push_back(Pair<K, V>(node->key, node->value));
        inorder_rec(node->right, out);
    }

    void range_query_rec(BSTNode<K, V>* node, const K& low, const K& high, Vector<Pair<K, V>>& out) const {
        if (!node) return;
        if (low < node->key) {
            range_query_rec(node->left, low, high, out);
        }
        if (!(node->key < low) && !(high < node->key)) {
            out.push_back(Pair<K, V>(node->key, node->value));
        }
        if (node->key < high) {
            range_query_rec(node->right, low, high, out);
        }
    }

    BSTNode<K, V>* build_balanced_from_sorted(Vector<Pair<K, V>>& arr, int start, int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        BSTNode<K, V>* node = new BSTNode<K, V>(arr[mid].first, arr[mid].second);
        node->left = build_balanced_from_sorted(arr, start, mid - 1);
        node->right = build_balanced_from_sorted(arr, mid + 1, end);
        return node;
    }

    std::size_t calc_height(BSTNode<K, V>* node) const {
        if (!node) return 0;
        std::size_t lh = calc_height(node->left);
        std::size_t rh = calc_height(node->right);
        return 1 + (lh > rh ? lh : rh);
    }

public:
    BinarySearchTree() : root_(nullptr), size_(0) {}

    ~BinarySearchTree() {
        free_subtree(root_);
    }

    void insert(const K& key, const V& val, OpMetrics* metrics = nullptr) {
        root_ = insert_rec(root_, key, val, metrics);
    }

    bool remove(const K& key, OpMetrics* metrics = nullptr) {
        bool deleted = false;
        root_ = delete_rec(root_, key, deleted, metrics);
        return deleted;
    }

    bool search(const K& key, V& out_val, OpMetrics* metrics = nullptr) const {
        BSTNode<K, V>* curr = root_;
        while (curr) {
            if (metrics) metrics->comparisons++;
            if (key < curr->key) {
                curr = curr->left;
            } else if (curr->key < key) {
                curr = curr->right;
            } else {
                out_val = curr->value;
                return true;
            }
        }
        return false;
    }

    Vector<Pair<K, V>> inorder() const {
        Vector<Pair<K, V>> res;
        inorder_rec(root_, res);
        return res;
    }

    Vector<Pair<K, V>> range_query(const K& low, const K& high) const {
        Vector<Pair<K, V>> res;
        range_query_rec(root_, low, high, res);
        return res;
    }

    void balance() {
        Vector<Pair<K, V>> sorted = inorder();
        free_subtree(root_);
        size_ = sorted.size();
        root_ = build_balanced_from_sorted(sorted, 0, static_cast<int>(sorted.size()) - 1);
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    std::size_t height() const { return calc_height(root_); }
};

} // namespace dsa

#endif // ACADPULSE_BST_HPP
