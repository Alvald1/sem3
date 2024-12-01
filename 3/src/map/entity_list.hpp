#ifndef ENTITY_LIST_HPP
#define ENTITY_LIST_HPP

#include <vector>
#include <utility>
#include "cell/cell.hpp"
#include "../queue/entity/entity.hpp"

class EntityList {
private:
    std::vector<std::pair<EntityID, Cell>> list;

public:
    Cell find_by_id(EntityID id) const;
    void append(EntityID id, Cell cell);
    void remove(EntityID id);
};

#endif // ENTITY_LIST_HPP
