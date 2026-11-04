#ifndef ACADPULSE_ARRAY3D_HPP
#define ACADPULSE_ARRAY3D_HPP

#include <cstddef>

namespace dsa {

/**
 * 3D Array ADT: Contiguous Memory Representation.
 * Models: Semester (Depth) x Course (Rows) x Assessment (Cols).
 * Offset Formula: Index(d, r, c) = (d * rows * cols) + (r * cols) + c.
 * Space Complexity: O(Depth * Rows * Cols)
 * Covers Syllabus: Unit 1 (3D Multidimensional Array & Address Computation)
 */
template <typename T>
class Array3D {
private:
    T* data_;
    std::size_t depth_;
    std::size_t rows_;
    std::size_t cols_;

public:
    Array3D() : data_(nullptr), depth_(0), rows_(0), cols_(0) {}

    Array3D(std::size_t depth, std::size_t rows, std::size_t cols, const T& default_val = T())
        : data_(nullptr), depth_(depth), rows_(rows), cols_(cols) {
        std::size_t total = depth_ * rows_ * cols_;
        if (total > 0) {
            data_ = new T[total];
            for (std::size_t i = 0; i < total; ++i) {
                data_[i] = default_val;
            }
        }
    }

    ~Array3D() {
        delete[] data_;
    }

    Array3D(const Array3D& other) 
        : data_(nullptr), depth_(other.depth_), rows_(other.rows_), cols_(other.cols_) {
        std::size_t total = depth_ * rows_ * cols_;
        if (total > 0) {
            data_ = new T[total];
            for (std::size_t i = 0; i < total; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    Array3D& operator=(const Array3D& other) {
        if (this != &other) {
            delete[] data_;
            depth_ = other.depth_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            std::size_t total = depth_ * rows_ * cols_;
            if (total > 0) {
                data_ = new T[total];
                for (std::size_t i = 0; i < total; ++i) {
                    data_[i] = other.data_[i];
                }
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }

    Array3D(Array3D&& other) noexcept 
        : data_(other.data_), depth_(other.depth_), rows_(other.rows_), cols_(other.cols_) {
        other.data_ = nullptr;
        other.depth_ = 0;
        other.rows_ = 0;
        other.cols_ = 0;
    }

    Array3D& operator=(Array3D&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            depth_ = other.depth_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            other.data_ = nullptr;
            other.depth_ = 0;
            other.rows_ = 0;
            other.cols_ = 0;
        }
        return *this;
    }

    std::size_t depth() const noexcept { return depth_; }
    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_; }

    T& at(std::size_t d, std::size_t r, std::size_t c) {
        return data_[(d * rows_ * cols_) + (r * cols_) + c];
    }

    const T& at(std::size_t d, std::size_t r, std::size_t c) const {
        return data_[(d * rows_ * cols_) + (r * cols_) + c];
    }

    T& operator()(std::size_t d, std::size_t r, std::size_t c) {
        return at(d, r, c);
    }

    const T& operator()(std::size_t d, std::size_t r, std::size_t c) const {
        return at(d, r, c);
    }

    std::size_t calculate_offset(std::size_t d, std::size_t r, std::size_t c) const noexcept {
        return (d * rows_ * cols_) + (r * cols_) + c;
    }
};

} // namespace dsa

#endif // ACADPULSE_ARRAY3D_HPP

