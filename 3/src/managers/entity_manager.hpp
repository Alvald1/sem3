#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include "../queue/entity/entity.hpp"
#include "../queue/queue.hpp"

class EntityManager {
  private:
    static EntityManager* instance_;

    EntityManager() : initiative_queue(*this) {} // Private constructor

    std::unordered_map<size_t, std::shared_ptr<Entity>> entities;
    SortQueue initiative_queue;

  public:
    static EntityManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new EntityManager();
        }
        return *instance_;
    }

    ~EntityManager() = default;

    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
    EntityManager(EntityManager&&) = default;
    EntityManager& operator=(EntityManager&&) = default;

    void
    add_entity(std::shared_ptr<Entity> entity) {
        if (entity) {
            entities[entity->get_id()] = entity;
            initiative_queue.insert(entity->get_id());
        }
    }

    void
    remove_entity(size_t id) {
        if (has_entity(id)) {
            initiative_queue.remove(id);
            entities.erase(id);
        }
    }

    void
    next_turn() {
        if (!initiative_queue.empty()) {
            initiative_queue.shift();
        }
    }

    [[nodiscard]] std::shared_ptr<Entity>
    get_current_entity() const {
        return !initiative_queue.empty() ? get_entity(initiative_queue.front()) : nullptr;
    }

    [[nodiscard]] std::shared_ptr<Entity>
    get_entity(size_t id) const {
        auto it = entities.find(id);
        return (it != entities.end()) ? it->second : nullptr;
    }

    [[nodiscard]] bool
    has_entity(size_t id) const {
        return entities.find(id) != entities.end();
    }

    [[nodiscard]] size_t
    get_entity_count() const {
        return entities.size();
    }

    void
    clear() {
        entities.clear();
    }
};

#endif // ENTITY_MANAGER_HPP
