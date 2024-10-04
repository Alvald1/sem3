#include "allocator.hpp"

#include <string>

Allocator::Allocator(int n) {
    size_ = 0;
    capacity_ = n;
    buffer = new char[capacity_];
}

Allocator::~Allocator() { delete[] buffer; }

void
Allocator::expand() {
    // Implementation here
    char* new_buffer = new char[capacity_ + chunk_size];
    std::copy(buffer, buffer + capacity_, new_buffer);
    delete[] buffer;
    buffer = new_buffer;
    capacity_ += chunk_size;
}