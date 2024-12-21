#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../managers/entity_manager.hpp"

// Forward declare EntityManager to resolve circular dependency
class EntityManager;

class SortQueue {
  private:
    struct Node {
        size_t entity_id;
        Node* next;
        Node* prev;

        explicit Node(size_t id) : entity_id(id), next(nullptr), prev(nullptr) {}
    };

    const EntityManager& entity_manager;
    Node* head = nullptr;
    size_t size = 0;

    void cleanup();
    void link_nodes(Node* first, Node* second);

    // Make constructor private and EntityManager a friend
    explicit SortQueue(const EntityManager& manager) : entity_manager(manager) {}
    friend class EntityManager;

  public:
    ~SortQueue() { cleanup(); }

    SortQueue(const SortQueue&) = delete;
    SortQueue& operator=(const SortQueue&) = delete;
    SortQueue(SortQueue&& other) noexcept;
    SortQueue& operator=(SortQueue&& other) noexcept;

    void insert(size_t entity_id);
    [[nodiscard]] size_t front() const;
    void shift();
    void remove(size_t id);

    [[nodiscard]] bool
    empty() const {
        return head == nullptr;
    }
};

#endif // QUEUE_HPP
