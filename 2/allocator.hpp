#ifndef LAB2_2_ALLOCATOR_HPP
#define LAB2_2_ALLOCATOR_HPP

#include "signal.hpp"

class Allocator {
  public:
    Allocator(int n);
    ~Allocator();

    void expand();

    int size_, capacity_;
    char* buffer;
};

#endif