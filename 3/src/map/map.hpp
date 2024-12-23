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
    // Add getter for matrix
    Matrix<std::shared_ptr<Cell>>&
    get_matrix() {
        return matrix;
    }

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

    // Replace cell at given position with new cell
    template <typename CellType>
    void replace_cell(std::shared_ptr<CellType> new_cell);

    // Export map data as matrices
    Matrix<bool> export_passability_matrix() const;
    Matrix<int> export_cell_types_matrix() const;
};

template <typename CellType>
void
Map::replace_cell(std::shared_ptr<CellType> new_cell) {
    if (dynamic_cast<Cell*>(new_cell.get()) == nullptr) {
        throw std::invalid_argument("Invalid cell type: must be derived from Cell");
    }

    Position pos = new_cell->get_position();
    if (pos.get_x() < 0 || pos.get_y() < 0 || static_cast<size_t>(pos.get_x()) >= size.first
        || static_cast<size_t>(pos.get_y()) >= size.second) {
        throw std::out_of_range("Cell position out of range");
    }

    matrix(static_cast<size_t>(pos.get_x()), static_cast<size_t>(pos.get_y())) = new_cell;
}

#endif // MAP_HPP
