#ifndef LAB2_2_ALLOCATOR_HPP
#define LAB2_2_ALLOCATOR_HPP

#include "signal.hpp"

class Allocator {
  public:
    Allocator(int n);
    ~Allocator();

    void resize(int);

    int size_, capacity_;
    Signal* buffer;
};

#endif