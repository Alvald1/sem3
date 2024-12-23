#include "school_builder.hpp"
#include "schools/school/school.hpp"

SchoolBuilder::SchoolBuilder(std::string name) : school_(new School(std::move(name))) {}

SchoolBuilder&
SchoolBuilder::addAbility(Ability ability) {
    school_->add_ability(std::move(ability));
    return *this;
}

School
SchoolBuilder::build() {
    School result = std::move(*school_);
    delete school_;
    school_ = nullptr;
    return result;
}
