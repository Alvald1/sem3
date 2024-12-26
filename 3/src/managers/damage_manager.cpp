#include "damage_manager.hpp"
#include "utilities/exceptions.hpp"

#include "entity_manager.hpp"
#include "map_manager.hpp"
#include "queue/entity/summoner.hpp"

DamageManager* DamageManager::instance_ = nullptr;

void
DamageManager::fight(BaseTroop& attacker, Entity& defender) {
    // Check if defender is a troop
    auto* defender_troop = dynamic_cast<BaseTroop*>(&defender);
    auto* defender_summoner = dynamic_cast<Summoner*>(&defender);
    if (defender_troop && attacker.get_id_summoner() == defender_troop->get_id_summoner()) {
        throw FriendlyFireException();
    } else if (defender_summoner) {
        if (attacker.get_id_summoner() == defender_summoner->get_id()) {
            throw FriendlyFireException();
        }
    }

    // Calculate and apply damage from attacker to defender
    int damage = attacker.get_damage();
    defender.modify_hp(-damage);

    // If defender is still alive and is a BaseTroop, perform counterattack
    if (defender.is_alive() && attacker.get_range() == 0) {
        if (defender_troop != nullptr) {
            int counter_damage = defender_troop->get_damage();
            attacker.modify_hp(-counter_damage);
        }
    } else if (!defender.is_alive()) {
        auto& map = MapManager::getInstance();
        auto& entity_manager = EntityManager::getInstance();

        // If the defender was a summoner, remove all their troops first
        if (defender_summoner) {
            // Get copy of ownerships since we'll be modifying it during iteration
            auto ownerships = defender_summoner->get_ownerships();
            for (size_t entity_id : ownerships) {
                map.remove_entity(entity_id);
                entity_manager.remove_entity(entity_id);
            }
        }

        // Remove the defender itself
        map.remove_entity(defender.get_id());
        entity_manager.remove_entity(defender.get_id());
    }
}
