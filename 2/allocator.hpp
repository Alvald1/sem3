#ifndef LAB2_2_ALLOCATOR_HPP
#define LAB2_2_ALLOCATOR_HPP

class Allocator {
  public:
    Allocator(int n);
    ~Allocator();

    void expand();

    int size_, capacity_;
    char* buffer;
    const int chunk_size = 8;
};

#endif