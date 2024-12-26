#include "action_manager.hpp"
#include "entity_manager.hpp"
#include "map_manager.hpp"

#include "damage_manager.hpp"
#include "summon_manager.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"
#include "utilities/exceptions.hpp"

void
ActionManager::handle_summoner_action(Summoner& summoner) {
    SummonerAction action = Control::getInstance().get_summoner_action();

    switch (action) {
        case Control::SummonerAction::SUMMON_TROOP: {
            auto available_abilities =
                Schools::getInstance().get_available_abilities(summoner.get_levels(), summoner.get_energy());

            if (available_abilities.empty()) {
                throw NoAvailableAbilitiesException();
            }

            size_t chosen_ability_id =
                Control::getInstance().get_ability_choice(available_abilities, summoner.get_energy());

            // Find the chosen ability in available abilities
            auto it = std::find_if(
                available_abilities.begin(), available_abilities.end(),
                [chosen_ability_id](const auto& ability) { return ability.get().get_id() == chosen_ability_id; });

            if (it != available_abilities.end()) {
                const Ability& chosen_ability = it->get();
                try {
                    auto summoner_pos = MapManager::getInstance().get_entity_position(summoner.get_id());
                    summoner.spend_energy(chosen_ability.get_energy());
                    Position target_pos = Control::getInstance().get_position_choice(*summoner_pos);
                    SummonManager::getInstance().summon(summoner, chosen_ability, target_pos);
                } catch (const NotEnoughEnergyException& e) {
                    throw;
                } catch (const InvalidPositionException& e) {
                    summoner.add_energy(chosen_ability.get_energy()); // возвращаем потраченную энергию
                    throw;
                } catch (const InvalidTroopTypeException& e) {
                    summoner.add_energy(chosen_ability.get_energy()); // возвращаем потраченную энергию
                    throw;
                }
            } else {
                throw AbilityNotFoundException();
            }
            break;
        }
        case Control::SummonerAction::ACCUMULATE_ENERGY: {
            summoner.accum_energy();
            break;
        }
        case Control::SummonerAction::UPGRADE_SCHOOL: {
            auto upgradable_abilities =
                Schools::getInstance().get_upgradable_abilities(summoner.get_levels(), summoner.get_experience());

            if (!upgradable_abilities.empty()) {
                size_t chosen_ability_id =
                    Control::getInstance().get_ability_choice(upgradable_abilities, summoner.get_experience());
                auto it = std::find_if(
                    upgradable_abilities.begin(), upgradable_abilities.end(),
                    [chosen_ability_id](const auto& ability) { return ability.get().get_id() == chosen_ability_id; });
                if (it != upgradable_abilities.end()) {
                    const Ability& chosen_ability = it->get();
                    auto school_opt = Schools::getInstance().find_school_by_ability_id(chosen_ability.get_id());
                    if (!school_opt.has_value()) {
                        throw SchoolNotFoundException();
                    }
                    const School& school = school_opt->get();
                    // Get required experience directly from ability
                    size_t required_exp = chosen_ability.get_experience();
                    try {
                        summoner.upgrade_school(school, required_exp);
                    } catch (const NotEnoughExperienceException& e) {
                        throw; // Пробрасываем дальше для обработки на верхнем уровне
                    } catch (const std::invalid_argument& e) {
                        throw SchoolNotFoundException(school.get_id()); // Преобразуем в наше исключение
                    }
                } else {
                    throw AbilityNotFoundException();
                }
            }
            break;
        }
        case Control::SummonerAction::SKIP_TURN:
            // Do nothing, just skip the turn
            break;
    }
}

void
ActionManager::handle_troop_action(BaseTroop& troop) {

    while (troop.get_remaining_movement() != 0) {
        auto action = Control::getInstance().get_troop_action();

        switch (action) {
            case Control::TroopAction::MOVE: {
                Position current_pos = *MapManager::getInstance().get_entity_position(troop.get_id());
                Position position = Control::getInstance().get_position_choice(current_pos);

                // Calculate required movement points
                size_t distance = current_pos.manhattan_distance(position);

                // Check if troop has enough movement points
                if (distance > troop.get_remaining_movement()) {
                    throw NotEnoughMovementException(troop.get_remaining_movement(), distance);
                }

                auto& map = MapManager::getInstance();
                try {
                    map.move_entity(troop.get_id(), position);
                    troop.spend_movement(distance);
                } catch (const std::exception& e) {
                    throw;
                }
                break;
            }
            case Control::TroopAction::EFFECT: {
                auto& map = MapManager::getInstance();

                auto effect = TypeSystem::get_effects(troop.get_type());
                if (effect.empty()) {
                    throw NoEffectAvailableException();
                }

                Position current_pos = *MapManager::getInstance().get_entity_position(troop.get_id());
                Position position = Control::getInstance().get_position_choice(current_pos);
                if (position.manhattan_distance(current_pos) > troop.get_range()) {
                    throw OutOfRangeException();
                }

                if (map.can_entity_act(troop.get_id(), position)) {
                    map.change_cell_type(position, effect[0].first, troop.get_damage() * (effect[0].second ? 1 : -1),
                                         3);
                    troop.spend_movement(troop.get_speed());
                }
                break;
            }
            case Control::TroopAction::ATTACK: {
                auto& map = MapManager::getInstance();
                auto& entity_manager = EntityManager::getInstance();
                Position current_pos = *MapManager::getInstance().get_entity_position(troop.get_id());
                Position position = Control::getInstance().get_position_choice(current_pos);

                if ((troop.get_range() > 0 && position.manhattan_distance(current_pos) > troop.get_range())
                    || position.manhattan_distance(current_pos) > 1) {
                    throw OutOfRangeException();
                }

                if (map.can_entity_attack(troop.get_id(), position)) {
                    auto cell = map.get_cell(position);
                    size_t target_id = cell->get_id_entity();
                    auto target = entity_manager.get_entity(target_id);
                    if (target == nullptr) {
                        throw EntityNotFoundException();
                    }
                    try {
                        DamageManager::getInstance().fight(troop, *target);
                        troop.spend_movement(troop.get_speed());
                    } catch (const FriendlyFireException& e) {
                        throw; // Пробрасываем дальше для обработки на верхнем уровне
                    } catch (const std::exception& e) {
                        // Обработка других возможных исключений при бое
                        throw GameLogicException(e.what());
                    }
                }
                break;
            }
            case Control::TroopAction::SKIP_TURN:
                // Do nothing, just skip the turn
                troop.spend_movement(troop.get_speed());
                break;
        }
    }
    troop.reset_movement();
}
