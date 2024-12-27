#ifndef NAME_ID_HPP
#define NAME_ID_HPP

#include <string>

/**
 * @brief Class for storing entity names and their unique identifiers
 */
class NameID {
  private:
    size_t id_;        ///< Unique identifier
    std::string name_; ///< Entity name

  public:
    /**
     * @brief Constructs a NameID object
     * @param identifier Unique ID
     * @param name Entity name
     */
    NameID(size_t identifier, std::string name) : id_(identifier), name_(std::move(name)) {}

    /**
     * @brief Copy constructor
     * @param other NameID object to copy from
     */
    NameID(const NameID& other) : id_(other.id_), name_(other.name_) {}

    /**
     * @brief Assignment operator
     * @param other NameID object to assign from
     * @return Reference to this object
     */
    NameID&
    operator=(const NameID& other) {
        if (this != &other) {
            id_ = other.id_;
            name_ = other.name_;
        }
        return *this;
    }

    /**
     * @brief Gets the unique identifier
     * @return ID value
     */
    [[nodiscard]] size_t
    get_id() const {
        return id_;
    }

    /**
     * @brief Gets the entity name
     * @return Reference to the name string
     */
    [[nodiscard]] const std::string&
    get_name() const {
        return name_;
    }

    /**
     * @brief Sets a new name
     * @param new_name New name to set
     */
    void
    set_name(const std::string& new_name) {
        name_ = new_name;
    }
};

#endif // NAME_ID_HPP
