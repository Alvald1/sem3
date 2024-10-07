#include "allocator.hpp"

#include <limits>
#include <math.h>
#include <string>

Allocator::Allocator() : size_(1), capacity_(1) { buffer = new Signals[capacity_]; }

Allocator::Allocator(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Invalid argument");
    }
    size_ = 1;
    capacity_ = n + 1;
    buffer = new Signals[capacity_ + 1];
}

Allocator::~Allocator() { delete[] buffer; }

Allocator::Allocator(const Allocator& other) : size_(other.size_), capacity_(other.capacity_) {
    buffer = new Signals[capacity_];
    std::copy(other.buffer, other.buffer + capacity_, buffer);
}

Allocator::Allocator(Allocator&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), buffer(other.buffer) {
    other.buffer = nullptr;
}

void
Allocator::resize(int n) {
    int new_capacity{}, multyplier{};
    if (n < 0) {
        throw std::invalid_argument("Invalid argument");
    }
    multyplier = std::ceil(double(n + size_) / capacity_);
    if (capacity_ > std::numeric_limits<int>::max() / multyplier) {
        throw std::overflow_error("Capacity overflow");
    }
    new_capacity = capacity_ * multyplier;
    if (multyplier > 1) {
        Signals* new_buffer = new Signals[new_capacity];
        std::move(buffer, buffer + capacity_, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
        capacity_ = new_capacity;
    }
}