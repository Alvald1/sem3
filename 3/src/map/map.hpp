#ifndef MAP_HPP
#define MAP_HPP

#include <utility>
#include "cell/cell.hpp"
#include "../matrix/matrix.hpp"

class Map {
  protected:
    Matrix<Cell> matrix;

  private:
    std::pair<size_t, size_t> size;

  public:
    // Getters and setters for size
    std::pair<size_t, size_t>
    get_size() const {
        return size;
    }

    void
    set_size(std::pair<size_t, size_t> new_size) {
        size = new_size;
    }

    // Map generation function
    void make_map(size_t width, size_t height);
};

#endif // MAP_HPP
