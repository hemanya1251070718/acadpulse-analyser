#ifndef ACADPULSE_LINKED_LISTS_HPP
#define ACADPULSE_LINKED_LISTS_HPP

#include <cstddef>
#include "core/metrics.hpp"

namespace dsa {

/**
 * Singly Linked List Node
 */
template <typename T>
struct SNode {
    T data;
    SNode* next;
    SNode(const T& val) : data(val), next(nullptr) {}
};

/**
 * Singly Linked List ADT with Fast & Slow Pointers and Dynamic Memory Allocation.
 * Covers Syllabus: Unit 2 (Singly Linked Lists, Fast/Slow Pointer, Dynamic Memory)
 */
template <typename T>
class SinglyLinkedList {
private:
    SNode<T>* head_;
    SNode<T>* tail_;
    std::size_t size_;

public:
    SinglyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~SinglyLinkedList() {
        clear();
    }

    void clear() {
        SNode<T>* curr = head_;
        while (curr) {
            SNode<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    void push_front(const T& val) {
        SNode<T>* node = new SNode<T>(val);
        node->next = head_;
        head_ = node;
        if (!tail_) tail_ = head_;
        ++size_;
    }

    void push_back(const T& val) {
        SNode<T>* node = new SNode<T>(val);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    bool pop_front(T& out_val) {
        if (!head_) return false;
        SNode<T>* temp = head_;
        out_val = temp->data;
        head_ = head_->next;
        if (!head_) tail_ = nullptr;
        delete temp;
        --size_;
        return true;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    SNode<T>* head() const noexcept { return head_; }

    /**
     * Fast and Slow Pointer technique to find the middle element in a single pass O(N).
     * Covers Syllabus: Unit 2 (Fast and Slow Pointers)
     */
    bool find_middle(T& middle_val, OpMetrics* metrics = nullptr) const {
        if (!head_) return false;
        SNode<T>* slow = head_;
        SNode<T>* fast = head_;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (metrics) metrics->pointer_hops += 2;
        }
        middle_val = slow->data;
        return true;
    }

    /**
     * Reverse Singly Linked List in-place O(N) time, O(1) space.
     */
    void reverse() {
        SNode<T>* prev = nullptr;
        SNode<T>* curr = head_;
        tail_ = head_;
        while (curr) {
            SNode<T>* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head_ = prev;
    }
};

/**
 * Doubly Linked List Node
 */
template <typename T>
struct DNode {
    T data;
    DNode* prev;
    DNode* next;
    DNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};

/**
 * Doubly Linked List ADT.
 * Covers Syllabus: Unit 2 (Doubly Linked Lists, Bidirectional Traversal, O(1) Removal)
 * Used in Student Ranking for maintaining an editable ranking chain where rank updates
 * perform O(1) splice / deletion.
 */
template <typename T>
class DoublyLinkedList {
private:
    DNode<T>* head_;
    DNode<T>* tail_;
    std::size_t size_;

public:
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void clear() {
        DNode<T>* curr = head_;
        while (curr) {
            DNode<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void push_front(const T& val) {
        DNode<T>* node = new DNode<T>(val);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    void push_back(const T& val) {
        DNode<T>* node = new DNode<T>(val);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        ++size_;
    }

    /**
     * O(1) Removal of an arbitrary node given pointer.
     */
    void remove_node(DNode<T>* node) {
        if (!node) return;
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }
        delete node;
        --size_;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    DNode<T>* head() const noexcept { return head_; }
    DNode<T>* tail() const noexcept { return tail_; }
};

/**
 * Circular Linked List ADT.
 * Covers Syllabus: Unit 2 (Circular Linked Lists, Round-Robin viva/exam scheduling)
 */
template <typename T>
class CircularLinkedList {
private:
    SNode<T>* tail_;
    std::size_t size_;

public:
    CircularLinkedList() : tail_(nullptr), size_(0) {}

    ~CircularLinkedList() {
        clear();
    }

    void clear() {
        if (!tail_) return;
        SNode<T>* curr = tail_->next;
        while (curr != tail_) {
            SNode<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        delete tail_;
        tail_ = nullptr;
        size_ = 0;
    }

    void push_back(const T& val) {
        SNode<T>* node = new SNode<T>(val);
        if (!tail_) {
            tail_ = node;
            tail_->next = tail_;
        } else {
            node->next = tail_->next;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    SNode<T>* head() const noexcept { return tail_ ? tail_->next : nullptr; }
};

/**
 * Floyd's Cycle Detection (Tortoise and the Hare)
 * Time Complexity: O(N), Space Complexity: O(1)
 * Covers Syllabus: Unit 2 (Floyd's Cycle Detection)
 */
template <typename T>
bool has_cycle(SNode<T>* head, OpMetrics* metrics = nullptr) {
    if (!head || !head->next) return false;
    SNode<T>* slow = head;
    SNode<T>* fast = head->next;

    while (fast && fast->next) {
        if (slow == fast) return true;
        slow = slow->next;
        fast = fast->next->next;
        if (metrics) {
            metrics->pointer_hops += 2;
            metrics->comparisons++;
        }
    }
    return false;
}

/**
 * Polynomial Term Node for Grade Weighting Decay / Curriculum Modeling
 * Covers Syllabus: Unit 2 (Applications of Linked List - Polynomial Addition)
 */
struct PolyTerm {
    double coeff;
    int exp;
    PolyTerm* next;
    PolyTerm(double c, int e) : coeff(c), exp(e), next(nullptr) {}
};

class Polynomial {
public:
    PolyTerm* head;

    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        PolyTerm* curr = head;
        while (curr) {
            PolyTerm* n = curr->next;
            delete curr;
            curr = n;
        }
    }

    void add_term(double coeff, int exp) {
        if (coeff == 0.0) return;
        PolyTerm* node = new PolyTerm(coeff, exp);
        if (!head || head->exp < exp) {
            node->next = head;
            head = node;
            return;
        }
        PolyTerm* curr = head;
        while (curr->next && curr->next->exp >= exp) {
            curr = curr->next;
        }
        if (curr->exp == exp) {
            curr->coeff += coeff;
            delete node;
        } else {
            node->next = curr->next;
            curr->next = node;
        }
    }

    static Polynomial add(const Polynomial& p1, const Polynomial& p2) {
        Polynomial res;
        PolyTerm* t1 = p1.head;
        PolyTerm* t2 = p2.head;

        while (t1 && t2) {
            if (t1->exp > t2->exp) {
                res.add_term(t1->coeff, t1->exp);
                t1 = t1->next;
            } else if (t2->exp > t1->exp) {
                res.add_term(t2->coeff, t2->exp);
                t2 = t2->next;
            } else {
                res.add_term(t1->coeff + t2->coeff, t1->exp);
                t1 = t1->next;
                t2 = t2->next;
            }
        }
        while (t1) {
            res.add_term(t1->coeff, t1->exp);
            t1 = t1->next;
        }
        while (t2) {
            res.add_term(t2->coeff, t2->exp);
            t2 = t2->next;
        }
        return res;
    }
};

} // namespace dsa

#endif // ACADPULSE_LINKED_LISTS_HPP

