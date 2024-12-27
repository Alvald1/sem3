#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include "utilities/position.hpp"

class CellBuilder;
class EffectCellSpeedBuilder;
class EffectCellRangeBuilder;
class EffectCellHPBuilder;
class EffectCellDamageBuilder;

class Cell {
  private:
    size_t id;
    Position position;
    bool passability;
    bool busy;
    size_t id_entity;
    static size_t next_id; // только объявление

    // Move constructor to private section

    friend class CellBuilder; // This allows CellBuilder to access the private constructor
    friend class EffectCellSpeedBuilder;
    friend class EffectCellRangeBuilder;
    friend class EffectCellHPBuilder;
    friend class EffectCellDamageBuilder;

  protected:
    Cell(Position position, bool passability = true, bool busy = false, size_t id_entity = 0)
        : position(position), passability(passability), busy(busy), id_entity(id_entity) {
        id = next_id++;
    }

  public:
    Cell(const Cell& other)
        : id(other.id), position(other.position), passability(other.passability), busy(other.busy),
          id_entity(other.id_entity) {}

    Cell(Cell&& other) noexcept
        : id(other.id), position(std::move(other.position)), passability(other.passability), busy(other.busy),
          id_entity(other.id_entity) {}

    Cell&
    operator=(const Cell& other) {
        if (this != &other) {
            id = other.id;
            position = other.position;
            passability = other.passability;
            busy = other.busy;
            id_entity = other.id_entity;
        }
        return *this;
    }

    Cell&
    operator=(Cell&& other) noexcept {
        if (this != &other) {
            id = other.id;
            position = std::move(other.position);
            passability = other.passability;
            busy = other.busy;
            id_entity = other.id_entity;
        }
        return *this;
    }

    // Add virtual destructor to make the class polymorphic
    virtual ~Cell() = default;

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
