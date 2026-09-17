
#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "common/throw_check.h"
#include "container/strong_int.h"
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>
#include "common/log.h"

#define DECLARE_STRONG_VECTOR(Name)                                          \
    DEFINE_STRONG_INT_TYPE(Name##Index, int);                                \
    class Name##IndexRange {                                                 \
     public:                                                                 \
        class Iterator : public Name##Index {                                \
         public:                                                             \
            explicit constexpr Iterator(int i) : Name##Index(i) {}           \
            Name##Index operator*() { return *this; }                        \
        };                                                                   \
        Name##IndexRange(int end) : end_(end) {}                             \
        Name##IndexRange(int begin, int end) : begin_(begin), end_(end) {}   \
        Iterator begin() const { return Iterator(begin_); }                  \
        Iterator end() const { return Iterator(end_); }                      \
                                                                             \
     private:                                                                \
        int begin_ = 0;                                                      \
        int end_ = 0;                                                        \
    };                                                                       \
    template <class T, class Alloc = std::allocator<T>>                      \
    class Name##Vector {                                                     \
     public:                                                                 \
        static constexpr Name##Index kInvalidIndex = Name##Index(-1);        \
        using value_type = T;                                                \
        void reserve(int size) { v_.reserve(size); }                         \
        void resize(int size) { v_.resize(size); }                           \
        void shrink_to_fit() { v_.shrink_to_fit(); }                         \
        void push_back(T &&t) { v_.push_back(std::forward<T>(t)); }          \
        void push_back(const T &t) { v_.push_back(t); }                      \
        const T &front() const { return v_.front(); }                        \
        T &front() { return v_.front(); }                                    \
        const T &back() const { return v_.back(); }                          \
        T &back() { return v_.back(); }                                      \
        void clear() { v_.clear(); }                                         \
        template <class... Args>                                             \
        constexpr T &emplace_back(Args &&... args) {                         \
            v_.emplace_back(std::forward<Args>(args)...);                    \
            return v_.back();                                                \
        }                                                                    \
        template <typename Iter>                                             \
        Iter erase(Iter iter) {                                              \
            return v_.erase(iter);                                           \
        }                                                                    \
        template <typename Iter>                                             \
        Iter erase(Iter first, Iter last) {                                  \
            return v_.erase(first, last);                                    \
        }                                                                    \
        const T *data() const { return v_.data(); }                          \
        int size() const { return v_.size(); }                               \
        T &operator[](const Name##Index index) { return v_[index.value()]; } \
        const T &operator[](const Name##Index index) const {                 \
            return v_[index.value()];                                        \
        }                                                                    \
        Name##IndexRange index_range() const {                               \
            return Name##IndexRange(v_.size());                              \
        }                                                                    \
        Name##IndexRange index_from(int begin) const {                       \
            XCHECK(begin >= 0);                                              \
            return Name##IndexRange(begin, v_.size());                       \
        }                                                                    \
        Name##IndexRange index_to(int end) const {                           \
            XCHECK(end <= v_.size());                                        \
            return Name##IndexRange(0, end);                                 \
        }                                                                    \
        Name##IndexRange index_range(int begin, int end) const {             \
            XCHECK(begin >= 0);                                              \
            XCHECK(end <= v_.size());                                        \
            return Name##IndexRange(begin, end);                             \
        }                                                                    \
        bool valid_index(Name##Index index) const {                          \
            return (index.value() >= 0) && (index.value() < v_.size());      \
        }                                                                    \
        typename std::vector<T, Alloc>::const_iterator begin() const {       \
            return v_.cbegin();                                              \
        }                                                                    \
        typename std::vector<T, Alloc>::const_iterator end() const {         \
            return v_.cend();                                                \
        }                                                                    \
        typename std::vector<T, Alloc>::iterator begin() {                   \
            return v_.begin();                                               \
        }                                                                    \
        typename std::vector<T, Alloc>::iterator end() { return v_.end(); }  \
                                                                             \
     private:                                                                \
        std::vector<T, Alloc> v_;                                            \
    };
