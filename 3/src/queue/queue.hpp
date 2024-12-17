#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>
#include "../entity/entity.hpp"

class SortQueue {
  private:
    std::vector<std::shared_ptr<Entity>> entities;
    size_t shift_index = 0;

    void
    sort_unshifted() {
        if (shift_index < entities.size()) {
            std::stable_sort(entities.begin() + shift_index, entities.end(),
                     [](const auto& a, const auto& b) {
                         return a->get_initiative() > b->get_initiative();
                     });
        }
    }

    void
    sort_shifted() {
        if (shift_index > 0) {
            std::stable_sort(entities.begin(), entities.begin() + shift_index,
                     [](const auto& a, const auto& b) {
                         return a->get_initiative() > b->get_initiative();
                     });
        }
    }

  public:
    void
    insert(std::shared_ptr<Entity> entity) {
        if (!entity) {
            throw std::invalid_argument("Cannot insert null entity");
        }
        if (entities.empty()) {
            entities.push_back(entity);
            return;
        }

        // Compare with front element
        if (entity->get_initiative() > entities[shift_index]->get_initiative()) {
            // Insert at the end of shifted portion
            entities.insert(entities.begin() + shift_index, entity);
            ++shift_index;
            sort_shifted();
        } else {
            // Insert into unshifted portion
            entities.push_back(entity);
            sort_unshifted();
        }
    }

    [[nodiscard]] std::shared_ptr<Entity>
    front() const {
        if (entities.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return entities[shift_index];
    }

    void
    shift() {
        if (entities.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        shift_index = (shift_index + 1) % entities.size();
        if (shift_index == 0) {
            // Start of a new round, sort the unshifted portion
            sort_unshifted();
        }
    }

    void
    remove(size_t id) {
        auto it = std::find_if(entities.begin(), entities.end(),
                               [id](const auto& entity) {
                                   return entity->get_id() == id;
                               });
        if (it != entities.end()) {
            size_t index = std::distance(entities.begin(), it);
            entities.erase(it);
            if (index < shift_index || shift_index >= entities.size()) {
                // Adjust shift_index if necessary
                shift_index = (shift_index == 0) ? 0 : shift_index - 1;
            }
        } else {
            throw std::runtime_error("Entity not found");
        }
    }

    [[nodiscard]] std::shared_ptr<Entity>
    get(size_t id) const {
        auto it = std::find_if(entities.begin(), entities.end(),
                               [id](const auto& entity) {
                                   return entity->get_id() == id;
                               });
        if (it != entities.end()) {
            return *it;
        }
        throw std::runtime_error("Entity not found");
    }
};

#endif // QUEUE_HPP
