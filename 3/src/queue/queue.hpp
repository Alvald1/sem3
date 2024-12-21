#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../managers/entity_manager.hpp"

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

public:
    explicit SortQueue(const EntityManager& manager) : entity_manager(manager) {}
    ~SortQueue() { cleanup(); }
    
    SortQueue(const SortQueue&) = delete;
    SortQueue& operator=(const SortQueue&) = delete;
    
    // Add move operations declarations
    SortQueue(SortQueue&& other) noexcept;
    SortQueue& operator=(SortQueue&& other) noexcept;
    
    void insert(size_t entity_id);
    [[nodiscard]] size_t front() const;
    void shift();
    void remove(size_t id);
    [[nodiscard]] bool empty() const { return head == nullptr; }
    [[nodiscard]] bool get(size_t id) const;
};

#endif // QUEUE_HPP
