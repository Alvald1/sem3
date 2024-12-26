#ifndef CELL_BUILDER_HPP
#define CELL_BUILDER_HPP

#include "map/cell/cell.hpp"
#include "utilities/position.hpp"

class CellBuilder {
  protected:
    Cell cell;

  public:
    CellBuilder(Position pos) : cell(pos) {}

    CellBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    CellBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    CellBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    [[nodiscard]] Cell
    build() const {
        return cell;
    }
};

#endif // CELL_BUILDER_HPP
