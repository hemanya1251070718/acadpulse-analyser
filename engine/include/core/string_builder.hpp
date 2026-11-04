#ifndef ACADPULSE_STRING_BUILDER_HPP
#define ACADPULSE_STRING_BUILDER_HPP

#include <cstddef>
#include <cstdio>
#include <cstring>
#include "core/vec.hpp"

namespace dsa {

/**
 * Lightweight Zero-STL String Buffer & JSON Serializer
 */
class StringBuilder {
private:
    Vector<char> buffer_;

public:
    StringBuilder() {}

    void append(char c) {
        buffer_.push_back(c);
    }

    void append(const char* str) {
        if (!str) return;
        while (*str) {
            buffer_.push_back(*str);
            ++str;
        }
    }

    void append_int(long long val) {
        char temp[32];
        std::snprintf(temp, sizeof(temp), "%lld", val);
        append(temp);
    }

    void append_float(double val, int precision = 2) {
        char temp[32];
        char fmt[16];
        std::snprintf(fmt, sizeof(fmt), "%%.%df", precision);
        std::snprintf(temp, sizeof(temp), fmt, val);
        append(temp);
    }

    void clear() {
        buffer_.clear();
    }

    const char* c_str() {
        buffer_.push_back('\0');
        const char* ptr = buffer_.data();
        buffer_.pop_back(); // preserve size
        return ptr ? ptr : "";
    }

    std::size_t length() const {
        return buffer_.size();
    }
};

} // namespace dsa

#endif // ACADPULSE_STRING_BUILDER_HPP

