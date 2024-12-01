#include "iterator.hpp"

int
main() {

    static_assert(std::contiguous_iterator<MatrixIterator<int, false>>);
    static_assert(std::contiguous_iterator<MatrixIterator<int, true>>);
}