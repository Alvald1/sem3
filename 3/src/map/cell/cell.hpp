#ifndef CELL_HPP
#define CELL_HPP

#include "../../utilities/position.hpp"
#include <cstddef>

class Cell {
private:
    size_t id;
    Position position;
    bool passability;
    bool busy;
    size_t id_entity;

public:
    // Getters
    Position get_position() const { return position; }
    bool get_passability() const { return passability; }
    bool get_busy() const { return busy; }
    size_t get_id_entity() const { return id_entity; }

    // Setters
    void set_passability(bool value) { passability = value; }
    void set_busy(bool value) { busy = value; }
    void set_id_entity(size_t value) { id_entity = value; }

    // Methods
    bool is_empty() const { return !busy; }
};

#endif // CELL_HPP
