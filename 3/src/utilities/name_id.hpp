#ifndef NAME_ID_HPP
#define NAME_ID_HPP

#include <string>

class NameID {
private:
    size_t id;
    std::string name;

public:
    NameID(size_t id, const std::string& name) : id(id), name(name) {}

    size_t getId() const { return id; }
    
    const std::string& getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }
};

#endif // NAME_ID_HPP
