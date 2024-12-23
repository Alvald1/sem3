#ifndef SCHOOL_BUILDER_HPP
#define SCHOOL_BUILDER_HPP

#include <memory>
#include "../school/school.hpp"

class SchoolBuilder {
  public:
    explicit SchoolBuilder(std::string name) : school_(std::make_unique<School>(std::move(name))) {}

    SchoolBuilder&
    addAbility(Ability ability) {
        school_->add_ability(std::move(ability));
        return *this;
    }

    School
    build() {
        return std::move(*school_);
    }

  private:
    std::unique_ptr<School> school_;
};

#endif // SCHOOL_BUILDER_HPP
