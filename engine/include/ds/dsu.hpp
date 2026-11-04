#ifndef ACADPULSE_DSU_HPP
#define ACADPULSE_DSU_HPP

#include <cstddef>
#include "core/vec.hpp"

namespace dsa {

/**
 * Disjoint Set Union (DSU / Union-Find) ADT.
 * Features:
 * - Path Compression in find() -> Amortized alpha(N)
 * - Union by Rank
 * Covers Syllabus: Unit 6 (Graph Connected Components, Kruskal's MST, Cycle Detection)
 */
class DisjointSetUnion {
private:
    Vector<std::size_t> parent_;
    Vector<std::size_t> rank_;
    std::size_t count_;

public:
    explicit DisjointSetUnion(std::size_t n = 0) : count_(n) {
        parent_.resize(n);
        rank_.resize(n, 0);
        for (std::size_t i = 0; i < n; ++i) {
            parent_[i] = i;
        }
    }

    std::size_t find(std::size_t x) {
        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]); // Path compression
        }
        return parent_[x];
    }

    bool unite(std::size_t x, std::size_t y) {
        std::size_t root_x = find(x);
        std::size_t root_y = find(y);
        if (root_x == root_y) return false; // Cycle detected

        // Union by rank
        if (rank_[root_x] < rank_[root_y]) {
            parent_[root_x] = root_y;
        } else if (rank_[root_y] < rank_[root_x]) {
            parent_[root_y] = root_x;
        } else {
            parent_[root_y] = root_x;
            rank_[root_x]++;
        }
        --count_;
        return true;
    }

    bool connected(std::size_t x, std::size_t y) {
        return find(x) == find(y);
    }

    std::size_t count() const noexcept { return count_; }
};

} // namespace dsa

#endif // ACADPULSE_DSU_HPP

