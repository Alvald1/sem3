#include "map_manager.hpp"
#include "utilities/exceptions.hpp"

#include "map/cell/builders/cell_director.hpp"
#include "queue/entity/troop/base_troop.hpp"

void
MapManager::move_entity(size_t id, Position delta) {
    auto current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        throw EntityNotFoundException();
    }

    Position curr_pos = current_cell->get_position();
    Position new_pos(curr_pos + delta);

    // Check bounds and passability
    if (new_pos.get_x() < 0 || new_pos.get_y() < 0 || static_cast<size_t>(new_pos.get_x()) >= get_size().first
        || static_cast<size_t>(new_pos.get_y()) >= get_size().second) {
        throw OutOfBoundsException();
    }

    if (!is_cell_passable(new_pos)) {
        throw CellNotPassableException();
    }
    if (is_cell_occupied(new_pos)) {
        throw CellOccupiedException();
    }

    // Get target cell
    auto target_cell = get_cell(new_pos);

    // Update cells
    current_cell->set_busy(false);
    current_cell->set_id_entity(0);
    target_cell->set_busy(true);
    target_cell->set_id_entity(id);

    // Update entity location
    entities_.remove(id);
    entities_.append(id, target_cell);
}

bool
MapManager::is_cell_occupied(Position pos) const {
    try {
        auto cell = get_cell(pos);
        return !cell->is_empty();
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool
MapManager::is_cell_passable(Position pos) const {
    try {
        auto cell = get_cell(pos);
        return cell->get_passability();
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool
MapManager::can_move_entity(size_t id, Position delta) const {
    auto current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        return false;
    }

    Position curr_pos = current_cell->get_position();
    Position new_pos(curr_pos.get_x() + delta.get_x(), curr_pos.get_y() + delta.get_y());

    return is_cell_passable(new_pos) && !is_cell_occupied(new_pos);
}

bool
MapManager::can_entity_act(size_t id, Position delta) const {
    auto current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        return false;
    }

    Position curr_pos = current_cell->get_position();
    Position target_pos(curr_pos.get_x() + delta.get_x(), curr_pos.get_y() + delta.get_y());

    return is_cell_passable(target_pos);
}

bool
MapManager::add_entity(size_t id, Position pos) {
    try {
        auto target_cell = get_cell(pos);
        if (!target_cell->is_empty() || !target_cell->get_passability()) {
            return false;
        }

        target_cell->set_busy(true);
        target_cell->set_id_entity(id);
        entities_.append(id, target_cell);
        return true;
    } catch (const std::out_of_range&) {
        return false;
    }
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
        auto cell = effect_cells_[i];
        if (!cell->is_empty()) {
            size_t entity_id = cell->get_id_entity();
            auto* entity = entity_manager.get_entity(entity_id);

            if (!entity) {
                continue;
            }

            try {
                if (auto hp_cell = std::dynamic_pointer_cast<EffectCellHP>(cell)) {
                    entity->modify_hp(hp_cell->give_effect());
                } else if (auto* troop = dynamic_cast<BaseTroop*>(entity)) {
                    if (auto damage_cell = std::dynamic_pointer_cast<EffectCellDamage>(cell)) {
                        troop->modify_damage(damage_cell->give_effect());
                    } else if (auto speed_cell = std::dynamic_pointer_cast<EffectCellSpeed>(cell)) {
                        troop->modify_speed(speed_cell->give_effect());
                    } else if (auto range_cell = std::dynamic_pointer_cast<EffectCellRange>(cell)) {
                        troop->modify_range(range_cell->give_effect());
                    }
                }
            } catch (...) {
                // Convert effect cell to basic cell using existing method
                change_cell_type(cell->get_position(), EffectType::NONE);

                // Since change_cell_type updates effect_cells_, adjust the counter
                --i;
            }
        }
    }
}

std::optional<Position>
MapManager::get_entity_position(size_t id) const {
    auto cell = entities_.find_by_id(id);
    if (!cell) {
        return std::nullopt;
    }
    return cell->get_position();
}

void
MapManager::change_cell_type(Position pos, EffectType type, int effect_value, size_t duration) {
    if (pos.get_x() < 0 || pos.get_y() < 0 || static_cast<size_t>(pos.get_x()) >= get_size().first
        || static_cast<size_t>(pos.get_y()) >= get_size().second) {
        throw OutOfBoundsException();
    }

    auto old_cell = get_cell(pos);

    // Remove old cell from effect_cells_ if it exists
    auto it = std::find(effect_cells_.begin(), effect_cells_.end(), old_cell);
    if (it != effect_cells_.end()) {
        effect_cells_.erase(it);
    }

    std::shared_ptr<Cell> new_cell;
    if (type == EffectType::NONE) {
        new_cell = std::make_shared<Cell>(CellDirector::createBasicCell(pos, old_cell->get_passability()));
    } else {
        switch (type) {
            case EffectType::DAMAGE:
                new_cell =
                    std::make_shared<EffectCellDamage>(CellDirector::createDamageCell(pos, effect_value, duration));
                break;
            case EffectType::SPEED:
                new_cell =
                    std::make_shared<EffectCellSpeed>(CellDirector::createSpeedCell(pos, effect_value, duration));
                break;
            case EffectType::RANGE:
                new_cell =
                    std::make_shared<EffectCellRange>(CellDirector::createRangeCell(pos, effect_value, duration));
                break;
            case EffectType::HEALTH:
                new_cell = std::make_shared<EffectCellHP>(CellDirector::createHPCell(pos, effect_value, duration));
                break;
            default: return;
        }
    }

    // Preserve the busy state and entity ID
    new_cell->set_busy(!old_cell->is_empty());
    new_cell->set_id_entity(old_cell->get_id_entity());

    // Replace the old cell
    matrix(pos.get_x(), pos.get_y()) = new_cell;

    // Add to effect cells if it's an effect cell
    if (type != EffectType::NONE) {
        effect_cells_.push_back(new_cell);
    }
}

bool
MapManager::can_entity_attack(size_t id, Position delta) const {
    auto current_cell = entities_.find_by_id(id);
    if (!current_cell) {
        return false;
    }

    Position curr_pos = current_cell->get_position();
    Position target_pos(curr_pos.get_x() + delta.get_x(), curr_pos.get_y() + delta.get_y());

    // Check if target position is within bounds
    if (target_pos.get_x() < 0 || target_pos.get_y() < 0 || static_cast<size_t>(target_pos.get_x()) >= get_size().first
        || static_cast<size_t>(target_pos.get_y()) >= get_size().second) {
        return false;
    }

    // Check if target cell is occupied by another entity
    return is_cell_occupied(target_pos);
}

void
MapManager::remove_entity(size_t id) {
    auto cell = entities_.find_by_id(id);
    if (!cell) {
        return;
    }

    // Reset the cell's state
    cell->set_busy(false);
    cell->set_id_entity(0);

    // Remove entity from entities list
    entities_.remove(id);
}
