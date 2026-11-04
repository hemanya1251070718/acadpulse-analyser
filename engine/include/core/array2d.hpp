#ifndef ACADPULSE_ARRAY2D_HPP
#define ACADPULSE_ARRAY2D_HPP

#include <cstddef>

namespace dsa {

/**
 * 2D Matrix ADT using contiguous Row-Major Memory Layout.
 * Formula: Index(r, c) = r * cols + c.
 * Space Complexity: O(R * C)
 * Covers Syllabus: Unit 1 (Multidimensional Array Memory Representation)
 */
template <typename T>
class Array2D {
private:
    T* data_;
    std::size_t rows_;
    std::size_t cols_;

public:
    Array2D() : data_(nullptr), rows_(0), cols_(0) {}

    Array2D(std::size_t rows, std::size_t cols, const T& default_val = T()) 
        : data_(nullptr), rows_(rows), cols_(cols) {
        if (rows * cols > 0) {
            data_ = new T[rows * cols];
            for (std::size_t i = 0; i < rows * cols; ++i) {
                data_[i] = default_val;
            }
        }
    }

    ~Array2D() {
        delete[] data_;
    }

    Array2D(const Array2D& other) : data_(nullptr), rows_(other.rows_), cols_(other.cols_) {
        if (rows_ * cols_ > 0) {
            data_ = new T[rows_ * cols_];
            for (std::size_t i = 0; i < rows_ * cols_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    Array2D& operator=(const Array2D& other) {
        if (this != &other) {
            delete[] data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            if (rows_ * cols_ > 0) {
                data_ = new T[rows_ * cols_];
                for (std::size_t i = 0; i < rows_ * cols_; ++i) {
                    data_[i] = other.data_[i];
                }
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }

    Array2D(Array2D&& other) noexcept : data_(other.data_), rows_(other.rows_), cols_(other.cols_) {
        other.data_ = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
    }

    Array2D& operator=(Array2D&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            other.data_ = nullptr;
            other.rows_ = 0;
            other.cols_ = 0;
        }
        return *this;
    }

    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_; }

    T& at(std::size_t r, std::size_t c) {
        return data_[r * cols_ + c];
    }

    const T& at(std::size_t r, std::size_t c) const {
        return data_[r * cols_ + c];
    }

    T& operator()(std::size_t r, std::size_t c) {
        return data_[r * cols_ + c];
    }

    const T& operator()(std::size_t r, std::size_t c) const {
        return data_[r * cols_ + c];
    }

    std::size_t row_major_offset(std::size_t r, std::size_t c) const noexcept {
        return r * cols_ + c;
    }

    std::size_t col_major_offset(std::size_t r, std::size_t c) const noexcept {
        return c * rows_ + r;
    }
};

} // namespace dsa

#endif // ACADPULSE_ARRAY2D_HPP

