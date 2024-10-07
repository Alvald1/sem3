#ifndef LAB2_2_ALLOCATOR_HPP
#define LAB2_2_ALLOCATOR_HPP

#include "../signal/signal.hpp"

typedef struct _signals {
    Signal signal;
    int time;
} Signals;

class Allocator {
  public:
    Allocator();
    Allocator(int n);
    ~Allocator();

    Allocator(const Allocator&);
    Allocator(Allocator&&) noexcept;

    Allocator& operator=(const Allocator&);
    Allocator& operator=(Allocator&&) noexcept;

    void resize(int);

    int size_, capacity_;
    Signals* buffer;
};

#endif