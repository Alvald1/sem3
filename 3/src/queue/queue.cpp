#include "queue.hpp"
#include "managers/entity_manager.hpp"
#include "queue/entity/entity.hpp"

#include <stdexcept>

void
SortQueue::link_nodes(Node* first, Node* second) {
    if (first) {
        first->next = second;
    }
    if (second) {
        second->prev = first;
    }
}

void
SortQueue::cleanup() {
    if (!head) {
        return;
    }

    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
    head = nullptr;
    size = 0;
}

SortQueue::SortQueue(SortQueue&& other) noexcept
    : entity_manager(other.entity_manager), head(other.head), size(other.size) {
    other.head = nullptr;
    other.size = 0;
}

SortQueue&
SortQueue::operator=(SortQueue&& other) noexcept {
    if (this != &other) {
        cleanup();
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
    }
    return *this;
}

void
SortQueue::insert(size_t entity_id) {
    if (!entity_manager->has_entity(entity_id)) {
        throw std::invalid_argument("Entity does not exist");
    }

    Node* new_node = new Node(entity_id);

    if (!head) {
        head = new_node;
        head->next = head->prev = head;
        size = 1;
        return;
    }

    // Идем влево пока не найдем элемент с меньшей инициативой
    Node* max_node = head;
    Node* current = head->prev;
    auto max_initiative = entity_manager->get_entity(max_node->entity_id)->get_initiative();

    while (current != head) {
        auto curr_initiative = entity_manager->get_entity(current->entity_id)->get_initiative();
        if (curr_initiative <= max_initiative) {
            break; // Нашли первый элемент с меньшей инициативой
        }
        if (curr_initiative > max_initiative) {
            max_node = current;
            max_initiative = curr_initiative;
        }
        current = current->prev;
    }

    // Теперь идем вправо от максимального элемента, чтобы найти место для вставки
    current = max_node;
    auto new_initiative = entity_manager->get_entity(entity_id)->get_initiative();

    do {
        auto curr_initiative = entity_manager->get_entity(current->entity_id)->get_initiative();
        if (new_initiative > curr_initiative) {
            // Insert before current
            link_nodes(current->prev, new_node);
            link_nodes(new_node, current);
            if (current == head) {
                head = new_node;
            }
            size++;
            return;
        }
        current = current->next;
    } while (current != max_node);

    // Вставка после max_node если новый элемент имеет наименьший приоритет
    link_nodes(max_node, new_node);
    link_nodes(new_node, max_node->next);
    size++;
}

size_t
SortQueue::front() const {
    if (!head) {
        throw std::runtime_error("Queue is empty");
    }
    return head->entity_id;
}

void
SortQueue::shift() {
    if (!head) {
        throw std::runtime_error("Queue is empty");
    }
    head = head->next;
}

void
SortQueue::remove(size_t id) {
    if (!head) {
        throw std::runtime_error("Queue is empty");
    }

    Node* current = head;

    do {
        if (current->entity_id == id) {
            if (size == 1) {
                delete head;
                head = nullptr;
            } else {
                link_nodes(current->prev, current->next);
                if (current == head) {
                    head = head->next;
                }
                delete current;
            }
            size--;
            return;
        }
        current = current->next;
    } while (current != head);

    throw std::runtime_error("Entity not found in queue");
}
