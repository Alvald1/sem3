#ifndef MAP_MATRIX_MATRIX_HPP_
#define MAP_MATRIX_MATRIX_HPP_

#include <algorithm>
#include <cstddef>
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
    pointer data_;

    void allocate(size_type rows, size_type cols);
    void deallocate();

  public:
    // Type traits
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    Matrix() : rows_(0), cols_(0), data_(nullptr) {}

    Matrix(size_type rows, size_type cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    // Size operations
    size_type
    get_rows() const {
        return rows_;
    }

    size_type
    get_cols() const {
        return cols_;
    }

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

    iterator
    begin() {
        return iterator(data_);
    }

    iterator
    end() {
        return iterator(data_ + rows_ * cols_);
    }

    const_iterator
    begin() const {
        return const_iterator(data_);
    }

    const_iterator
    end() const {
        return const_iterator(data_ + rows_ * cols_);
    }

    const_iterator
    cbegin() const {
        return const_iterator(data_);
    }

    const_iterator
    cend() const {
        return const_iterator(data_ + rows_ * cols_);
    }
};

template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols) : rows_(rows), cols_(cols) {
    allocate(rows, cols);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    allocate(rows_, cols_);
    std::copy(other.data_, other.data_ + rows_ * cols_, data_);
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

template <typename T>
void
Matrix<T>::allocate(size_type rows, size_type cols) {
    data_ = new value_type[rows * cols]();
}

template <typename T>
void
Matrix<T>::deallocate() {
    delete[] data_;
    data_ = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {
    deallocate();
}

template <typename T>
Matrix<T>&
Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        pointer new_data = new value_type[other.rows_ * other.cols_];
        std::copy(other.data_, other.data_ + other.rows_ * other.cols_, new_data);

        deallocate();
        data_ = new_data;
        rows_ = other.rows_;
        cols_ = other.cols_;
    }
    return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        deallocate();
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;

        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

template <typename T>
reference
Matrix<T>::operator()(size_type row, size_type col) {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + col];
}

template <typename T>
const_reference
Matrix<T>::operator()(size_type row, size_type col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + col];
}

template <typename T>
void
Matrix<T>::resize(size_type new_rows, size_type new_cols) {
    pointer new_data = new value_type[new_rows * new_cols]();

    for (size_type i = 0; i < std::min(rows_, new_rows); ++i) {
        for (size_type j = 0; j < std::min(cols_, new_cols); ++j) {
            new_data[i * new_cols + j] = data_[i * cols_ + j];
        }
    }

    delete[] data_;
    data_ = new_data;
    rows_ = new_rows;
    cols_ = new_cols;
}

#endif // MAP_MATRIX_MATRIX_HPP_
