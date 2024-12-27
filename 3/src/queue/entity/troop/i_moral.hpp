#ifndef I_MORAL_HPP
#define I_MORAL_HPP

#include <cstddef>

/**
 * @brief Interface for entities with morale mechanics
 * 
 * Defines operations for managing morale levels of game entities.
 */
class IMoral {
  public:
    virtual ~IMoral() = default;

    /**
     * @brief Increase entity's morale
     * @param amount Amount to increase morale by
     */
    virtual void increase_morale(std::size_t amount) = 0;

    /**
     * @brief Decrease entity's morale
     * @param amount Amount to decrease morale by
     */
    virtual void decrease_morale(std::size_t amount) = 0;

    /**
     * @brief Balance entity's morale towards neutral
     * @param amount Amount to adjust morale by
     */
    virtual void balance_morale(std::size_t amount) = 0;
};

#endif // I_MORAL_HPP
