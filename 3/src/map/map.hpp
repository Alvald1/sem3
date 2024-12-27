#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>

#include "cell/cell.hpp"
#include "matrix/matrix.hpp"

class Map {
  protected:
    Matrix<std::shared_ptr<Cell>> matrix;

  private:
    std::pair<size_t, size_t> size;

  public:
    const Matrix<std::shared_ptr<Cell>>&
    get_matrix() const {
        return matrix;
    }

    // Getters and setters for size
    std::pair<size_t, size_t>
    get_size() const {
        return size;
    }

    // Map generation function
    void make_map(std::pair<size_t, size_t> size);

    // Load map from passability matrix
    void load_from_passability_matrix(const Matrix<bool>& passability_matrix);

    // Export map data as matrices
    Matrix<bool> export_passability_matrix() const;
    Matrix<int> export_cell_types_matrix() const;

    // Add new method declaration
    Matrix<size_t> export_entity_ids_matrix() const;

    // Generate walls matrix based on size and wall percentage
    Matrix<bool> generate_walls(std::pair<size_t, size_t> size, float wall_percentage);

    // Get cell by position
    std::shared_ptr<Cell>& get_cell(const Position& pos);
    const std::shared_ptr<Cell>& get_cell(const Position& pos) const;
};

#endif // MAP_HPP
