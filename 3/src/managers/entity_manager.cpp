#include "entity_manager.hpp"
#include "queue/entity/summoner.hpp"
#include "queue/entity/troop/base_troop.hpp"
#include "queue/queue.hpp"

EntityManager::EntityManager() : queue_(std::make_unique<SortQueue>(this)) {}

void
EntityManager::add_entity(std::unique_ptr<Entity> entity) {
    if (entity) {
        size_t id = entity->get_id();
        entities_[id] = std::move(entity);
        queue_->insert(id);
    }
}

void
EntityManager::remove_entity(size_t id) {
    if (has_entity(id)) {
        auto entity = dynamic_cast<BaseTroop*>(get_entity(id));
        auto summoner = dynamic_cast<Summoner*>(get_entity(entity->get_id_summoner()));
        summoner->delete_ownership(id);
        queue_->remove(id);
        entities_.erase(id);
    }
}

void
EntityManager::next_turn() {
    if (!queue_->empty()) {
        queue_->shift();
    }
}

Entity*
EntityManager::get_entity(size_t id) {
    return entities_.at(id).get();
}

const Entity*
EntityManager::get_entity(size_t id) const {
    return entities_.at(id).get();
}

Entity*
EntityManager::get_current_entity() {
    return get_entity(queue_->front());
}

const Entity*
EntityManager::get_current_entity() const {
    return get_entity(queue_->front());
}

bool
EntityManager::has_entity(size_t id) const {
    return entities_.find(id) != entities_.end();
}

size_t
EntityManager::get_entity_count() const {
    return entities_.size();
}

void
EntityManager::clear() {
    entities_.clear();
}

std::vector<Entity*>
EntityManager::get_queue_entities() {
    std::vector<Entity*> result;
    auto ids = queue_->to_vector();
    result.reserve(ids.size());

    for (size_t id : ids) {
        result.push_back(get_entity(id));
    }

    return result;
}

std::vector<Entity*>
EntityManager::get_allied_entities(size_t id) {
    std::vector<Entity*> allies;
    Entity* entity = get_entity(id);

    // Try to cast entity to BaseTroop first
    if (auto* troop = dynamic_cast<BaseTroop*>(entity)) {
        // If it's a troop, get its summoner
        auto* summoner = dynamic_cast<Summoner*>(get_entity(troop->get_id_summoner()));
        allies.push_back(summoner); // Add summoner

        // Add all entities owned by the summoner
        for (size_t owned_id : summoner->get_ownerships()) {
            allies.push_back(get_entity(owned_id));
        }
    } else if (auto* summoner = dynamic_cast<Summoner*>(entity)) {
        // If it's already a summoner
        allies.push_back(summoner); // Add the summoner itself

        // Add all entities owned by the summoner
        for (size_t owned_id : summoner->get_ownerships()) {
            allies.push_back(get_entity(owned_id));
        }
    }

    return allies;
}
