#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include "../../utilities/position.hpp"

class Cell {
  private:
    size_t id;
    Position position;
    bool passability;
    bool busy;
    size_t id_entity;

  public:
    // Add virtual destructor to make the class polymorphic
    virtual ~Cell() = default;

    // Constructors
    Cell(size_t id, Position position, bool passability = true, bool busy = false, size_t id_entity = 0)
        : id(id), position(position), passability(passability), busy(busy), id_entity(id_entity) {}

    // Getters
    inline Position
    get_position() const {
        return position;
    }

    inline bool
    get_passability() const {
        return passability;
    }

    inline bool
    get_busy() const {
        return busy;
    }

    inline size_t
    get_id_entity() const {
        return id_entity;
    }

    // Add getter for id
    inline size_t
    get_id() const {
        return id;
    }

    // Setters
    inline void
    set_passability(bool value) {
        passability = value;
    }

    inline void
    set_busy(bool value) {
        busy = value;
    }

    inline void
    set_id_entity(size_t value) {
        id_entity = value;
    }

    // Methods
    inline bool
    is_empty() const {
        return !busy;
    }
};

#endif // CELL_HPP
