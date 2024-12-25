#ifndef POSITION_HPP
#define POSITION_HPP

#include "cmath"

class Position {
  private:
    int x;
    int y;

  public:
    Position(int x = 0, int y = 0) : x(x), y(y) {}

    int
    get_x() const {
        return x;
    }

    int
    get_y() const {
        return y;
    }

    void
    set_x(int new_x) {
        x = new_x;
    }

    void
    set_y(int new_y) {
        y = new_y;
    }

    Position
    operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }

    int
    manhattan_distance(const Position& other) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
};

#endif // POSITION_HPP