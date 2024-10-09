#ifndef LAB2_2_ALLOCATOR_HPP
#define LAB2_2_ALLOCATOR_HPP

#include "../signal/signal.hpp"

struct Signals {
    Signal signal;
    int time;
};

class Allocator {
  public:
    Allocator() = default;
    Allocator(int n);
    ~Allocator();

    Allocator(const Allocator&);
    Allocator(Allocator&&) noexcept;

    Allocator& operator=(const Allocator&);
    Allocator& operator=(Allocator&&) noexcept;

    void resize(int);

    int size_ = 0, capacity_ = 0;
    Signals* buffer_ = nullptr;
};

#endif