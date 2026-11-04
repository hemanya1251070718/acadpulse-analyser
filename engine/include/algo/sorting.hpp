#ifndef ACADPULSE_SORTING_HPP
#define ACADPULSE_SORTING_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/metrics.hpp"

namespace dsa {

/**
 * Snapshot of a sorting pass for educational and viva visualization.
 */
template <typename T>
struct SortPassSnapshot {
    std::size_t pass_num;
    Vector<T> array_state;
    std::size_t comparisons;
    std::size_t swaps;
};

enum class PivotStrategy {
    FIRST,
    LAST,
    MEDIAN_OF_THREE
};

/**
 * Sorting Algorithms with Step/Pass Tracking.
 * Covers Syllabus: Unit 1 (Sorting techniques: Merge Sort, Quick Sort with Analysis and passes, Insertion Sort)
 */
class Sorting {
public:
    /**
     * Insertion Sort: Adaptive O(N) best case, O(N^2) worst case.
     */
    template <typename T>
    static void insertion_sort(Vector<T>& arr, Vector<SortPassSnapshot<T>>* passes = nullptr, OpMetrics* metrics = nullptr) {
        std::size_t n = arr.size();
        for (std::size_t i = 1; i < n; ++i) {
            T key = arr[i];
            int j = static_cast<int>(i) - 1;

            while (j >= 0) {
                if (metrics) metrics->comparisons++;
                if (key < arr[j]) {
                    arr[j + 1] = arr[j];
                    if (metrics) metrics->swaps++;
                    --j;
                } else {
                    break;
                }
            }
            arr[j + 1] = key;

            if (passes) {
                SortPassSnapshot<T> snap;
                snap.pass_num = i;
                snap.array_state = arr;
                snap.comparisons = metrics ? metrics->comparisons : 0;
                snap.swaps = metrics ? metrics->swaps : 0;
                passes->push_back(snap);
            }
        }
    }

    /**
     * Merge Sort: Divide and Conquer, Stable O(N log N) in all cases.
     * Space: O(N) auxiliary.
     */
    template <typename T>
    static void merge_sort(Vector<T>& arr, Vector<SortPassSnapshot<T>>* passes = nullptr, OpMetrics* metrics = nullptr) {
        if (arr.size() <= 1) return;
        Vector<T> temp(arr.size(), T());
        std::size_t pass_counter = 0;
        merge_sort_helper(arr, temp, 0, arr.size() - 1, pass_counter, passes, metrics);
    }

private:
    template <typename T>
    static void merge_sort_helper(Vector<T>& arr, Vector<T>& temp, std::size_t left, std::size_t right,
                                  std::size_t& pass_counter, Vector<SortPassSnapshot<T>>* passes, OpMetrics* metrics) {
        if (left >= right) return;
        if (metrics) metrics->record_recursion_enter();

        std::size_t mid = left + (right - left) / 2;
        merge_sort_helper(arr, temp, left, mid, pass_counter, passes, metrics);
        merge_sort_helper(arr, temp, mid + 1, right, pass_counter, passes, metrics);

        // Merge two sorted halves
        std::size_t i = left;
        std::size_t j = mid + 1;
        std::size_t k = left;

        while (i <= mid && j <= right) {
            if (metrics) metrics->comparisons++;
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (std::size_t idx = left; idx <= right; ++idx) {
            arr[idx] = temp[idx];
            if (metrics) metrics->swaps++;
        }

        if (passes) {
            SortPassSnapshot<T> snap;
            snap.pass_num = ++pass_counter;
            snap.array_state = arr;
            snap.comparisons = metrics ? metrics->comparisons : 0;
            snap.swaps = metrics ? metrics->swaps : 0;
            passes->push_back(snap);
        }

        if (metrics) metrics->record_recursion_exit();
    }

public:
    /**
     * Quick Sort with 3 Pivot Strategies and Recursion Pass Tracking.
     * Time: O(N log N) average, O(N^2) worst case.
     */
    template <typename T>
    static void quick_sort(Vector<T>& arr, PivotStrategy pivot_strat = PivotStrategy::MEDIAN_OF_THREE,
                           Vector<SortPassSnapshot<T>>* passes = nullptr, OpMetrics* metrics = nullptr) {
        if (arr.size() <= 1) return;
        std::size_t pass_counter = 0;
        quick_sort_helper(arr, 0, static_cast<int>(arr.size()) - 1, pivot_strat, pass_counter, passes, metrics);
    }

private:
    template <typename T>
    static void quick_sort_helper(Vector<T>& arr, int low, int high, PivotStrategy pivot_strat,
                                  std::size_t& pass_counter, Vector<SortPassSnapshot<T>>* passes, OpMetrics* metrics) {
        if (low >= high) return;
        if (metrics) metrics->record_recursion_enter();

        int p_idx = partition(arr, low, high, pivot_strat, metrics);

        if (passes) {
            SortPassSnapshot<T> snap;
            snap.pass_num = ++pass_counter;
            snap.array_state = arr;
            snap.comparisons = metrics ? metrics->comparisons : 0;
            snap.swaps = metrics ? metrics->swaps : 0;
            passes->push_back(snap);
        }

        quick_sort_helper(arr, low, p_idx - 1, pivot_strat, pass_counter, passes, metrics);
        quick_sort_helper(arr, p_idx + 1, high, pivot_strat, pass_counter, passes, metrics);

        if (metrics) metrics->record_recursion_exit();
    }

    template <typename T>
    static int partition(Vector<T>& arr, int low, int high, PivotStrategy pivot_strat, OpMetrics* metrics) {
        if (pivot_strat == PivotStrategy::FIRST) {
            T tmp = arr[low];
            arr[low] = arr[high];
            arr[high] = tmp;
        } else if (pivot_strat == PivotStrategy::MEDIAN_OF_THREE) {
            int mid = low + (high - low) / 2;
            if (arr[mid] < arr[low]) { T t = arr[low]; arr[low] = arr[mid]; arr[mid] = t; }
            if (arr[high] < arr[low]) { T t = arr[low]; arr[low] = arr[high]; arr[high] = t; }
            if (arr[high] < arr[mid]) { T t = arr[mid]; arr[mid] = arr[high]; arr[high] = t; }
            // mid is now median
            T tmp = arr[mid];
            arr[mid] = arr[high];
            arr[high] = tmp;
        }

        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (metrics) metrics->comparisons++;
            if (arr[j] <= pivot) {
                ++i;
                T tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                if (metrics) metrics->swaps++;
            }
        }
        T tmp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tmp;
        if (metrics) metrics->swaps++;

        return i + 1;
    }
};

} // namespace dsa

#endif // ACADPULSE_SORTING_HPP

