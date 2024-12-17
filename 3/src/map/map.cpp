#include "map.hpp"

void Map::make_map(std::pair<size_t, size_t> new_size) {
    size = new_size;
    matrix.resize(size.first, size.second);
    
    size_t cell_id = 0;
    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            matrix(i, j) = std::make_shared<Cell>(cell_id++, Position(i, j));
        }
    }
}

void Map::load_from_passability_matrix(const Matrix<bool>& passability_matrix) {
    size = {passability_matrix.get_rows(), passability_matrix.get_cols()};
    matrix.resize(size.first, size.second);
    
    size_t cell_id = 0;
    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            matrix(i, j) = std::make_shared<Cell>(cell_id++, Position(i, j), passability_matrix(i, j));
        }
    }
}
