#include "entity_list.hpp"

std::shared_ptr<Cell>
EntityList::find_by_id(size_t id) const {
    auto it = id_to_cell.find(id);
    if (it != id_to_cell.end()) {
        return it->second;
    }
    return nullptr;
}

size_t
EntityList::find_by_cell(const std::shared_ptr<Cell>& cell) const {
    auto it = cell_to_id.find(cell);
    if (it != cell_to_id.end()) {
        return it->second;
    }
    return 0;
}

void
EntityList::append(size_t id, const std::shared_ptr<Cell>& cell) {
    auto existing_it = id_to_cell.find(id);
    if (existing_it != id_to_cell.end()) {
        cell_to_id.erase(existing_it->second);
    }

    // Append new mapping
    id_to_cell[id] = cell;
    cell_to_id[cell] = id;
}

void
EntityList::remove(size_t id) {
    auto it = id_to_cell.find(id);
    if (it != id_to_cell.end()) {
        cell_to_id.erase(it->second);
        id_to_cell.erase(it);
    }
}
