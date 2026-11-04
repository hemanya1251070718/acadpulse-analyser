#ifndef ACADPULSE_BINARY_TREE_HPP
#define ACADPULSE_BINARY_TREE_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/pair.hpp"
#include "ds/stack.hpp"
#include "ds/queue.hpp"

namespace dsa {

/**
 * Binary Tree Node
 */
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

/**
 * Binary Tree ADT with both Pointer-Based and Array-Based representations.
 * Covers Syllabus: Unit 4 (Trees: terminology, representation using array and linked lists, traversals)
 */
template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root_;

    void free_subtree(TreeNode<T>* node) {
        if (!node) return;
        free_subtree(node->left);
        free_subtree(node->right);
        delete node;
    }

    void inorder_rec(TreeNode<T>* node, Vector<T>& out) const {
        if (!node) return;
        inorder_rec(node->left, out);
        out.push_back(node->data);
        inorder_rec(node->right, out);
    }

    void preorder_rec(TreeNode<T>* node, Vector<T>& out) const {
        if (!node) return;
        out.push_back(node->data);
        preorder_rec(node->left, out);
        preorder_rec(node->right, out);
    }

    void postorder_rec(TreeNode<T>* node, Vector<T>& out) const {
        if (!node) return;
        postorder_rec(node->left, out);
        postorder_rec(node->right, out);
        out.push_back(node->data);
    }

    std::size_t calc_height(TreeNode<T>* node) const {
        if (!node) return 0;
        std::size_t lh = calc_height(node->left);
        std::size_t rh = calc_height(node->right);
        return 1 + (lh > rh ? lh : rh);
    }

    std::size_t calc_count(TreeNode<T>* node) const {
        if (!node) return 0;
        return 1 + calc_count(node->left) + calc_count(node->right);
    }

public:
    BinaryTree() : root_(nullptr) {}
    explicit BinaryTree(TreeNode<T>* r) : root_(r) {}

    ~BinaryTree() {
        free_subtree(root_);
    }

    TreeNode<T>* root() const noexcept { return root_; }
    void set_root(TreeNode<T>* r) { root_ = r; }

    std::size_t height() const { return calc_height(root_); }
    std::size_t count() const { return calc_count(root_); }

    /**
     * Recursive Traversals:
     */
    Vector<T> inorder_recursive() const {
        Vector<T> res;
        inorder_rec(root_, res);
        return res;
    }

    Vector<T> preorder_recursive() const {
        Vector<T> res;
        preorder_rec(root_, res);
        return res;
    }

    Vector<T> postorder_recursive() const {
        Vector<T> res;
        postorder_rec(root_, res);
        return res;
    }

    /**
     * Non-recursive (Iterative) Inorder Traversal using explicit Stack ADT.
     * Covers Syllabus: Unit 4 (Non-recursive Traversals)
     */
    Vector<T> inorder_iterative() const {
        Vector<T> res;
        ArrayStack<TreeNode<T>*> st;
        TreeNode<T>* curr = root_;

        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            st.pop(curr);
            res.push_back(curr->data);
            curr = curr->right;
        }
        return res;
    }

    /**
     * Non-recursive (Iterative) Preorder Traversal using explicit Stack ADT.
     */
    Vector<T> preorder_iterative() const {
        Vector<T> res;
        if (!root_) return res;
        ArrayStack<TreeNode<T>*> st;
        st.push(root_);

        TreeNode<T>* curr = nullptr;
        while (st.pop(curr)) {
            res.push_back(curr->data);
            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
        }
        return res;
    }

    /**
     * Non-recursive (Iterative) Postorder Traversal using two explicit Stacks.
     */
    Vector<T> postorder_iterative() const {
        Vector<T> res;
        if (!root_) return res;
        ArrayStack<TreeNode<T>*> s1;
        ArrayStack<TreeNode<T>*> s2;

        s1.push(root_);
        TreeNode<T>* curr = nullptr;
        while (s1.pop(curr)) {
            s2.push(curr);
            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }

        while (s2.pop(curr)) {
            res.push_back(curr->data);
        }
        return res;
    }

    /**
     * Level Order Traversal using explicit Queue ADT.
     * Covers Syllabus: Unit 4 (Tree Traversals)
     */
    Vector<T> level_order() const {
        Vector<T> res;
        if (!root_) return res;
        CircularQueue<TreeNode<T>*> q(32);
        q.enqueue(root_);

        TreeNode<T>* curr = nullptr;
        while (q.dequeue(curr)) {
            res.push_back(curr->data);
            if (curr->left) q.enqueue(curr->left);
            if (curr->right) q.enqueue(curr->right);
        }
        return res;
    }

    /**
     * Array Representation of Binary Tree.
     * Left child: 2*i + 1, Right child: 2*i + 2, Parent: (i - 1) / 2.
     * Covers Syllabus: Unit 4 (representation using array)
     */
    static Vector<Pair<bool, T>> to_array_representation(TreeNode<T>* r) {
        Vector<Pair<bool, T>> arr;
        if (!r) return arr;

        CircularQueue<Pair<std::size_t, TreeNode<T>*>> q(32);
        q.enqueue(Pair<std::size_t, TreeNode<T>*>(std::size_t(0), r));

        Pair<std::size_t, TreeNode<T>*> curr;
        std::size_t max_idx = 0;

        Vector<Pair<std::size_t, T>> flat;
        while (q.dequeue(curr)) {
            flat.push_back(Pair<std::size_t, T>(curr.first, curr.second->data));
            if (curr.first > max_idx) max_idx = curr.first;

            if (curr.second->left) {
                q.enqueue(Pair<std::size_t, TreeNode<T>*>(2 * curr.first + 1, curr.second->left));
            }
            if (curr.second->right) {
                q.enqueue(Pair<std::size_t, TreeNode<T>*>(2 * curr.first + 2, curr.second->right));
            }
        }

        arr.resize(max_idx + 1, Pair<bool, T>(false, T()));
        for (std::size_t i = 0; i < flat.size(); ++i) {
            arr[flat[i].first] = Pair<bool, T>(true, flat[i].second);
        }
        return arr;
    }
};

} // namespace dsa

#endif // ACADPULSE_BINARY_TREE_HPP
