#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>

template <typename T>
class Matrix; // Forward declaration

template <typename T, bool is_const = false>
class MatrixIterator {
  private:
    using elem_ptr_t = std::conditional_t<is_const, const T, T>*;

    elem_ptr_t elem_;

  public:
    using value_t = T;
    using difference_t = ptrdiff_t;
    using pointer = std::conditional_t<is_const, const T, T>*;
    using reference = std::conditional_t<is_const, const T, T>&;
    using iterator_category = std::contiguous_iterator_tag;

    friend Matrix<T>;
    friend MatrixIterator<T, !is_const>;

    MatrixIterator() : elem_(nullptr) {};

    MatrixIterator(elem_ptr_t elem) : elem_(elem) {};

    template <bool other_const>
    MatrixIterator(MatrixIterator<T, other_const>& o) noexcept
        requires(is_const >= other_const)
        : elem_(o.elem_){};

    template <bool other_const>
    MatrixIterator&
    operator=(const MatrixIterator<T, other_const>& o) noexcept
        requires(is_const >= other_const)
    {
        elem_ = o.elem_;
        return *this;
    }

    MatrixIterator&
    operator++() noexcept {
        ++elem_;
        return *this;
    }

    MatrixIterator
    operator++(int) noexcept {
        MatrixIterator res(elem_);
        ++elem_;
        return res;
    }

    reference
    operator*() const noexcept {
        return *elem_;
    }

    pointer
    operator->() const noexcept {
        return elem_;
    }

    template <bool other_const>
    bool
    operator==(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ == o.elem_;
    }

    MatrixIterator&
    operator--() noexcept {
        --elem_;
        return *this;
    }

    MatrixIterator
    operator--(int) noexcept {
        MatrixIterator res(elem_);
        --elem_;
        return res;
    }

    template <bool other_const>
    bool
    operator<(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ < o.elem_;
    }

    template <bool other_const>
    bool
    operator>(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ > o.elem_;
    }

    template <bool other_const>
    bool
    operator<=(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ <= o.elem_;
    }

    template <bool other_const>
    bool
    operator>=(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ >= o.elem_;
    }

    template <bool other_const>
    difference_t
    operator-(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ - o.elem_;
    }

    MatrixIterator
    operator+(difference_t n) const noexcept {
        MatrixIterator res(elem_ + n);
        return res;
    }

    MatrixIterator&
    operator+=(difference_t n) noexcept {
        elem_ += n;
        return *this;
    }

    MatrixIterator
    operator-(difference_t n) const noexcept {
        MatrixIterator res(elem_ - n);
        return res;
    }

    MatrixIterator&
    operator-=(difference_t n) noexcept {
        elem_ -= n;
        return *this;
    }

    reference
    operator[](difference_t n) const {
        return elem_[n];
    }

    template <bool other_const>
    friend MatrixIterator
    operator+(difference_t n, const MatrixIterator<T, other_const>& o) {
        return MatrixIterator(o.elem_ + n);
    }
};

#endif // MATRIX_ITERATOR_HPP