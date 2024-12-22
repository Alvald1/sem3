#include "action_manager.hpp"
#include "../ui/control.hpp"
#include "../ui/view.hpp"

ActionManager* ActionManager::instance_ = nullptr;

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
                // TODO: Handle ability choice for summoning using chosen_ability_id
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
            }
            break;
        }
    }
}

void
ActionManager::handle_troop_action(BaseTroop* troop) {
    // TODO: Implement troop-specific actions
}
