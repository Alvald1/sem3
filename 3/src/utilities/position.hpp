#ifndef POSITION_HPP
#define POSITION_HPP

#include "cmath"

/**
 * @brief Represents a 2D position in the game grid
 */
class Position {
  private:
    int y; ///< Y-coordinate (row)
    int x; ///< X-coordinate (column)

  public:
    /**
     * @brief Constructs a position
     * @param y Y-coordinate (default: 0)
     * @param x X-coordinate (default: 0)
     */
    Position(int y = 0, int x = 0) : y(y), x(x) {}

    /**
     * @brief Gets the X-coordinate
     * @return X-coordinate value
     */
    int
    get_x() const {
        return x;
    }

    /**
     * @brief Gets the Y-coordinate
     * @return Y-coordinate value
     */
    int
    get_y() const {
        return y;
    }

    /**
     * @brief Sets the X-coordinate
     * @param new_x New X-coordinate value
     */
    void
    set_x(int new_x) {
        x = new_x;
    }

    /**
     * @brief Sets the Y-coordinate
     * @param new_y New Y-coordinate value
     */
    void
    set_y(int new_y) {
        y = new_y;
    }

    /**
     * @brief Adds two positions
     * @param other Position to add
     * @return New position with summed coordinates
     */
    Position
    operator+(const Position& other) const {
        return Position(y + other.y, x + other.x);
    }

    /**
     * @brief Compares two positions for equality
     * @param other Position to compare with
     * @return True if positions are equal, false otherwise
     */
    bool
    operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    /**
     * @brief Calculates Manhattan distance to another position
     * @param other Target position
     * @return Manhattan distance between positions
     */
    [[nodiscard]] size_t
    manhattan_distance(const Position& other) const {
        return std::abs(x - other.get_x()) + std::abs(y - other.get_y());
    }
};

#endif // POSITION_HPP