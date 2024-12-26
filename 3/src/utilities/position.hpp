#ifndef POSITION_HPP
#define POSITION_HPP

#include "cmath"

class Position {
  private:
    int y;
    int x;

  public:
    Position(int y = 0, int x = 0) : y(y), x(x) {}

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
        return Position(y + other.y, x + other.x);
    }

    bool
    operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] size_t
    manhattan_distance(const Position& other) const {
        return std::abs(x - other.get_x()) + std::abs(y - other.get_y());
    }
};

#endif // POSITION_HPP