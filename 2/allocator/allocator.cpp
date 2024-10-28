/**
 * @file allocator.cpp
 * @brief Реализация класса Allocator для управления динамическим массивом объектов Signals.
 */

#include "allocator.hpp"
#include <cmath>
#include <limits>
#include <string>

/**
 * @brief Конструктор Allocator, инициализирующий массив с заданной емкостью.
 * 
 * @param n Начальная емкость массива.
 * @throws std::invalid_argument Если n меньше или равно нулю.
 */
Allocator::Allocator(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Invalid argument");
    }
    size_ = 0;
    capacity_ = n;
    buffer_ = new Signals[capacity_];
}

/**
 * @brief Деструктор, освобождающий выделенную память.
 */
Allocator::~Allocator() { delete[] buffer_; }

/**
 * @brief Конструктор копирования, создающий глубокую копию другого объекта Allocator.
 * 
 * @param other Другой объект Allocator для копирования.
 */
Allocator::Allocator(const Allocator& other) : size_(other.size_), capacity_(other.capacity_) {
    buffer_ = new Signals[capacity_];
    std::copy(other.buffer_, other.buffer_ + size_, buffer_);
}

/**
 * @brief Конструктор перемещения, перемещающий данные из другого объекта Allocator.
 * 
 * @param other Другой объект Allocator для перемещения.
 */
Allocator::Allocator(Allocator&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), buffer_(other.buffer_) {
    other.buffer_ = nullptr;
}

/**
 * @brief Оператор присваивания копированием.
 * 
 * @param other Другой объект Allocator для копирования.
 * @return Ссылка на текущий объект после присваивания.
 */
Allocator&
Allocator::operator=(const Allocator& other) {
    if (this != &other) {
        Signals* new_buffer_ = new Signals[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        delete[] buffer_;
        buffer_ = new_buffer_;
        std::copy(other.buffer_, other.buffer_ + size_, buffer_);
    }
    return *this;
}

/**
 * @brief Оператор присваивания перемещением.
 * 
 * @param other Другой объект Allocator для перемещения.
 * @return Ссылка на текущий объект после присваивания.
 */
Allocator&
Allocator::operator=(Allocator&& other) noexcept {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(buffer_, other.buffer_);
    return *this;
}

/**
 * @brief Изменяет размер массива.
 * 
 * Если новый размер превышает текущую емкость, выделяет новую память и копирует элементы.
 * 
 * @param n Новый размер массива.
 * @throws std::invalid_argument Если n меньше или равно нулю.
 * @throws std::overflow_error Если новый размер превышает допустимый предел.
 */
void
Allocator::resize(int n) {
    int new_capacity{}, multiplier{};
    if (n <= 0) {
        throw std::invalid_argument("Invalid argument");
    }
    if (capacity_ == 0) {
        new_capacity = n;
    } else {
        multiplier = std::ceil(double(n + size_) / capacity_);
        if (capacity_ > std::numeric_limits<int>::max() / multiplier) {
            throw std::overflow_error("Capacity overflow");
        }
        new_capacity = capacity_ * multiplier;
    }
    if (capacity_ == 0 || multiplier > 1) {
        Signals* new_buffer_ = new Signals[new_capacity];
        std::move(buffer_, buffer_ + size_, new_buffer_);
        delete[] buffer_;
        buffer_ = new_buffer_;
        capacity_ = new_capacity;
    }
}
