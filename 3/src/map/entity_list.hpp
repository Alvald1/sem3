#ifndef ENTITY_LIST_HPP
#define ENTITY_LIST_HPP

#include <memory>
#include <unordered_map>

#include "cell/cell.hpp"
#include "queue/entity/entity.hpp"

/**
 * @brief Class managing entity-cell mappings
 * 
 * The EntityList class maintains bidirectional mappings between entity IDs
 * and their corresponding cells, facilitating entity tracking and lookup.
 */
class EntityList {
  private:
    std::unordered_map<size_t, std::shared_ptr<Cell>> id_to_cell;
    std::unordered_map<std::shared_ptr<Cell>, size_t, std::hash<std::shared_ptr<Cell>>,
                       std::equal_to<std::shared_ptr<Cell>>>
        cell_to_id;

  public:
    /**
     * @brief Find cell by entity ID
     * @param id Entity identifier
     * @return Pointer to cell or nullptr if not found
     */
    std::shared_ptr<Cell> find_by_id(size_t id) const;

    /**
     * @brief Find entity ID by cell
     * @param cell Shared pointer to cell
     * @return Entity ID or 0 if not found
     */
    size_t find_by_cell(const std::shared_ptr<Cell>& cell) const;

    /**
     * @brief Add or update entity-cell mapping
     * @param id Entity identifier
     * @param cell Shared pointer to cell
     */
    void append(size_t id, const std::shared_ptr<Cell>& cell);

    /**
     * @brief Remove entity and its cell mapping
     * @param id Entity identifier to remove
     */
    void remove(size_t id);

    /**
     * @brief Get ID to cell mapping
     * @return Const reference to ID-cell map
     */
    const std::unordered_map<size_t, std::shared_ptr<Cell>> get_id_to_cell() const;

    /**
     * @brief Get cell to ID mapping
     * @return Const reference to cell-ID map
     */
    const std::unordered_map<std::shared_ptr<Cell>, size_t> get_cell_to_id() const;
};

#endif // ENTITY_LIST_HPP
