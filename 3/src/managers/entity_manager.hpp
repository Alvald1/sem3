#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include "../queue/entity/entity.hpp"

class EntityManager {
private:
    std::unordered_map<size_t, std::shared_ptr<Entity>> entities;

public:
    EntityManager() = default;
    ~EntityManager() = default;

    // Delete copy operations to prevent multiple managers managing the same entities
    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;

    // Allow move operations
    EntityManager(EntityManager&&) = default;
    EntityManager& operator=(EntityManager&&) = default;

    void add_entity(std::shared_ptr<Entity> entity) {
        if (entity) {
            entities[entity->get_id()] = entity;
        }
    }

    void remove_entity(size_t id) {
        entities.erase(id);
    }

    [[nodiscard]] std::shared_ptr<Entity> get_entity(size_t id) const {
        auto it = entities.find(id);
        return (it != entities.end()) ? it->second : nullptr;
    }

    [[nodiscard]] bool has_entity(size_t id) const {
        return entities.find(id) != entities.end();
    }

    [[nodiscard]] size_t get_entity_count() const {
        return entities.size();
    }

    void clear() {
        entities.clear();
    }
};

#endif // ENTITY_MANAGER_HPP
