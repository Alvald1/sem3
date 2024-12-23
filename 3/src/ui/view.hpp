#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <functional>
#include <vector>

#include "schools/school/ability/ability.hpp"

class View {
  private:
    View() = default;
    static View* instance;

  public:
    View(const View&) = delete;
    View& operator=(const View&) = delete;

    static View&
    getInstance() {
        if (instance == nullptr) {
            instance = new View();
        }
        return *instance;
    }

    enum class AbilityDisplayType { AVAILABLE, UPGRADABLE };

    const char* get_title(AbilityDisplayType type) const;
    const char* get_empty_message(AbilityDisplayType type) const;
    void send_abilities(const std::vector<std::reference_wrapper<const Ability>>& abilities,
                        AbilityDisplayType type) const;
};

#endif // VIEW_HPP_
