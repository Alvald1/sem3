#ifndef CREATURE_BUILDER_HPP
#define CREATURE_BUILDER_HPP

#include <memory>
#include <string>
#include "../school/ability/creature.hpp"

class CreatureBuilder {
  public:
    explicit CreatureBuilder(std::string name) : creature_(new Creature(std::move(name))) {}

    CreatureBuilder&
    speed(size_t value) {
        creature_->speed = value;
        return *this;
    }

    CreatureBuilder&
    damage(size_t value) {
        creature_->damage = value;
        return *this;
    }

    CreatureBuilder&
    range(size_t value) {
        creature_->range = value;
        return *this;
    }

    CreatureBuilder&
    type(size_t value) {
        creature_->type = value;
        return *this;
    }

    CreatureBuilder&
    initiative(size_t value) {
        creature_->initiative = value;
        return *this;
    }

    std::unique_ptr<Creature>
    build() {
        return std::move(creature_);
    }

  private:
    std::unique_ptr<Creature> creature_;
};

#endif // CREATURE_BUILDER_HPP
