#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <vector>
#include "queue/entity/entity.hpp"

// Forward declare SortQueue
class SortQueue;

class EntityManager {
  private:
    static EntityManager* instance_;
    std::unordered_map<size_t, std::unique_ptr<Entity>> entities_;
    std::unique_ptr<SortQueue> queue_;

    // Constructor will be defined in cpp file
    EntityManager();

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
    EntityManager(EntityManager&&) = delete;
    EntityManager& operator=(EntityManager&&) = delete;

    void add_entity(std::unique_ptr<Entity> entity);
    void remove_entity(size_t id);
    void next_turn();
    [[nodiscard]] Entity* get_current_entity();
    [[nodiscard]] const Entity* get_current_entity() const;
    [[nodiscard]] Entity* get_entity(size_t id);
    [[nodiscard]] const Entity* get_entity(size_t id) const;
    [[nodiscard]] bool has_entity(size_t id) const;
    [[nodiscard]] size_t get_entity_count() const;
    void clear();
    [[nodiscard]] std::vector<Entity*> get_queue_entities();
    [[nodiscard]] std::vector<Entity*> get_allied_entities(size_t id);
};

#endif // ENTITY_MANAGER_HPP
