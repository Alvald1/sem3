#ifndef ENTITY_LIST_HPP
#define ENTITY_LIST_HPP

#include <memory>
#include <unordered_map>

#include "cell/cell.hpp"
#include "queue/entity/entity.hpp"

class EntityList {
  private:
    std::unordered_map<size_t, std::shared_ptr<Cell>> id_to_cell;
    std::unordered_map<std::shared_ptr<Cell>, size_t> cell_to_id;

  public:
    std::shared_ptr<Cell> find_by_id(size_t id) const;
    size_t find_by_cell(const std::shared_ptr<Cell>& cell) const;
    void append(size_t id, const std::shared_ptr<Cell>& cell);
    void remove(size_t id);
};

#endif // ENTITY_LIST_HPP
