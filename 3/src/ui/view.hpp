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

/**
 * @brief Main view class responsible for rendering the game interface
 * 
 * The View class implements a singleton pattern and handles all visual aspects
 * of the game including menus, game board, and information panels.
 */
class View {
  private:
    /** @brief Width of the information panel */
    static const int INFO_PANEL_WIDTH = 32;
    /** @brief Width of the summoner information window */
    static const int SUMMONER_INFO_WIDTH = 30;
    /** @brief Width of the troop information window */
    static const int TROOP_INFO_WIDTH = 30;

    /** @brief Private constructor for singleton pattern */
    View();
    /** @brief Singleton instance pointer */
    static View* instance;
    /** @brief Main game window */
    WINDOW* window;
    /** @brief Window for displaying summoner information */
    WINDOW* summoner_info_window;
    /** @brief Window for displaying troop information */
    WINDOW* troop_info_window{nullptr};
    /** @brief Map of ability IDs to their visual icons */
    std::unordered_map<size_t, std::string> ability_icons;
    /** @brief Current scroll offset for ability display */
    mutable size_t ability_scroll_offset{0};

    void init_colors();
    void draw_input_form(int width, int height, bool width_selected) const;
    void create_error_window(const std::string& message) const;

  public:
    /**
     * @brief Clean up NCurses windows and restore terminal state
     */
    void cleanup();

    /**
     * @brief Destructor
     */
    ~View();

    /**
     * @brief Get singleton instance of View
     * @return Reference to View instance
     */
    View(const View&) = delete;
    View& operator=(const View&) = delete;

    static View& getInstance();

    /**
     * @brief Initialize NCurses and set up initial display
     */
    void init();

    /**
     * @brief Display the main menu
     */
    void show_menu() const;

    /**
     * @brief Clear the screen
     */
    void clear_screen() const;

    /**
     * @brief Refresh the display
     */
    void refresh_display() const;

    /**
     * @brief Show the form for map size input
     * @param width Current width value
     * @param height Current height value
     * @param width_selected Whether width field is selected
     */
    void show_form(int width, int height, bool width_selected) const;

    /**
     * @brief Enumeration for different ability display types
     */
    enum class AbilityDisplayType { AVAILABLE, UPGRADABLE };

    /**
     * @brief Get title for ability display
     * @param type Type of ability display
     * @return Const char pointer to title string
     */
    const char* get_title(AbilityDisplayType type) const;

    /**
     * @brief Get empty message for ability display
     * @param type Type of ability display
     * @return Const char pointer to empty message string
     */
    const char* get_empty_message(AbilityDisplayType type) const;

    /**
     * @brief Display list of abilities
     * @param current_energy Current energy available
     * @param current_experience Current experience available
     * @param abilities Vector of abilities to display
     * @param type Type of ability display
     * @param selected_index Currently selected ability index
     */
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

    void scroll_abilities_up() const; // Add these methods
    void scroll_abilities_down() const;
    size_t get_max_visible_abilities() const;

    [[nodiscard]] size_t
    get_ability_scroll_offset() const {
        return ability_scroll_offset;
    }

    void show_save_confirmation() const;
    bool show_load_game_menu() const;
};

#endif // VIEW_HPP_
