#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <vector>
#include "queue/entity/entity.hpp"
#include "queue/queue.hpp" // Заменяем forward declaration на полное включение

/**
 * @brief Manages all entities in the game
 *
 * This singleton class handles entity creation, removal, and turn management.
 * It maintains a collection of entities and their turn order queue.
 */
class EntityManager {
  private:
    static EntityManager* instance_;
    std::unordered_map<size_t, std::unique_ptr<Entity>> entities_;
    std::unique_ptr<SortQueue> queue_;

    // Constructor will be defined in cpp file
    EntityManager();

  public:
    /**
     * @brief Get the singleton instance
     * @return Reference to the EntityManager instance
     */
    static EntityManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new EntityManager();
        }
        return *instance_;
    }

    /**
     * @brief Destroy the singleton instance
     */
    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    ~EntityManager() = default;

    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
    EntityManager(EntityManager&&) = delete;
    EntityManager& operator=(EntityManager&&) = delete;

    /**
     * @brief Add a new entity to the manager
     * @param entity Unique pointer to the entity to add
     */
    void add_entity(std::unique_ptr<Entity> entity);

    /**
     * @brief Remove an entity from the manager
     * @param id ID of the entity to remove
     */
    void remove_entity(size_t id);

    /**
     * @brief Advance to the next turn in the queue
     */
    void next_turn();

    /**
     * @brief Get the currently active entity
     * @return Pointer to the current entity, or nullptr if none
     */
    [[nodiscard]] Entity* get_current_entity();

    /**
     * @brief Get the currently active entity (const version)
     * @return Const pointer to the current entity, or nullptr if none
     */
    [[nodiscard]] const Entity* get_current_entity() const;

    /**
     * @brief Get an entity by ID
     * @param id ID of the entity to retrieve
     * @return Pointer to the entity, or nullptr if not found
     */
    [[nodiscard]] Entity* get_entity(size_t id);

    /**
     * @brief Get an entity by ID (const version)
     * @param id ID of the entity to retrieve
     * @return Const pointer to the entity, or nullptr if not found
     */
    [[nodiscard]] const Entity* get_entity(size_t id) const;

    /**
     * @brief Check if an entity exists
     * @param id ID to check
     * @return true if entity exists, false otherwise
     */
    [[nodiscard]] bool has_entity(size_t id) const;

    /**
     * @brief Get total number of entities
     * @return Count of entities
     */
    [[nodiscard]] size_t get_entity_count() const;

    /**
     * @brief Remove all entities
     */
    void clear();

    /**
     * @brief Get all entities in turn order
     * @return Vector of pointers to entities
     */
    [[nodiscard]] std::vector<Entity*> get_queue_entities();

    /**
     * @brief Get all entities allied with specified entity
     * @param id ID of entity to find allies for
     * @return Vector of pointers to allied entities
     */
    [[nodiscard]] std::vector<Entity*> get_allied_entities(size_t id);

    /**
     * @brief Check if entity is a summoner
     * @param id ID of entity to check
     * @return true if entity is a summoner, false otherwise
     */
    [[nodiscard]] bool is_summoner(size_t id) const;

    /**
     * @brief Check if entity is a troop
     * @param id ID of entity to check
     * @return true if entity is a troop, false otherwise
     */
    [[nodiscard]] bool is_troop(size_t id) const;
};

#endif // ENTITY_MANAGER_HPP
