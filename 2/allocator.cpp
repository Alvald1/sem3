#include "allocator.hpp"

#include <string>

Allocator::Allocator(int n) {
    size_ = 0;
    capacity_ = n;
    buffer = new Signal[capacity_];
}

Allocator::~Allocator() { delete[] buffer; }

void
Allocator::expand() {
    // Implementation here
    Signal* new_buffer = new Signal[capacity_ * 2];
    std::copy(buffer, buffer + capacity_, new_buffer);
    delete[] buffer;
    buffer = new_buffer;
    capacity_ *= 2;
}