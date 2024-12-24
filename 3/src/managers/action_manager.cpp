#include "action_manager.hpp"

#include "summon_manager.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"

void
ActionManager::handle_summoner_action(Summoner* summoner) {
    SummonerAction action = Control::getInstance()->get_summoner_action();

    switch (action) {
        case SummonerAction::SUMMON_TROOP: {
            auto available_abilities =
                Schools::getInstance().get_available_abilities(summoner->get_levels(), summoner->get_energy());

            if (!available_abilities.empty()) {
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
                    } catch (const std::runtime_error& e) {
                        (void)e;
                    }
                }
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

            if (!upgradable_abilities.empty()) {
                View::getInstance().send_abilities(upgradable_abilities, View::AbilityDisplayType::UPGRADABLE);
                size_t chosen_ability_id = Control::getInstance()->get_ability_choice();
                // TODO: Handle ability choice for upgrading using chosen_ability_id
                (void)chosen_ability_id;
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
