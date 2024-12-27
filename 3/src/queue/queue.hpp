#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef> // for size_t
#include <vector>  // for std::vector

// Forward declare EntityManager
class EntityManager;

/**
 * @brief Circular queue implementation for entity turn order
 * 
 * Maintains a sorted circular queue of entities based on their initiative values.
 */
class SortQueue {
  private:
    struct Node {
        size_t entity_id;
        Node* next;
        Node* prev;

        explicit Node(size_t id) : entity_id(id), next(nullptr), prev(nullptr) {}
    };

    // Change member variable type to match constructor
    EntityManager& entity_manager;
    Node* head = nullptr;
    size_t size = 0;

    void cleanup();
    void link_nodes(Node* first, Node* second);

    // Fix constructor parameter type

    friend class EntityManager;

  public:
    explicit SortQueue(EntityManager& manager) : entity_manager(manager) {}

    ~SortQueue() { cleanup(); }

    SortQueue(const SortQueue&) = delete;
    SortQueue& operator=(const SortQueue&) = delete;
    SortQueue(SortQueue&& other) noexcept;
    SortQueue& operator=(SortQueue&& other) noexcept;

    /**
     * @brief Insert new entity into the queue
     * @param entity_id ID of entity to insert
     * @throw std::invalid_argument if entity doesn't exist
     */
    void insert(size_t entity_id);

    /**
     * @brief Get ID of entity at front of queue
     * @return Entity ID
     * @throw std::runtime_error if queue is empty
     */
    [[nodiscard]] size_t front() const;

    /**
     * @brief Rotate queue to next entity
     * @throw std::runtime_error if queue is empty
     */
    void shift();

    /**
     * @brief Remove entity from queue
     * @param id ID of entity to remove
     * @throw std::runtime_error if entity not found or queue empty
     */
    void remove(size_t id);

    [[nodiscard]] bool
    empty() const {
        return head == nullptr;
    }

    [[nodiscard]] std::vector<size_t> to_vector() const;
};

#endif // QUEUE_HPP
