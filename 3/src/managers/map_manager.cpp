#include "map_manager.hpp"

#include "queue/entity/troop/base_troop.hpp"

MapManager::MoveResult
MapManager::move_entity(size_t id, Position delta) {
    Cell* current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        return MoveResult::ENTITY_NOT_FOUND;
    }

    Position curr_pos = current_cell->get_position();
    Position new_pos(curr_pos.get_x() + delta.get_x(), curr_pos.get_y() + delta.get_y());

    // Check bounds first to avoid unnecessary checks
    if (new_pos.get_x() < 0 || new_pos.get_y() < 0 || static_cast<size_t>(new_pos.get_x()) >= get_size().first
        || static_cast<size_t>(new_pos.get_y()) >= get_size().second) {
        return MoveResult::OUT_OF_BOUNDS;
    }

    // Use can_move_entity for complete validation
    if (!can_move_entity(id, delta)) {
        // Need to determine specific reason for failure
        if (!is_cell_passable(new_pos)) {
            return MoveResult::CELL_NOT_PASSABLE;
        }
        return MoveResult::CELL_OCCUPIED;
    }

    // Get target cell and perform the move
    Cell* target_cell = matrix(static_cast<size_t>(new_pos.get_x()), static_cast<size_t>(new_pos.get_y())).get();

    // Update cells
    current_cell->set_busy(false);
    current_cell->set_id_entity(0);
    target_cell->set_busy(true);
    target_cell->set_id_entity(id);

    // Update entity location in entity list
    entities_.remove(id);
    entities_.append(id, target_cell);

    return MoveResult::SUCCESS;
}

bool
MapManager::is_cell_occupied(Position pos) const {
    // Check if position is within bounds
    if (pos.get_x() < 0 || pos.get_y() < 0 || static_cast<size_t>(pos.get_x()) >= get_size().first
        || static_cast<size_t>(pos.get_y()) >= get_size().second) {
        return false;
    }

    // Get cell and check if it's occupied
    Cell* cell = matrix(static_cast<size_t>(pos.get_x()), static_cast<size_t>(pos.get_y())).get();
    return !cell->is_empty();
}

bool
MapManager::is_cell_passable(Position pos) const {
    // Check if position is within bounds
    if (pos.get_x() < 0 || pos.get_y() < 0 || static_cast<size_t>(pos.get_x()) >= get_size().first
        || static_cast<size_t>(pos.get_y()) >= get_size().second) {
        return false;
    }

    // Get cell and check if it's passable
    Cell* cell = matrix(static_cast<size_t>(pos.get_x()), static_cast<size_t>(pos.get_y())).get();
    return cell->get_passability();
}

bool
MapManager::can_move_entity(size_t id, Position delta) const {
    Cell* current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        return false;
    }

    Position curr_pos = current_cell->get_position();
    Position new_pos(curr_pos.get_x() + delta.get_x(), curr_pos.get_y() + delta.get_y());

    return is_cell_passable(new_pos) && !is_cell_occupied(new_pos);
}

bool
MapManager::can_entity_act(size_t id, Position delta) const {
    Cell* current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        return false;
    }

    Position curr_pos = current_cell->get_position();
    Position target_pos(curr_pos.get_x() + delta.get_x(), curr_pos.get_y() + delta.get_y());

    return is_cell_passable(target_pos);
}

bool
MapManager::add_entity(size_t id, Position pos) {
    if (pos.get_x() < 0 || pos.get_y() < 0 || static_cast<size_t>(pos.get_x()) >= get_size().first
        || static_cast<size_t>(pos.get_y()) >= get_size().second) {
        return false;
    }

    Cell* target_cell = matrix(static_cast<size_t>(pos.get_x()), static_cast<size_t>(pos.get_y())).get();

    if (!target_cell->is_empty() || !target_cell->get_passability()) {
        return false;
    }

    target_cell->set_busy(true);
    target_cell->set_id_entity(id);
    entities_.append(id, target_cell);

    return true;
}

void
MapManager::effect_cells() {
    if (effect_cells_.empty()) {
        return;
    }

    auto& entity_manager = EntityManager::getInstance();
    const size_t num_cells = effect_cells_.size();
    const size_t hardware_threads = std::thread::hardware_concurrency();
    const size_t num_threads = std::min(hardware_threads, (num_cells + 3) / 4); // Минимум 4 ячейки на поток

    if (num_threads <= 1) {
        // Для малого количества ячеек используем однопоточное выполнение
        process_effects(0, num_cells, entity_manager);
        return;
    }

    const size_t cells_per_thread = (num_cells + num_threads - 1) / num_threads;
    std::vector<std::future<void>> futures;

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * cells_per_thread;
        if (start >= num_cells) {
            break;
        }

        size_t end = std::min(start + cells_per_thread, num_cells);
        futures.push_back(
            std::async(std::launch::async, &MapManager::process_effects, this, start, end, std::ref(entity_manager)));
    }

    for (auto& future : futures) {
        future.wait();
    }
}

void
MapManager::process_effects(size_t start, size_t end, EntityManager& entity_manager) {
    for (size_t i = start; i < end; ++i) {
        Cell* cell = effect_cells_[i];
        if (!cell->is_empty()) {
            size_t entity_id = cell->get_id_entity();
            auto* entity = entity_manager.get_entity(entity_id);

            if (!entity) {
                continue;
            }

            if (auto* hp_cell = dynamic_cast<EffectCellHP*>(cell)) {
                entity->modify_hp(hp_cell->give_effect());
            } else if (auto* troop = dynamic_cast<BaseTroop*>(entity)) {
                if (auto* damage_cell = dynamic_cast<EffectCellDamage*>(cell)) {
                    troop->modify_damage(damage_cell->give_effect());
                } else if (auto* speed_cell = dynamic_cast<EffectCellSpeed*>(cell)) {
                    troop->modify_speed(speed_cell->give_effect());
                } else if (auto* range_cell = dynamic_cast<EffectCellRange*>(cell)) {
                    troop->modify_range(range_cell->give_effect());
                }
            }
        }
    }
}

std::optional<Position>
MapManager::get_entity_position(size_t id) const {
    Cell* cell = entities_.find_by_id(id);
    if (!cell) {
        return std::nullopt;
    }
    return cell->get_position();
}
