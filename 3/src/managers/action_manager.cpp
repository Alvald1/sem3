#include "action_manager.hpp"
#include "entity_manager.hpp"
#include "map_manager.hpp"

#include "summon_manager.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"
#include "utilities/exceptions.hpp"

void
ActionManager::handle_summoner_action(Summoner& summoner) {
    SummonerAction action = Control::getInstance()->get_summoner_action();

    switch (action) {
        case Control::SummonerAction::SUMMON_TROOP: {
            auto available_abilities =
                Schools::getInstance().get_available_abilities(summoner.get_levels(), summoner.get_energy());

            if (available_abilities.empty()) {
                throw NoAvailableAbilitiesException();
            }
            View::getInstance().send_abilities(available_abilities, View::AbilityDisplayType::AVAILABLE);

            size_t chosen_ability_id = Control::getInstance()->get_ability_choice();

            // Find the chosen ability in available abilities
            auto it = std::find_if(
                available_abilities.begin(), available_abilities.end(),
                [chosen_ability_id](const auto& ability) { return ability.get().get_id() == chosen_ability_id; });

            if (it != available_abilities.end()) {
                const Ability& chosen_ability = it->get();
                try {
                    summoner.spend_energy(chosen_ability.get_energy());
                    Position target_pos = Control::getInstance()->get_position_choice();
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
            View::getInstance().send_abilities(upgradable_abilities, View::AbilityDisplayType::UPGRADABLE);

            if (!upgradable_abilities.empty()) {
                size_t chosen_ability_id = Control::getInstance()->get_ability_choice();
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
    auto action = Control::getInstance()->get_troop_action();

    switch (action) {
        case Control::TroopAction::MOVE: {
            Position current_pos = *MapManager::getInstance().get_entity_position(troop.get_id());
            Position delta = Control::getInstance()->get_position_choice();
            Position target_pos(current_pos + delta);

            // Calculate required movement points
            size_t distance = current_pos.manhattan_distance(target_pos);

            // Check if troop has enough movement points
            if (distance > troop.get_remaining_movement()) {
                throw NotEnoughMovementException(troop.get_remaining_movement(), distance);
            }

            auto& map = MapManager::getInstance();
            try {
                map.move_entity(troop.get_id(), delta);
                troop.spend_movement(distance);
                if (troop.get_remaining_movement() == 0) {
                    // End turn if no movement points left
                    troop.reset_movement();
                }
            } catch (const std::exception& e) {
                throw;
            }
            break;
        }
        case Control::TroopAction::EFFECT: {
            // Position target = Control::getInstance()->get_position_choice();
            // auto& map = MapManager::getInstance();

            // if (map.can_entity_act(troop.get_id(), target)) {
            //     // TODO: Implement effect application
            // }
            break;
        }
        case Control::TroopAction::ATTACK: {
            // Position target = Control::getInstance()->get_position_choice();
            // auto& map = MapManager::getInstance();
            // auto& entity_manager = EntityManager::getInstance();

            // if (map.can_entity_act(troop.get_id(), target)) {
            //     // Find target entity at position and apply damage
            //     auto target_pos = map.get_entity_position(troop.get_id());
            //     if (target_pos && *target_pos == target) {
            //         if (auto* target_entity =
            //                 entity_manager.get_entity(map.matrix(target.get_x(), target.get_y())->get_id_entity())) {
            //             target_entity->modify_hp(-troop.get_damage());
            //         }
            //     }
            // }
            break;
        }
        case Control::TroopAction::SKIP_TURN:
            troop.reset_movement();
            // Do nothing, just skip the turn
            break;
    }
}
