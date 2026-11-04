#ifndef ACADPULSE_VEC_HPP
#define ACADPULSE_VEC_HPP

#include <cstddef>
#include <initializer_list>

namespace dsa {

/**
 * Dynamic Array ADT implemented from scratch (Zero-STL).
 * Amortized O(1) push_back with geometric doubling (factor 2).
 * Covers Syllabus: Unit 1 (Dynamic Arrays, Space/Time Complexity)
 */
template <typename T>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reallocate(std::size_t new_cap) {
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = static_cast<T&&>(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(std::size_t initial_cap) : data_(nullptr), size_(0), capacity_(0) {
        if (initial_cap > 0) {
            data_ = new T[initial_cap];
            capacity_ = initial_cap;
        }
    }

    Vector(std::size_t count, const T& value) : data_(nullptr), size_(0), capacity_(0) {
        if (count > 0) {
            data_ = new T[count];
            capacity_ = count;
            size_ = count;
            for (std::size_t i = 0; i < count; ++i) {
                data_[i] = value;
            }
        }
    }

    Vector(std::initializer_list<T> init) : data_(nullptr), size_(0), capacity_(0) {
        if (init.size() > 0) {
            data_ = new T[init.size()];
            capacity_ = init.size();
            for (const auto& item : init) {
                data_[size_++] = item;
            }
        }
    }

    ~Vector() {
        delete[] data_;
    }

    Vector(const Vector& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        if (capacity_ > 0) {
            data_ = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            if (capacity_ > 0) {
                data_ = new T[capacity_];
                for (std::size_t i = 0; i < size_; ++i) {
                    data_[i] = other.data_[i];
                }
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }

    Vector(Vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    void push_back(const T& val) {
        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        data_[size_++] = val;
    }

    void push_back(T&& val) {
        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        data_[size_++] = static_cast<T&&>(val);
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void clear() {
        size_ = 0;
    }

    void reserve(std::size_t new_cap) {
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
    }

    void resize(std::size_t new_size, const T& default_val = T()) {
        if (new_size > capacity_) {
            reallocate(new_size);
        }
        for (std::size_t i = size_; i < new_size; ++i) {
            data_[i] = default_val;
        }
        size_ = new_size;
    }

    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }

    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    T* begin() noexcept { return data_; }
    const T* begin() const noexcept { return data_; }
    T* end() noexcept { return data_ + size_; }
    const T* end() const noexcept { return data_ + size_; }
};

} // namespace dsa

#endif // ACADPULSE_VEC_HPP

