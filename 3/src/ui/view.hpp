#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <functional>
#include <ncurses.h>
#include <vector>
#include "schools/school/ability/ability.hpp"

class View {
  private:
    View();
    static View* instance;
    WINDOW* window;

    void init_colors();
    void cleanup();
    void draw_input_form(int width, int height, bool width_selected) const;

  public:
    ~View();
    View(const View&) = delete;
    View& operator=(const View&) = delete;

    static View& getInstance();

    void init();
    void show_menu() const;
    void clear_screen() const;
    void refresh_display() const;
    void show_form(int width, int height, bool width_selected) const;

    // Keep existing ability display methods
    enum class AbilityDisplayType { AVAILABLE, UPGRADABLE };

    const char* get_title(AbilityDisplayType type) const;
    const char* get_empty_message(AbilityDisplayType type) const;
    void send_abilities(const std::vector<std::reference_wrapper<const Ability>>& abilities,
                        AbilityDisplayType type) const;
};

#endif // VIEW_HPP_
