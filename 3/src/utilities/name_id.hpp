#ifndef NAME_ID_HPP
#define NAME_ID_HPP

#include <string>

class NameID {
  private:
    size_t id_;
    std::string name_;

  public:
    NameID(size_t identifier, std::string name) : id_(identifier), name_(std::move(name)) {}

    [[nodiscard]] size_t
    get_id() const {
        return id_;
    }

    [[nodiscard]] const std::string&
    get_name() const {
        return name_;
    }

    void
    set_name(const std::string& new_name) {
        name_ = new_name;
    }
};

#endif // NAME_ID_HPP
