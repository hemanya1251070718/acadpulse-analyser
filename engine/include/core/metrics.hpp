#ifndef ACADPULSE_METRICS_HPP
#define ACADPULSE_METRICS_HPP

#include <cstdint>

namespace dsa {

/**
 * Metric & Complexity Tracker for Live Big-O Empirical Validation
 * Tracks operations: comparisons, swaps, heapify operations, pointer hops, allocations.
 * Covers Syllabus: Unit 1 (Asymptotic Notations, Time & Space Complexity)
 */
struct OpMetrics {
    uint64_t comparisons = 0;
    uint64_t swaps = 0;
    uint64_t allocations = 0;
    uint64_t pointer_hops = 0;
    uint64_t passes = 0;
    uint64_t recursion_depth = 0;
    uint64_t max_recursion_depth = 0;

    void reset() {
        comparisons = 0;
        swaps = 0;
        allocations = 0;
        pointer_hops = 0;
        passes = 0;
        recursion_depth = 0;
        max_recursion_depth = 0;
    }

    void record_recursion_enter() {
        ++recursion_depth;
        if (recursion_depth > max_recursion_depth) {
            max_recursion_depth = recursion_depth;
        }
    }

    void record_recursion_exit() {
        if (recursion_depth > 0) --recursion_depth;
    }
};

} // namespace dsa

#endif // ACADPULSE_METRICS_HPP

