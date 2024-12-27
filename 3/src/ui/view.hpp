#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <functional>
#include <ncurses.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "queue/entity/summoner.hpp"
#include "queue/entity/troop/base_troop.hpp"
#include "schools/school/ability/ability.hpp"

class View {
  private:
    static const int INFO_PANEL_WIDTH = 32;    // Add this constant
    static const int SUMMONER_INFO_WIDTH = 30; // Add this constant
    static const int TROOP_INFO_WIDTH = 30;    // Add this constant
    View();
    static View* instance;
    WINDOW* window;
    WINDOW* summoner_info_window;
    WINDOW* troop_info_window{nullptr}; // Add this member
    std::unordered_map<size_t, std::string> ability_icons;

    void init_colors();
    void draw_input_form(int width, int height, bool width_selected) const;
    void create_error_window(const std::string& message) const;

  public:
    void cleanup(); // Remains private
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
    void send_abilities(size_t current_energy, size_t current_experience,
                        const std::vector<std::reference_wrapper<const Ability>>& abilities, AbilityDisplayType type,
                        size_t selected_index) const;

    void add_ability_icon(size_t ability_id, std::string icon);
    const std::string& get_ability_icon(size_t ability_id) const;
    bool has_ability_icon(size_t ability_id) const;

    void show_summoners_selection(const std::vector<std::reference_wrapper<const Ability>>& summoners,
                                  const std::vector<bool>& selected, int current_player, int current_selection) const;

    void clear_ability_panel() const; // Add this method
    void show_error(const std::string& message) const;
    void show_summoner_info(const Summoner& summoner); // Remove const from method
    void show_troop_info(const BaseTroop& troop);
};

#endif // VIEW_HPP_
