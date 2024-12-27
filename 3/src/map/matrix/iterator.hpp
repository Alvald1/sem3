#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>

template <typename T>
class Matrix; // Forward declaration

/**
 * @brief Iterator class for Matrix container
 * @tparam T Type of elements in the Matrix
 * @tparam is_const Boolean flag for const/non-const iterator
 */
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

    /** @brief Default constructor creating a null iterator */
    MatrixIterator() : elem_(nullptr) {};

    /**
     * @brief Constructs iterator pointing to specific element
     * @param elem Pointer to the matrix element
     */
    MatrixIterator(elem_ptr_t elem) : elem_(elem) {};

    /**
     * @brief Converting constructor
     * @tparam other_const Const-ness of the source iterator
     * @param o Source iterator
     */
    template <bool other_const>
    MatrixIterator(MatrixIterator<T, other_const>& o) noexcept
        requires(is_const >= other_const)
        : elem_(o.elem_){};

    /**
     * @brief Converting assignment operator
     * @tparam other_const Const-ness of the source iterator
     * @param o Source iterator
     * @return Reference to this iterator
     */
    template <bool other_const>
    MatrixIterator&
    operator=(const MatrixIterator<T, other_const>& o) noexcept
        requires(is_const >= other_const)
    {
        elem_ = o.elem_;
        return *this;
    }

    /**
     * @brief Pre-increment operator
     * @return Reference to this iterator
     */
    MatrixIterator&
    operator++() noexcept {
        ++elem_;
        return *this;
    }

    /**
     * @brief Post-increment operator
     * @return Copy of the iterator before increment
     */
    MatrixIterator
    operator++(int) noexcept {
        MatrixIterator res(elem_);
        ++elem_;
        return res;
    }

    /**
     * @brief Dereference operator
     * @return Reference to the element pointed by the iterator
     */
    reference
    operator*() const noexcept {
        return *elem_;
    }

    /**
     * @brief Arrow operator
     * @return Pointer to the element pointed by the iterator
     */
    pointer
    operator->() const noexcept {
        return elem_;
    }

    /**
     * @brief Equality comparison operator
     * @tparam other_const Const-ness of the other iterator
     * @param o Other iterator
     * @return True if both iterators point to the same element, false otherwise
     */
    template <bool other_const>
    bool
    operator==(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ == o.elem_;
    }

    /**
     * @brief Pre-decrement operator
     * @return Reference to this iterator
     */
    MatrixIterator&
    operator--() noexcept {
        --elem_;
        return *this;
    }

    /**
     * @brief Post-decrement operator
     * @return Copy of the iterator before decrement
     */
    MatrixIterator
    operator--(int) noexcept {
        MatrixIterator res(elem_);
        --elem_;
        return res;
    }

    /**
     * @brief Less-than comparison operator
     * @tparam other_const Const-ness of the other iterator
     * @param o Other iterator
     * @return True if this iterator points to an element before the other iterator, false otherwise
     */
    template <bool other_const>
    bool
    operator<(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ < o.elem_;
    }

    /**
     * @brief Greater-than comparison operator
     * @tparam other_const Const-ness of the other iterator
     * @param o Other iterator
     * @return True if this iterator points to an element after the other iterator, false otherwise
     */
    template <bool other_const>
    bool
    operator>(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ > o.elem_;
    }

    /**
     * @brief Less-than-or-equal-to comparison operator
     * @tparam other_const Const-ness of the other iterator
     * @param o Other iterator
     * @return True if this iterator points to an element before or at the same position as the other iterator, false otherwise
     */
    template <bool other_const>
    bool
    operator<=(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ <= o.elem_;
    }

    /**
     * @brief Greater-than-or-equal-to comparison operator
     * @tparam other_const Const-ness of the other iterator
     * @param o Other iterator
     * @return True if this iterator points to an element after or at the same position as the other iterator, false otherwise
     */
    template <bool other_const>
    bool
    operator>=(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ >= o.elem_;
    }

    /**
     * @brief Difference operator
     * @tparam other_const Const-ness of the other iterator
     * @param o Other iterator
     * @return Difference in positions between this iterator and the other iterator
     */
    template <bool other_const>
    difference_t
    operator-(const MatrixIterator<T, other_const>& o) const noexcept {
        return elem_ - o.elem_;
    }

    /**
     * @brief Addition operator
     * @param n Number of elements to advance
     * @return Iterator advanced by n elements
     */
    MatrixIterator
    operator+(difference_t n) const noexcept {
        MatrixIterator res(elem_ + n);
        return res;
    }

    /**
     * @brief Addition assignment operator
     * @param n Number of elements to advance
     * @return Reference to this iterator
     */
    MatrixIterator&
    operator+=(difference_t n) noexcept {
        elem_ += n;
        return *this;
    }

    /**
     * @brief Subtraction operator
     * @param n Number of elements to retreat
     * @return Iterator retreated by n elements
     */
    MatrixIterator
    operator-(difference_t n) const noexcept {
        MatrixIterator res(elem_ - n);
        return res;
    }

    /**
     * @brief Subtraction assignment operator
     * @param n Number of elements to retreat
     * @return Reference to this iterator
     */
    MatrixIterator&
    operator-=(difference_t n) noexcept {
        elem_ -= n;
        return *this;
    }

    /**
     * @brief Subscript operator
     * @param n Index of the element
     * @return Reference to the element at index n
     */
    reference
    operator[](difference_t n) const {
        return elem_[n];
    }

    /**
     * @brief Addition operator for difference and iterator
     * @tparam other_const Const-ness of the iterator
     * @param n Number of elements to advance
     * @param o Iterator to be advanced
     * @return Iterator advanced by n elements
     */
    template <bool other_const>
    friend MatrixIterator
    operator+(difference_t n, const MatrixIterator<T, other_const>& o) {
        return MatrixIterator(o.elem_ + n);
    }
};

#endif // MATRIX_ITERATOR_HPP