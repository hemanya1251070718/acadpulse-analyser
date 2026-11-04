#ifndef ACADPULSE_PAIR_HPP
#define ACADPULSE_PAIR_HPP

namespace dsa {

/**
 * Custom Pair ADT (Zero-STL)
 */
template <typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;

    Pair() : first(), second() {}
    Pair(const T1& a, const T2& b) : first(a), second(b) {}
    Pair(T1&& a, T2&& b) : first(static_cast<T1&&>(a)), second(static_cast<T2&&>(b)) {}
    Pair(const Pair& o) = default;
    Pair& operator=(const Pair& o) = default;
    Pair(Pair&& o) noexcept = default;
    Pair& operator=(Pair&& o) noexcept = default;

    bool operator==(const Pair& o) const { return first == o.first && second == o.second; }
    bool operator!=(const Pair& o) const { return !(*this == o); }
    bool operator<(const Pair& o) const {
        if (first < o.first) return true;
        if (o.first < first) return false;
        return second < o.second;
    }
    bool operator>(const Pair& o) const { return o < *this; }
    bool operator<=(const Pair& o) const { return !(o < *this); }
    bool operator>=(const Pair& o) const { return !(*this < o); }
};

template <typename T1, typename T2>
Pair<T1, T2> make_pair(const T1& a, const T2& b) {
    return Pair<T1, T2>(a, b);
}

} // namespace dsa

#endif // ACADPULSE_PAIR_HPP

