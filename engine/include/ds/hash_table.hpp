#ifndef ACADPULSE_HASH_TABLE_HPP
#define ACADPULSE_HASH_TABLE_HPP

#include <cstddef>
#include <cstdint>
#include "core/vec.hpp"
#include "core/pair.hpp"
#include "core/metrics.hpp"
#include "ds/linked_lists.hpp"

namespace dsa {

enum class CollisionStrategy {
    CHAINING,
    LINEAR_PROBING,
    QUADRATIC_PROBING,
    DOUBLE_HASHING
};

/**
 * Hash Function (djb2)
 */
inline uint64_t hash_djb2(const char* str) {
    uint64_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

inline uint64_t hash_secondary(uint64_t key_hash) {
    return 7 - (key_hash % 7);
}

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;
    bool occupied = false;
    bool deleted = false;
};

/**
 * Universal Hash Table ADT with 4 Collision Resolution Strategies & Dynamic Rehashing.
 * Covers Syllabus: Unit 2 (Hash Tables, Hash Functions, Collision Resolution)
 */
template <typename V>
class HashTable {
private:
    CollisionStrategy strategy_;
    std::size_t capacity_;
    std::size_t size_;

    // Chaining storage
    Vector<SinglyLinkedList<Pair<Vector<char>, V>>> chains_;

    // Open addressing storage
    Vector<HashEntry<Vector<char>, V>> table_;

    bool keys_equal(const Vector<char>& a, const char* b) const {
        std::size_t i = 0;
        while (i < a.size() && b[i] != '\0') {
            if (a[i] != b[i]) return false;
            ++i;
        }
        return (i == a.size() && b[i] == '\0');
    }

    Vector<char> to_vec(const char* s) const {
        Vector<char> v;
        while (*s) {
            v.push_back(*s);
            ++s;
        }
        return v;
    }

public:
    HashTable(CollisionStrategy strat = CollisionStrategy::CHAINING, std::size_t cap = 31)
        : strategy_(strat), capacity_(cap), size_(0) {
        if (strategy_ == CollisionStrategy::CHAINING) {
            chains_.resize(capacity_);
        } else {
            table_.resize(capacity_);
        }
    }

    void rehash() {
        std::size_t old_cap = capacity_;
        std::size_t new_cap = old_cap * 2 + 1;

        if (strategy_ == CollisionStrategy::CHAINING) {
            Vector<SinglyLinkedList<Pair<Vector<char>, V>>> old_chains = static_cast<Vector<SinglyLinkedList<Pair<Vector<char>, V>>>&&>(chains_);
            chains_.clear();
            chains_.resize(new_cap);
            capacity_ = new_cap;
            size_ = 0;

            for (std::size_t i = 0; i < old_cap; ++i) {
                SNode<Pair<Vector<char>, V>>* curr = old_chains[i].head();
                while (curr) {
                    put(curr->data.first.data(), curr->data.second);
                    curr = curr->next;
                }
            }
        } else {
            Vector<HashEntry<Vector<char>, V>> old_table = static_cast<Vector<HashEntry<Vector<char>, V>>&&>(table_);
            table_.clear();
            table_.resize(new_cap);
            capacity_ = new_cap;
            size_ = 0;

            for (std::size_t i = 0; i < old_cap; ++i) {
                if (old_table[i].occupied && !old_table[i].deleted) {
                    put(old_table[i].key.data(), old_table[i].value);
                }
            }
        }
    }

    bool put(const char* key, const V& val, OpMetrics* metrics = nullptr) {
        if (static_cast<double>(size_ + 1) / capacity_ > 0.70) {
            rehash();
        }

        uint64_t h = hash_djb2(key);

        if (strategy_ == CollisionStrategy::CHAINING) {
            std::size_t idx = h % capacity_;
            SNode<Pair<Vector<char>, V>>* curr = chains_[idx].head();
            while (curr) {
                if (metrics) metrics->comparisons++;
                if (keys_equal(curr->data.first, key)) {
                    curr->data.second = val;
                    return true;
                }
                curr = curr->next;
            }
            chains_[idx].push_back(Pair<Vector<char>, V>(to_vec(key), val));
            ++size_;
            return true;
        } else {
            std::size_t step = 0;
            std::size_t first_deleted = capacity_;

            while (step < capacity_) {
                std::size_t idx;
                if (strategy_ == CollisionStrategy::LINEAR_PROBING) {
                    idx = (h + step) % capacity_;
                } else if (strategy_ == CollisionStrategy::QUADRATIC_PROBING) {
                    idx = (h + step * step) % capacity_;
                } else { // DOUBLE_HASHING
                    idx = (h + step * hash_secondary(h)) % capacity_;
                }

                if (metrics) metrics->comparisons++;

                if (!table_[idx].occupied) {
                    std::size_t target = (first_deleted < capacity_) ? first_deleted : idx;
                    table_[target].key = to_vec(key);
                    table_[target].value = val;
                    table_[target].occupied = true;
                    table_[target].deleted = false;
                    ++size_;
                    return true;
                } else if (table_[idx].deleted) {
                    if (first_deleted == capacity_) first_deleted = idx;
                } else if (keys_equal(table_[idx].key, key)) {
                    table_[idx].value = val;
                    return true;
                }
                ++step;
            }
            return false;
        }
    }

    bool get(const char* key, V& out_val, OpMetrics* metrics = nullptr) const {
        uint64_t h = hash_djb2(key);

        if (strategy_ == CollisionStrategy::CHAINING) {
            std::size_t idx = h % capacity_;
            SNode<Pair<Vector<char>, V>>* curr = chains_[idx].head();
            while (curr) {
                if (metrics) metrics->comparisons++;
                if (keys_equal(curr->data.first, key)) {
                    out_val = curr->data.second;
                    return true;
                }
                curr = curr->next;
            }
            return false;
        } else {
            std::size_t step = 0;
            while (step < capacity_) {
                std::size_t idx;
                if (strategy_ == CollisionStrategy::LINEAR_PROBING) {
                    idx = (h + step) % capacity_;
                } else if (strategy_ == CollisionStrategy::QUADRATIC_PROBING) {
                    idx = (h + step * step) % capacity_;
                } else {
                    idx = (h + step * hash_secondary(h)) % capacity_;
                }

                if (metrics) metrics->comparisons++;

                if (!table_[idx].occupied) {
                    return false;
                }
                if (!table_[idx].deleted && keys_equal(table_[idx].key, key)) {
                    out_val = table_[idx].value;
                    return true;
                }
                ++step;
            }
            return false;
        }
    }

    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
    CollisionStrategy strategy() const noexcept { return strategy_; }
};

} // namespace dsa

#endif // ACADPULSE_HASH_TABLE_HPP
