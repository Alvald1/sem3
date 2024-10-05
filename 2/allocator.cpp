#include "allocator.hpp"

#include <limits>
#include <math.h>
#include <string>

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
    if (n < 0) {
        throw std::invalid_argument("Invalid argument");
    }
    if (n == 0 && size_ == 0) {
        return;
    }
    int multyplier = std::ceil(double(n + size_) / capacity_);
    if (capacity_ > std::numeric_limits<int>::max() / multyplier) {
        throw std::overflow_error("Capacity overflow");
    }
    if (multyplier > 1) {
        Signal* new_buffer = new Signal[capacity_ * multyplier];
        std::copy(buffer, buffer + capacity_, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
        capacity_ *= multyplier;
    }
}