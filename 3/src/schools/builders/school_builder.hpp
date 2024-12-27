#ifndef SCHOOL_BUILDER_HPP
#define SCHOOL_BUILDER_HPP

#include "schools/school/ability/ability.hpp"
#include "schools/school/school.hpp"

/**
 * @brief Builder class for creating School objects
 * 
 * Implements the Builder pattern to construct School objects
 * with a fluent interface.
 */
class SchoolBuilder {
  private:
    School school;

  public:
    /**
     * @brief Construct a new School Builder
     * @param name Name of the school to build
     */
    explicit SchoolBuilder(std::string name) : school(std::move(name)) {}

    /**
     * @brief Add ability to the school being built
     * @param ability Ability to add
     * @return Reference to this builder
     */
    SchoolBuilder&
    add_ability(Ability ability) {
        school.add_ability(std::move(ability));
        return *this;
    }

    /**
     * @brief Build and return the School object
     * @return Constructed School object
     */
    [[nodiscard]] School
    build() const {
        return school;
    }
};

#endif // SCHOOL_BUILDER_HPP
