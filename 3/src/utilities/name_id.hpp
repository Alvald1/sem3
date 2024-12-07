#ifndef NAME_ID_HPP
#define NAME_ID_HPP

#include <string>

class NameID {
private:
    size_t id;
    std::string name;

public:
    NameID(size_t id, const std::string& name) : id(id), name(name) {}

    size_t get_id() const { return id; }
    
    const std::string& get_name() const { return name; }
    void set_name(const std::string& new_name) { name = new_name; }
};

#endif // NAME_ID_HPP
