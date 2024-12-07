#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>
#include "../entity/entity.hpp"

class SortQueue {
  private:
    std::vector<Entity> list;

    void
    sort_by_initiative() {
        std::sort(list.begin(), list.end(),
                  [](const Entity& a, const Entity& b) { return a.getInitiative() > b.getInitiative(); });
    }

  public:
    void
    insert(Entity entity) {
        list.push_back(entity);
        sort_by_initiative();
    }

    Entity
    front() const {
        if (list.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return list.front();
    }

    void
    shift() {
        if (list.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        Entity front = list.front();
        list.erase(list.begin());
        list.push_back(front);
    }

    void
    remove(size_t id) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->getId() == id) {
                list.erase(it);
                return;
            }
        }
        throw std::runtime_error("Entity not found");
    }

    Entity
    get(ID id) const {
        for (const auto& entity : list) {
            if (entity.getId() == id) {
                return entity;
            }
        }
        throw std::runtime_error("Entity not found");
    }
};

#endif // QUEUE_HPP
