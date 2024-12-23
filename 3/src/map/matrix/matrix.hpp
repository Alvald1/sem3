#ifndef MAP_MATRIX_MATRIX_HPP_
#define MAP_MATRIX_MATRIX_HPP_

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>

#include "iterator.hpp"

/**
 * @brief A 2D matrix container class
 * @tparam T Type of elements stored in the matrix
 */
template <typename T>
class Matrix {
  private:
    using value_t = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_t = std::size_t;
    using difference_t = std::ptrdiff_t;

    size_t rows_;
    size_t cols_;
    std::shared_ptr<value_t[]> data_;

    /**
     * @brief Allocates memory for matrix data
     * @param rows Number of rows
     * @param cols Number of columns
     */
    void allocate(size_t rows, size_t cols);

    /** @brief Deallocates matrix memory */
    void deallocate();

  public:
    // Type traits

    /** @brief Default constructor creating empty matrix */
    Matrix();

    /**
     * @brief Constructor creating matrix of specified size
     * @param rows Number of rows
     * @param cols Number of columns
     */
    Matrix(size_t rows, size_t cols);

    /**
     * @brief Constructor creating matrix of specified size with initial value
     * @param rows Number of rows
     * @param cols Number of columns
     * @param initial_value Initial value for all elements
     */
    Matrix(size_t rows, size_t cols, const T& initial_value);

    /**
     * @brief Copy constructor
     * @param other Matrix to copy from
     */
    Matrix(const Matrix& other);

    /**
     * @brief Move constructor
     * @param other Matrix to move from
     */
    Matrix(Matrix&& other) noexcept;

    /** @brief Virtual destructor */
    virtual ~Matrix();

    /**
     * @brief Gets number of rows
     * @return Number of rows in matrix
     */
    inline size_t get_rows() const;

    /**
     * @brief Gets number of columns
     * @return Number of columns in matrix
     */
    inline size_t get_cols() const;

    /**
     * @brief Resizes matrix to new dimensions
     * @param new_rows New number of rows
     * @param new_cols New number of columns
     */
    void resize(size_t new_rows, size_t new_cols);

    /**
     * @brief Adds a new row at specified position
     * @param pos Position to insert row
     * @throw std::out_of_range if position is invalid
     */
    void add_row(size_t pos);

    /**
     * @brief Adds a new column at specified position
     * @param pos Position to insert column
     * @throw std::out_of_range if position is invalid
     */
    void add_column(size_t pos);

    /**
     * @brief Deletes row at specified position
     * @param pos Position of row to delete
     * @throw std::out_of_range if position is invalid
     */
    void delete_row(size_t pos);

    /**
     * @brief Deletes column at specified position
     * @param pos Position of column to delete
     * @throw std::out_of_range if position is invalid
     */
    void delete_column(size_t pos);

    // Operators
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    reference operator()(size_t row, size_t col);
    const_reference operator()(size_t row, size_t col) const;

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
Matrix<T>::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    allocate(rows, cols);
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T& initial_value) : rows_(rows), cols_(cols) {
    allocate(rows, cols);
    std::fill(data_.get(), data_.get() + rows * cols, initial_value);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    // Shared ownership, no need to copy data
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
    // Set the source matrix to empty state
    other.rows_ = 0;
    other.cols_ = 0;
    // Note: data_ is already moved, no need to clear it
}

template <typename T>
Matrix<T>::~Matrix() = default;

template <typename T>
void
Matrix<T>::allocate(size_t rows, size_t cols) {
    data_ = std::shared_ptr<value_t[]>(new value_t[rows * cols]());
}

template <typename T>
void
Matrix<T>::deallocate() {
    data_.reset();
}

template <typename T>
inline typename Matrix<T>::size_t
Matrix<T>::get_rows() const {
    return rows_;
}

template <typename T>
inline typename Matrix<T>::size_t
Matrix<T>::get_cols() const {
    return cols_;
}

template <typename T>
void
Matrix<T>::resize(size_t new_rows, size_t new_cols) {
    auto new_data = std::make_unique<value_t[]>(new_rows * new_cols);

    size_t common_rows = std::min(rows_, new_rows);
    size_t common_cols = std::min(cols_, new_cols);
    for (size_t i = 0; i < common_rows; ++i) {
        std::copy(data_.get() + i * cols_, data_.get() + i * cols_ + common_cols, new_data.get() + i * new_cols);
    }

    data_ = std::move(new_data);
    rows_ = new_rows;
    cols_ = new_cols;
}

template <typename T>
void
Matrix<T>::add_row(size_t pos) {
    if (pos > rows_) {
        throw std::out_of_range("Row position out of range");
    }
    resize(rows_ + 1, cols_);
    for (size_t i = rows_ - 1; i > pos; --i) {
        std::copy(data_.get() + (i - 1) * cols_, data_.get() + (i - 1) * cols_ + cols_, data_.get() + i * cols_);
    }
    std::fill(data_.get() + pos * cols_, data_.get() + (pos + 1) * cols_, T());
}

template <typename T>
void
Matrix<T>::add_column(size_t pos) {
    if (pos > cols_) {
        throw std::out_of_range("Column position out of range");
    }
    resize(rows_, cols_ + 1);
    for (size_t i = 0; i < rows_; ++i) {
        std::move_backward(data_.get() + i * cols_ + pos, data_.get() + i * cols_ + cols_ - 1,
                           data_.get() + i * cols_ + cols_);
        data_[i * cols_ + pos] = T();
    }
}

template <typename T>
void
Matrix<T>::delete_row(size_t pos) {
    if (pos >= rows_) {
        throw std::out_of_range("Row position out of range");
    }
    for (size_t i = pos; i < rows_ - 1; ++i) {
        std::copy(data_.get() + (i + 1) * cols_, data_.get() + (i + 1) * cols_ + cols_, data_.get() + i * cols_);
    }
    resize(rows_ - 1, cols_);
}

template <typename T>
void
Matrix<T>::delete_column(size_t pos) {
    if (pos >= cols_) {
        throw std::out_of_range("Column position out of range");
    }
    for (size_t i = 0; i < rows_; ++i) {
        std::move(data_.get() + i * cols_ + pos + 1, data_.get() + (i + 1) * cols_,
                  data_.get() + i * (cols_ - 1) + pos);
    }
    resize(rows_, cols_ - 1);
}

template <typename T>
typename Matrix<T>::reference
Matrix<T>::operator()(size_t row, size_t col) {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + col];
}

template <typename T>
typename Matrix<T>::const_reference
Matrix<T>::operator()(size_t row, size_t col) const {
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
Matrix<T>&
Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        rows_ = other.rows_;
        cols_ = other.cols_;

        // Reset the moved-from object
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
