#ifndef ACADPULSE_QUEUE_HPP
#define ACADPULSE_QUEUE_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "ds/linked_lists.hpp"

namespace dsa {

/**
 * Circular Array Queue ADT.
 * Covers Syllabus: Unit 3 (Queues: Representation and implementation using array)
 * Time Complexity: O(1) enqueue, dequeue
 */
template <typename T>
class CircularQueue {
private:
    T* data_;
    std::size_t capacity_;
    std::size_t front_;
    std::size_t rear_;
    std::size_t size_;

    void resize(std::size_t new_cap) {
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = static_cast<T&&>(data_[(front_ + i) % capacity_]);
        }
        delete[] data_;
        data_ = new_data;
        front_ = 0;
        rear_ = size_;
        capacity_ = new_cap;
    }

public:
    explicit CircularQueue(std::size_t cap = 16) 
        : data_(new T[cap]), capacity_(cap), front_(0), rear_(0), size_(0) {}

    ~CircularQueue() {
        delete[] data_;
    }

    void enqueue(const T& val) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        data_[rear_] = val;
        rear_ = (rear_ + 1) % capacity_;
        ++size_;
    }

    bool dequeue(T& out_val) {
        if (size_ == 0) return false;
        out_val = static_cast<T&&>(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        --size_;
        return true;
    }

    bool front(T& out_val) const {
        if (size_ == 0) return false;
        out_val = data_[front_];
        return true;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
};

/**
 * Linked List Queue ADT.
 * Covers Syllabus: Unit 3 (Queues: Representation and implementation using linked list)
 */
template <typename T>
class LinkedQueue {
private:
    SNode<T>* front_;
    SNode<T>* rear_;
    std::size_t size_;

public:
    LinkedQueue() : front_(nullptr), rear_(nullptr), size_(0) {}

    ~LinkedQueue() {
        clear();
    }

    void clear() {
        while (front_) {
            SNode<T>* temp = front_->next;
            delete front_;
            front_ = temp;
        }
        rear_ = nullptr;
        size_ = 0;
    }

    void enqueue(const T& val) {
        SNode<T>* node = new SNode<T>(val);
        if (!rear_) {
            front_ = rear_ = node;
        } else {
            rear_->next = node;
            rear_ = node;
        }
        ++size_;
    }

    bool dequeue(T& out_val) {
        if (!front_) return false;
        SNode<T>* temp = front_;
        out_val = temp->data;
        front_ = front_->next;
        if (!front_) rear_ = nullptr;
        delete temp;
        --size_;
        return true;
    }

    bool front(T& out_val) const {
        if (!front_) return false;
        out_val = front_->data;
        return true;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
};

/**
 * Priority Queue ADT backed by custom Binary Heap.
 * Covers Syllabus: Unit 3 (Priority Queue)
 */
template <typename T, typename Comparator>
class PriorityQueue {
private:
    Vector<T> heap_;
    Comparator comp_;

    void sift_up(std::size_t idx) {
        while (idx > 0) {
            std::size_t parent = (idx - 1) / 2;
            if (comp_(heap_[idx], heap_[parent])) {
                T temp = heap_[idx];
                heap_[idx] = heap_[parent];
                heap_[parent] = temp;
                idx = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(std::size_t idx) {
        std::size_t n = heap_.size();
        while (idx * 2 + 1 < n) {
            std::size_t left = idx * 2 + 1;
            std::size_t right = idx * 2 + 2;
            std::size_t best = idx;

            if (left < n && comp_(heap_[left], heap_[best])) {
                best = left;
            }
            if (right < n && comp_(heap_[right], heap_[best])) {
                best = right;
            }
            if (best != idx) {
                T temp = heap_[idx];
                heap_[idx] = heap_[best];
                heap_[best] = temp;
                idx = best;
            } else {
                break;
            }
        }
    }

public:
    PriorityQueue() {}

    void push(const T& val) {
        heap_.push_back(val);
        sift_up(heap_.size() - 1);
    }

    bool pop(T& out_val) {
        if (heap_.empty()) return false;
        out_val = heap_[0];
        heap_[0] = heap_.back();
        heap_.pop_back();
        if (!heap_.empty()) {
            sift_down(0);
        }
        return true;
    }

    bool top(T& out_val) const {
        if (heap_.empty()) return false;
        out_val = heap_[0];
        return true;
    }

    std::size_t size() const noexcept { return heap_.size(); }
    bool empty() const noexcept { return heap_.empty(); }
};

} // namespace dsa

#endif // ACADPULSE_QUEUE_HPP

