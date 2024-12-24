#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef> // for size_t

// Forward declare EntityManager
class EntityManager;

class SortQueue {
  private:
    struct Node {
        size_t entity_id;
        Node* next;
        Node* prev;

        explicit Node(size_t id) : entity_id(id), next(nullptr), prev(nullptr) {}
    };

    // Change member variable type to match constructor
    EntityManager* entity_manager;
    Node* head = nullptr;
    size_t size = 0;

    void cleanup();
    void link_nodes(Node* first, Node* second);

    // Fix constructor parameter type

    friend class EntityManager;

  public:
    explicit SortQueue(EntityManager* manager) : entity_manager(manager) {}

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
