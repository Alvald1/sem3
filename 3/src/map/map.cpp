#include "map.hpp"

#include "map/cell/builders/cell_director.hpp"

void
Map::make_map(std::pair<size_t, size_t> new_size) {
    size = new_size;
    matrix.resize(size.first, size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            matrix(i, j) = std::make_shared<Cell>(
                CellDirector::createBasicCell(Position(static_cast<int>(i), static_cast<int>(j))));
        }
    }
}

void
Map::load_from_passability_matrix(const Matrix<bool>& passability_matrix) {
    size = {passability_matrix.get_rows(), passability_matrix.get_cols()};
    matrix.resize(size.first, size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            matrix(i, j) = std::make_shared<Cell>(CellDirector::createBasicCell(
                Position(static_cast<int>(i), static_cast<int>(j)), passability_matrix(i, j)));
        }
    }
}

Matrix<bool>
Map::export_passability_matrix() const {
    Matrix<bool> passability_matrix(size.first, size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            passability_matrix(i, j) = matrix(i, j)->get_passability();
        }
    }

    return passability_matrix;
}

Matrix<int>
Map::export_cell_types_matrix() const {
    Matrix<int> types_matrix(size.first, size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            auto cell = matrix(i, j);
            if (!cell->get_passability()) {
                types_matrix(i, j) = 1; // wall/obstacle
            } else if (cell->get_busy()) {
                types_matrix(i, j) = 2; // occupied cell
            } else {
                types_matrix(i, j) = 0; // empty passable cell
            }
        }
    }

    return types_matrix;
}

Matrix<size_t>
Map::export_entity_ids_matrix() const {
    Matrix<size_t> ids_matrix(size.first, size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            auto cell = matrix(i, j);
            if (cell->get_busy()) {
                ids_matrix(i, j) = cell->get_id_entity();
            } else {
                ids_matrix(i, j) = 0; // 0 indicates no entity
            }
        }
    }

    return ids_matrix;
}

std::shared_ptr<Cell>&
Map::get_cell(const Position& pos) {
    if (pos.get_x() < 0 || static_cast<size_t>(pos.get_x()) >= size.first || pos.get_y() < 0
        || static_cast<size_t>(pos.get_y()) >= size.second) {
        throw std::out_of_range("Position is out of map bounds");
    }
    return matrix(pos.get_x(), pos.get_y());
}

const std::shared_ptr<Cell>&
Map::get_cell(const Position& pos) const {
    if (pos.get_x() < 0 || static_cast<size_t>(pos.get_x()) >= size.first || pos.get_y() < 0
        || static_cast<size_t>(pos.get_y()) >= size.second) {
        throw std::out_of_range("Position is out of map bounds");
    }
    return matrix(pos.get_x(), pos.get_y());
}
