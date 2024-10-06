#include "allocator.hpp"

#include <limits>
#include <math.h>
#include <string>

Allocator::Allocator() {
    size_ = 0;
    capacity_ = 0;
    buffer = nullptr;
}

Allocator::Allocator(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Invalid argument");
    }
    size_ = 0;
    capacity_ = n;
    buffer = new Signal[capacity_];
}

Allocator::~Allocator() { delete[] buffer; }

void
Allocator::resize(int n) {
    int new_capacity{}, multyplier{};
    if (n < 0) {
        throw std::invalid_argument("Invalid argument");
    }
    if (n == 0 && size_ == 0) {
        return;
    }
    if (capacity_ == 0) {
        new_capacity = n;
        multyplier = n;
    } else {
        multyplier = std::ceil(double(n + size_) / capacity_);
        if (capacity_ > std::numeric_limits<int>::max() / multyplier) {
            throw std::overflow_error("Capacity overflow");
        }
        new_capacity = capacity_ * multyplier;
    }
    if (multyplier > 1) {
        Signal* new_buffer = new Signal[new_capacity];
        std::copy(buffer, buffer + capacity_, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
        capacity_ = new_capacity;
    }
}