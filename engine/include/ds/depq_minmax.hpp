#ifndef ACADPULSE_DEPQ_MINMAX_HPP
#define ACADPULSE_DEPQ_MINMAX_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/metrics.hpp"

namespace dsa {

/**
 * Double-Ended Priority Queue (DEPQ) implemented as a Min-Max Heap.
 * Covers Syllabus: Unit 3 (Doubly Ended Priority Queue)
 * 
 * Properties:
 * - Root is at level 0 (Min level: every node at level 2k is <= all descendants)
 * - Level 1 is Max level (every node at level 2k+1 is >= all descendants)
 * - peek_min(): O(1) -> Returns lowest performing / at-risk student
 * - peek_max(): O(1) -> Returns top ranker / merit gold medalist
 * - push(): O(log N)
 * - pop_min(), pop_max(): O(log N)
 */
template <typename T>
class MinMaxHeap {
private:
    Vector<T> heap_;

    static int level_of(std::size_t i) {
        int lvl = 0;
        std::size_t val = i + 1;
        while (val >>= 1) {
            lvl++;
        }
        return lvl;
    }

    static bool is_min_level(std::size_t i) {
        return (level_of(i) % 2) == 0;
    }

    void swap_nodes(std::size_t i, std::size_t j) {
        T temp = heap_[i];
        heap_[i] = heap_[j];
        heap_[j] = temp;
    }

    void push_up_min(std::size_t i) {
        while (i >= 3) { // has grandparent
            std::size_t gp = (i - 3) / 4;
            if (heap_[i] < heap_[gp]) {
                swap_nodes(i, gp);
                i = gp;
            } else {
                break;
            }
        }
    }

    void push_up_max(std::size_t i) {
        while (i >= 3) { // has grandparent
            std::size_t gp = (i - 3) / 4;
            if (heap_[gp] < heap_[i]) {
                swap_nodes(i, gp);
                i = gp;
            } else {
                break;
            }
        }
    }

    void push_up(std::size_t i) {
        if (i == 0) return;
        std::size_t p = (i - 1) / 2;
        if (is_min_level(i)) {
            if (heap_[p] < heap_[i]) {
                swap_nodes(i, p);
                push_up_max(p);
            } else {
                push_up_min(i);
            }
        } else {
            if (heap_[i] < heap_[p]) {
                swap_nodes(i, p);
                push_up_min(p);
            } else {
                push_up_max(i);
            }
        }
    }

    void push_down_min(std::size_t i) {
        std::size_t n = heap_.size();
        while (true) {
            std::size_t m = i;
            // Children
            for (std::size_t c = 2 * i + 1; c <= 2 * i + 2 && c < n; ++c) {
                if (heap_[c] < heap_[m]) m = c;
            }
            // Grandchildren
            for (std::size_t gc = 4 * i + 3; gc <= 4 * i + 6 && gc < n; ++gc) {
                if (heap_[gc] < heap_[m]) m = gc;
            }

            if (m == i) break;

            if (m >= 4 * i + 3) { // m is a grandchild
                if (heap_[m] < heap_[i]) {
                    swap_nodes(m, i);
                    std::size_t parent_of_m = (m - 1) / 2;
                    if (heap_[parent_of_m] < heap_[m]) {
                        swap_nodes(m, parent_of_m);
                    }
                    i = m; // continue sifting down
                } else {
                    break;
                }
            } else { // m is a direct child
                if (heap_[m] < heap_[i]) {
                    swap_nodes(m, i);
                }
                break;
            }
        }
    }

    void push_down_max(std::size_t i) {
        std::size_t n = heap_.size();
        while (true) {
            std::size_t m = i;
            // Children
            for (std::size_t c = 2 * i + 1; c <= 2 * i + 2 && c < n; ++c) {
                if (heap_[m] < heap_[c]) m = c;
            }
            // Grandchildren
            for (std::size_t gc = 4 * i + 3; gc <= 4 * i + 6 && gc < n; ++gc) {
                if (heap_[m] < heap_[gc]) m = gc;
            }

            if (m == i) break;

            if (m >= 4 * i + 3) { // grandchild
                if (heap_[i] < heap_[m]) {
                    swap_nodes(m, i);
                    std::size_t parent_of_m = (m - 1) / 2;
                    if (heap_[m] < heap_[parent_of_m]) {
                        swap_nodes(m, parent_of_m);
                    }
                    i = m;
                } else {
                    break;
                }
            } else { // direct child
                if (heap_[i] < heap_[m]) {
                    swap_nodes(m, i);
                }
                break;
            }
        }
    }

    void push_down(std::size_t i) {
        if (is_min_level(i)) {
            push_down_min(i);
        } else {
            push_down_max(i);
        }
    }

public:
    MinMaxHeap() {}

    void push(const T& val) {
        heap_.push_back(val);
        push_up(heap_.size() - 1);
    }

    bool empty() const noexcept { return heap_.empty(); }
    std::size_t size() const noexcept { return heap_.size(); }

    bool peek_min(T& out) const {
        if (heap_.empty()) return false;
        out = heap_[0];
        return true;
    }

    bool peek_max(T& out) const {
        if (heap_.empty()) return false;
        if (heap_.size() == 1) {
            out = heap_[0];
            return true;
        }
        if (heap_.size() == 2) {
            out = heap_[1];
            return true;
        }
        out = (heap_[1] < heap_[2]) ? heap_[2] : heap_[1];
        return true;
    }

    bool pop_min(T& out) {
        if (heap_.empty()) return false;
        out = heap_[0];
        heap_[0] = heap_.back();
        heap_.pop_back();
        if (!heap_.empty()) {
            push_down(0);
        }
        return true;
    }

    bool pop_max(T& out) {
        if (heap_.empty()) return false;
        if (heap_.size() == 1) {
            out = heap_[0];
            heap_.pop_back();
            return true;
        }
        std::size_t max_idx = 1;
        if (heap_.size() > 2 && heap_[1] < heap_[2]) {
            max_idx = 2;
        }
        out = heap_[max_idx];
        heap_[max_idx] = heap_.back();
        heap_.pop_back();
        if (max_idx < heap_.size()) {
            push_down(max_idx);
        }
        return true;
    }
};

} // namespace dsa

#endif // ACADPULSE_DEPQ_MINMAX_HPP

