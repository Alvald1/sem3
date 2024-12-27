#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>

#include "cell/cell.hpp"
#include "matrix/matrix.hpp"

/**
 * @brief Class representing a 2D game map
 * 
 * The Map class manages a 2D grid of cells, handling map generation,
 * cell access, and various map data export functions.
 */
class Map {
  protected:
    Matrix<std::shared_ptr<Cell>> matrix;

  private:
    std::pair<size_t, size_t> size;

  public:
    /**
     * @brief Get const reference to the underlying matrix
     * @return Const reference to the matrix of cells
     */
    const Matrix<std::shared_ptr<Cell>>& get_matrix() const;

    /**
     * @brief Get mutable reference to the underlying matrix
     * @return Mutable reference to the matrix of cells
     */
    Matrix<std::shared_ptr<Cell>>& get_matrix();

    /**
     * @brief Get the map dimensions
     * @return Pair containing rows and columns count
     */
    std::pair<size_t, size_t> get_size() const;

    /**
     * @brief Generate a new map with given dimensions
     * @param size Pair containing desired rows and columns count
     */
    void make_map(std::pair<size_t, size_t> size);

    /**
     * @brief Load map from a boolean passability matrix
     * @param passability_matrix Matrix indicating which cells are passable
     */
    void load_from_passability_matrix(const Matrix<bool>& passability_matrix);

    /**
     * @brief Export map passability data
     * @return Matrix of boolean values indicating cell passability
     */
    Matrix<bool> export_passability_matrix() const;

    /**
     * @brief Export cell types as integer matrix
     * @return Matrix where 0=empty, 1=wall, 2=occupied
     */
    Matrix<int> export_cell_types_matrix() const;

    /**
     * @brief Export entity IDs as matrix
     * @return Matrix containing entity IDs (0 for empty cells)
     */
    Matrix<size_t> export_entity_ids_matrix() const;

    /**
     * @brief Generate walls matrix with given density
     * @param size Map dimensions
     * @param wall_percentage Percentage of cells to be walls (0.0 to 1.0)
     * @return Boolean matrix where false indicates wall presence
     */
    Matrix<bool> generate_walls(std::pair<size_t, size_t> size, float wall_percentage);

    /**
     * @brief Get cell at specified position
     * @param pos Position coordinates
     * @return Reference to cell pointer
     * @throws std::out_of_range if position is invalid
     */
    std::shared_ptr<Cell>& get_cell(const Position& pos);

    /**
     * @brief Get const cell at specified position
     * @param pos Position coordinates
     * @return Const reference to cell pointer
     * @throws std::out_of_range if position is invalid
     */
    const std::shared_ptr<Cell>& get_cell(const Position& pos) const;
};

#endif // MAP_HPP
