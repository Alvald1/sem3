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
    if (!entity_manager.has_entity(entity_id)) {
        throw std::invalid_argument("Entity does not exist");
    }

    Node* new_node = new Node(entity_id);
    auto new_initiative = entity_manager.get_entity(entity_id)->get_initiative();

    // Если очередь пуста
    if (!head) {
        head = new_node;
        head->next = head; // Зацикливаем на себя
        size = 1;
        return;
    }

    // Находим элемент с максимальной инициативой
    Node* max_node = head;
    Node* current = head->next;
    auto max_initiative = entity_manager.get_entity(head->entity_id)->get_initiative();

    while (current != head) {
        auto curr_initiative = entity_manager.get_entity(current->entity_id)->get_initiative();
        if (curr_initiative > max_initiative) {
            max_initiative = curr_initiative;
            max_node = current;
        }
        current = current->next;
    }

    // Начиная с максимального элемента, ищем место для вставки
    current = max_node;
    do {
        auto next_initiative = entity_manager.get_entity(current->next->entity_id)->get_initiative();
        if (new_initiative > next_initiative) {
            // Вставляем после текущего элемента
            new_node->next = current->next;
            current->next = new_node;

            size++;
            return;
        }
        current = current->next;
    } while (current != max_node);

    // Если мы здесь, значит нужно вставить после max_node
    new_node->next = max_node->next;
    max_node->next = new_node;
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

    // Если удаляем голову
    if (head->entity_id == id) {
        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            Node* new_head = head->next;
            delete head;
            head = new_head;
            last->next = head;
        }
        size--;
        return;
    }

    // Ищем элемент для удаления
    Node* current = head;
    while (current->next != head && current->next->entity_id != id) {
        current = current->next;
    }

    if (current->next == head) {
        throw std::runtime_error("Entity not found in queue");
    }

    Node* to_delete = current->next;
    current->next = to_delete->next;
    delete to_delete;
    size--;
}

std::vector<size_t>
SortQueue::to_vector() const {
    std::vector<size_t> result;
    if (!head) {
        return result;
    }

    result.reserve(size);
    Node* current = head;
    do {
        result.push_back(current->entity_id);
        current = current->next;
    } while (current != head);

    return result;
}
