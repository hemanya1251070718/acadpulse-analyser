#ifndef ACADPULSE_SPARSE_MATRIX_HPP
#define ACADPULSE_SPARSE_MATRIX_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/metrics.hpp"

namespace dsa {

/**
 * Triplet structure representing non-zero elements in Sparse Matrix.
 */
struct MatrixElement {
    std::size_t row;
    std::size_t col;
    double val;

    MatrixElement() : row(0), col(0), val(0.0) {}
    MatrixElement(std::size_t r, std::size_t c, double v) : row(r), col(c), val(v) {}
};

/**
 * Sparse Matrix ADT in 3-Tuple (Triplet) Representation.
 * Covers Syllabus: Unit 1 (Sparse Matrix: Simple & Fast Transpose)
 * 
 * Used in Student Ranking & Performance Analyser for:
 * - Student Elective Course Registration Matrix (Sparse, most students take 2 of 20 electives)
 * - Absenteeism / Remedial Exam Attendance Records
 * 
 * Time Complexities:
 * - Simple Transpose: O(Cols * Nonzeros)
 * - Fast Transpose: O(Cols + Nonzeros)
 * Space Complexity: O(Nonzeros)
 */
class SparseMatrix {
private:
    std::size_t rows_;
    std::size_t cols_;
    Vector<MatrixElement> elements_;

public:
    SparseMatrix() : rows_(0), cols_(0) {}
    SparseMatrix(std::size_t r, std::size_t c) : rows_(r), cols_(c) {}

    void insert(std::size_t r, std::size_t c, double val) {
        if (val != 0.0) {
            elements_.push_back(MatrixElement(r, c, val));
        }
    }

    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_; }
    std::size_t non_zeros() const noexcept { return elements_.size(); }
    const Vector<MatrixElement>& elements() const noexcept { return elements_; }

    /**
     * Simple Transpose:
     * Scans all non-zeros for each column 0..cols-1.
     * Time Complexity: O(Cols * Nonzeros)
     */
    SparseMatrix simple_transpose(OpMetrics* metrics = nullptr) const {
        SparseMatrix result(cols_, rows_);
        std::size_t total = elements_.size();

        for (std::size_t c = 0; c < cols_; ++c) {
            for (std::size_t i = 0; i < total; ++i) {
                if (metrics) metrics->comparisons++;
                if (elements_[i].col == c) {
                    result.elements_.push_back(MatrixElement(elements_[i].col, elements_[i].row, elements_[i].val));
                    if (metrics) metrics->swaps++;
                }
            }
        }
        return result;
    }

    /**
     * Fast Transpose:
     * Uses frequency array `total[col]` and start index array `index[col]`.
     * Time Complexity: O(Cols + Nonzeros)
     * Space Complexity: O(Cols) auxiliary
     */
    SparseMatrix fast_transpose(OpMetrics* metrics = nullptr) const {
        SparseMatrix result(cols_, rows_);
        std::size_t n = elements_.size();
        if (n == 0 || cols_ == 0) return result;

        result.elements_.resize(n);

        Vector<std::size_t> total(cols_, 0);
        Vector<std::size_t> index(cols_, 0);

        // Count non-zeros in each column of original matrix
        for (std::size_t i = 0; i < n; ++i) {
            total[elements_[i].col]++;
            if (metrics) metrics->pointer_hops++;
        }

        // Compute starting index for each column in transposed matrix
        index[0] = 0;
        for (std::size_t c = 1; c < cols_; ++c) {
            index[c] = index[c - 1] + total[c - 1];
            if (metrics) metrics->comparisons++;
        }

        // Place elements directly into their final sorted positions
        for (std::size_t i = 0; i < n; ++i) {
            std::size_t c = elements_[i].col;
            std::size_t pos = index[c];
            result.elements_[pos] = MatrixElement(elements_[i].col, elements_[i].row, elements_[i].val);
            index[c]++;
            if (metrics) metrics->swaps++;
        }

        return result;
    }
};

} // namespace dsa

#endif // ACADPULSE_SPARSE_MATRIX_HPP

