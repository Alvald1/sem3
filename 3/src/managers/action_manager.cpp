#include "action_manager.hpp"

#include "summon_manager.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"
#include "utilities/exceptions.hpp"

void
ActionManager::handle_summoner_action(Summoner* summoner) {
    SummonerAction action = Control::getInstance()->get_summoner_action();

    switch (action) {
        case SummonerAction::SUMMON_TROOP: {
            auto available_abilities =
                Schools::getInstance().get_available_abilities(summoner->get_levels(), summoner->get_energy());

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
                    summoner->spend_energy(chosen_ability.get_energy());
                    Position target_pos = Control::getInstance()->get_position_choice();
                    SummonManager::getInstance().summon(*summoner, chosen_ability, target_pos);
                } catch (const NotEnoughEnergyException& e) {
                    throw;
                } catch (const InvalidPositionException& e) {
                    summoner->add_energy(chosen_ability.get_energy()); // возвращаем потраченную энергию
                    throw;
                } catch (const InvalidTroopTypeException& e) {
                    summoner->add_energy(chosen_ability.get_energy()); // возвращаем потраченную энергию
                    throw;
                }
            } else {
                throw AbilityNotFoundException();
            }
            break;
        }
        case SummonerAction::ACCUMULATE_ENERGY: {
            summoner->accum_energy();
            break;
        }
        case SummonerAction::UPGRADE_SCHOOL: {
            auto upgradable_abilities =
                Schools::getInstance().get_upgradable_abilities(summoner->get_levels(), summoner->get_experience());
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
                        summoner->upgrade_school(school, required_exp);
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
    }
}

void
ActionManager::handle_troop_action(BaseTroop* troop) {
    (void)troop;
    // TODO: Implement troop-specific actions
}
