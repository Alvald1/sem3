#ifndef MAP_MATRIX_MATRIX_HPP_
#define MAP_MATRIX_MATRIX_HPP_

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include "iterator.hpp"

template <typename T, bool is_const>
class Iterator; // Forward declaration

template <typename T>
class Matrix {
  private:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    size_type rows_;
    size_type cols_;
    std::shared_ptr<value_type[]> data_;

    void allocate(size_type rows, size_type cols);
    void deallocate();

  public:
    // Type traits

    Matrix();
    Matrix(size_type rows, size_type cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    virtual ~Matrix();

    // Size operations
    inline size_type get_rows() const;
    inline size_type get_cols() const;

    void resize(size_type new_rows, size_type new_cols);

    // Row/Column operations
    void add_row(size_type pos);
    void add_column(size_type pos);
    void delete_row(size_type pos);
    void delete_column(size_type pos);

    // Operators
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    reference operator()(size_type row, size_type col);
    const_reference operator()(size_type row, size_type col) const;

    // Iterator support
    using iterator = MatrixIterator<T, false>;
    using const_iterator = MatrixIterator<T, true>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
};

// Function Definitions

template <typename T>
Matrix<T>::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols) : rows_(rows), cols_(cols) {
    allocate(rows, cols);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    // Shared ownership, no need to copy data
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
    other.rows_ = 0;
    other.cols_ = 0;
}

template <typename T>
Matrix<T>::~Matrix() = default;

template <typename T>
void
Matrix<T>::allocate(size_type rows, size_type cols) {
    data_ = std::shared_ptr<value_type[]>(new value_type[rows * cols](), std::default_delete<value_type[]>());
}

template <typename T>
void
Matrix<T>::deallocate() {
    data_.reset();
}

template <typename T>
inline typename Matrix<T>::size_type
Matrix<T>::get_rows() const {
    return rows_;
}

template <typename T>
inline typename Matrix<T>::size_type
Matrix<T>::get_cols() const {
    return cols_;
}

template <typename T>
void
Matrix<T>::resize(size_type new_rows, size_type new_cols) {
    auto new_data = std::make_unique<value_type[]>(new_rows * new_cols);

    size_type common_rows = std::min(rows_, new_rows);
    size_type common_cols = std::min(cols_, new_cols);
    for (size_type i = 0; i < common_rows; ++i) {
        std::copy(data_.get() + i * cols_, data_.get() + i * cols_ + common_cols, new_data.get() + i * new_cols);
    }

    data_ = std::move(new_data);
    rows_ = new_rows;
    cols_ = new_cols;
}

template <typename T>
void
Matrix<T>::add_row(size_type pos) {
    if (pos > rows_) {
        throw std::out_of_range("Row position out of range");
    }
    resize(rows_ + 1, cols_);
    for (size_type i = rows_ - 1; i > pos; --i) {
        std::copy(data_.get() + (i - 1) * cols_, data_.get() + (i - 1) * cols_ + cols_, data_.get() + i * cols_);
    }
    std::fill(data_.get() + pos * cols_, data_.get() + (pos + 1) * cols_, T());
}

template <typename T>
void
Matrix<T>::add_column(size_type pos) {
    if (pos > cols_) {
        throw std::out_of_range("Column position out of range");
    }
    resize(rows_, cols_ + 1);
    for (size_type i = 0; i < rows_; ++i) {
        std::move_backward(data_.get() + i * cols_ + pos, data_.get() + i * cols_ + cols_ - 1,
                           data_.get() + i * cols_ + cols_);
        data_[i * cols_ + pos] = T();
    }
}

template <typename T>
void
Matrix<T>::delete_row(size_type pos) {
    if (pos >= rows_) {
        throw std::out_of_range("Row position out of range");
    }
    for (size_type i = pos; i < rows_ - 1; ++i) {
        std::copy(data_.get() + (i + 1) * cols_, data_.get() + (i + 1) * cols_ + cols_, data_.get() + i * cols_);
    }
    resize(rows_ - 1, cols_);
}

template <typename T>
void
Matrix<T>::delete_column(size_type pos) {
    if (pos >= cols_) {
        throw std::out_of_range("Column position out of range");
    }
    for (size_type i = 0; i < rows_; ++i) {
        std::move(data_.get() + i * cols_ + pos + 1, data_.get() + (i + 1) * cols_,
                  data_.get() + i * (cols_ - 1) + pos);
    }
    resize(rows_, cols_ - 1);
}

template <typename T>
typename Matrix<T>::reference
Matrix<T>::operator()(size_type row, size_type col) {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + col];
}

template <typename T>
typename Matrix<T>::const_reference
Matrix<T>::operator()(size_type row, size_type col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + col];
}

template <typename T>
Matrix<T>&
Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        data_ = other.data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = std::move(other.data_);
        other.rows_ = 0;
        other.cols_ = 0;
    }
    return *this;
}

template <typename T>
typename Matrix<T>::iterator
Matrix<T>::begin() {
    return iterator(data_.get());
}

template <typename T>
typename Matrix<T>::iterator
Matrix<T>::end() {
    return iterator(data_.get() + rows_ * cols_);
}

template <typename T>
typename Matrix<T>::const_iterator
Matrix<T>::begin() const {
    return const_iterator(data_.get());
}

template <typename T>
typename Matrix<T>::const_iterator
Matrix<T>::end() const {
    return const_iterator(data_.get() + rows_ * cols_);
}

template <typename T>
typename Matrix<T>::const_iterator
Matrix<T>::cbegin() const {
    return const_iterator(data_.get());
}

template <typename T>
typename Matrix<T>::const_iterator
Matrix<T>::cend() const {
    return const_iterator(data_.get() + rows_ * cols_);
}

#endif // MAP_MATRIX_MATRIX_HPP_
