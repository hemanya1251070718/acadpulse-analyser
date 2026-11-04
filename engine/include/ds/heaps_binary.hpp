#ifndef ACADPULSE_HEAPS_BINARY_HPP
#define ACADPULSE_HEAPS_BINARY_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/metrics.hpp"

namespace dsa {

/**
 * Binary Max-Heap ADT.
 * Covers Syllabus: Unit 5 (Max Heap, Heap Operations, Heapify, Heapsort)
 * Used in Student Ranking for Top-K Merit List Generation (O(K log N) vs O(N log N) full sort).
 */
template <typename T>
class BinaryMaxHeap {
private:
    Vector<T> data_;

    void sift_up(std::size_t i, OpMetrics* metrics = nullptr) {
        while (i > 0) {
            std::size_t p = (i - 1) / 2;
            if (metrics) metrics->comparisons++;
            if (data_[p] < data_[i]) {
                T temp = data_[p];
                data_[p] = data_[i];
                data_[i] = temp;
                if (metrics) metrics->swaps++;
                i = p;
            } else {
                break;
            }
        }
    }

    void sift_down(std::size_t i, std::size_t n, OpMetrics* metrics = nullptr) {
        while (2 * i + 1 < n) {
            std::size_t left = 2 * i + 1;
            std::size_t right = 2 * i + 2;
            std::size_t largest = i;

            if (left < n) {
                if (metrics) metrics->comparisons++;
                if (data_[largest] < data_[left]) largest = left;
            }
            if (right < n) {
                if (metrics) metrics->comparisons++;
                if (data_[largest] < data_[right]) largest = right;
            }

            if (largest != i) {
                T temp = data_[i];
                data_[i] = data_[largest];
                data_[largest] = temp;
                if (metrics) metrics->swaps++;
                i = largest;
            } else {
                break;
            }
        }
    }

public:
    BinaryMaxHeap() {}

    explicit BinaryMaxHeap(const Vector<T>& items, OpMetrics* metrics = nullptr) : data_(items) {
        heapify(metrics);
    }

    /**
     * In-place Heapify in O(N) time.
     * Starts from last non-leaf node (N/2 - 1) down to 0.
     */
    void heapify(OpMetrics* metrics = nullptr) {
        if (data_.empty()) return;
        int n = static_cast<int>(data_.size());
        for (int i = n / 2 - 1; i >= 0; --i) {
            sift_down(i, data_.size(), metrics);
        }
    }

    void insert(const T& val, OpMetrics* metrics = nullptr) {
        data_.push_back(val);
        sift_up(data_.size() - 1, metrics);
    }

    bool extract_max(T& out_max, OpMetrics* metrics = nullptr) {
        if (data_.empty()) return false;
        out_max = data_[0];
        data_[0] = data_.back();
        data_.pop_back();
        if (!data_.empty()) {
            sift_down(0, data_.size(), metrics);
        }
        return true;
    }

    bool peek(T& out_max) const {
        if (data_.empty()) return false;
        out_max = data_[0];
        return true;
    }

    std::size_t size() const noexcept { return data_.size(); }
    bool empty() const noexcept { return data_.empty(); }

    static void sift_down_static(Vector<T>& arr, std::size_t i, std::size_t n, OpMetrics* metrics = nullptr) {
        std::size_t curr = i;
        while (2 * curr + 1 < n) {
            std::size_t left = 2 * curr + 1;
            std::size_t right = 2 * curr + 2;
            std::size_t largest = curr;

            if (left < n) {
                if (metrics) metrics->comparisons++;
                if (arr[largest] < arr[left]) largest = left;
            }
            if (right < n) {
                if (metrics) metrics->comparisons++;
                if (arr[largest] < arr[right]) largest = right;
            }

            if (largest != curr) {
                T tmp = arr[curr];
                arr[curr] = arr[largest];
                arr[largest] = tmp;
                if (metrics) metrics->swaps++;
                curr = largest;
            } else {
                break;
            }
        }
    }

    /**
     * In-place Heapsort Algorithm.
     * Time Complexity: O(N log N), Space: O(1) auxiliary.
     * Covers Syllabus: Unit 5 (Heapsort)
     */
    static void heapsort(Vector<T>& arr, OpMetrics* metrics = nullptr) {
        std::size_t n = arr.size();
        if (n <= 1) return;

        // 1. Build Max Heap O(N)
        for (int i = static_cast<int>(n) / 2 - 1; i >= 0; --i) {
            sift_down_static(arr, static_cast<std::size_t>(i), n, metrics);
        }

        // 2. Extract max one by one and place at end
        for (std::size_t i = n - 1; i > 0; --i) {
            T tmp = arr[0];
            arr[0] = arr[i];
            arr[i] = tmp;
            if (metrics) metrics->swaps++;

            sift_down_static(arr, 0, i, metrics);
        }
    }
};

/**
 * Binary Min-Heap ADT.
 * Covers Syllabus: Unit 5 (Min Heap)
 * Used for tracking at-risk/lowest scoring students and Dijkstra's algorithm.
 */
template <typename T>
class BinaryMinHeap {
private:
    Vector<T> data_;

    void sift_up(std::size_t i, OpMetrics* metrics = nullptr) {
        while (i > 0) {
            std::size_t p = (i - 1) / 2;
            if (metrics) metrics->comparisons++;
            if (data_[i] < data_[p]) {
                T temp = data_[p];
                data_[p] = data_[i];
                data_[i] = temp;
                if (metrics) metrics->swaps++;
                i = p;
            } else {
                break;
            }
        }
    }

    void sift_down(std::size_t i, OpMetrics* metrics = nullptr) {
        std::size_t n = data_.size();
        while (2 * i + 1 < n) {
            std::size_t left = 2 * i + 1;
            std::size_t right = 2 * i + 2;
            std::size_t smallest = i;

            if (left < n) {
                if (metrics) metrics->comparisons++;
                if (data_[left] < data_[smallest]) smallest = left;
            }
            if (right < n) {
                if (metrics) metrics->comparisons++;
                if (data_[right] < data_[smallest]) smallest = right;
            }

            if (smallest != i) {
                T temp = data_[i];
                data_[i] = data_[smallest];
                data_[smallest] = temp;
                if (metrics) metrics->swaps++;
                i = smallest;
            } else {
                break;
            }
        }
    }

public:
    BinaryMinHeap() {}

    void insert(const T& val, OpMetrics* metrics = nullptr) {
        data_.push_back(val);
        sift_up(data_.size() - 1, metrics);
    }

    bool extract_min(T& out_min, OpMetrics* metrics = nullptr) {
        if (data_.empty()) return false;
        out_min = data_[0];
        data_[0] = data_.back();
        data_.pop_back();
        if (!data_.empty()) {
            sift_down(0, metrics);
        }
        return true;
    }

    bool peek(T& out_min) const {
        if (data_.empty()) return false;
        out_min = data_[0];
        return true;
    }

    std::size_t size() const noexcept { return data_.size(); }
    bool empty() const noexcept { return data_.empty(); }
};

} // namespace dsa

#endif // ACADPULSE_HEAPS_BINARY_HPP
