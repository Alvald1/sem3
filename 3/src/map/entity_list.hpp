#ifndef ENTITY_LIST_HPP
#define ENTITY_LIST_HPP

#include <unordered_map>

#include "cell/cell.hpp"
#include "queue/entity/entity.hpp"

class EntityList {
  private:
    std::unordered_map<size_t, Cell*> id_to_cell;
    std::unordered_map<Cell*, size_t> cell_to_id;

  public:
    Cell* find_by_id(size_t id) const;
    size_t find_by_cell(Cell* cell) const;
    void append(size_t id, Cell* cell);
    void remove(size_t id);
};

#endif // ENTITY_LIST_HPP
