#ifndef TIME_HPP
#define TIME_HPP

#include <cstddef>

class EffectCellSpeedBuilder;
class EffectCellRangeBuilder;
class EffectCellHPBuilder;
class EffectCellDamageBuilder;

/**
 * @brief Class representing time duration for effects
 * 
 * This class manages time-related functionality for effect cells,
 * including time tracking and manipulation.
 */
class Time {
  private:
    size_t time; ///< Current time value

    friend class EffectCellSpeedBuilder;
    friend class EffectCellRangeBuilder;
    friend class EffectCellHPBuilder;
    friend class EffectCellDamageBuilder;

  public:
    /**
     * @brief Construct a new Time object
     * @param t Initial time value
     */
    explicit Time(size_t t) : time(t) {}

    /**
     * @brief Get the current time value
     * @return size_t Current time
     */
    inline size_t
    get_time() const {
        return time;
    }

    /**
     * @brief Set a new time value
     * @param new_time New time value to set
     */
    inline void
    set_time(size_t new_time) {
        time = new_time;
    }

    /**
     * @brief Decrease the time by one unit if greater than zero
     */
    inline void
    decrease_time() {
        if (time > 0) {
            time--;
        }
    }

    /**
     * @brief Check if time is greater than zero
     * @return true if time > 0, false otherwise
     */
    inline bool
    is_not_zero() const {
        return time > 0;
    }
};

#endif // TIME_HPP
